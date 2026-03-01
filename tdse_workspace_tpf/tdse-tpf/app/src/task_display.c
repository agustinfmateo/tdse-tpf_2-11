/*
 * @file   : task_display.c
 * @brief  : Display Library (Blocking Init + Non-Blocking TX Queue) - 4 BITS ONLY
 */

/********************** inclusions *******************************************/
#include "main.h"
#include "task_display.h"
#include "task_display_attribute.h"
#include "logger.h"
#include "dwt.h"
#include <stdbool.h>

/********************** macros and definitions *******************************/
#ifndef OFF
#define OFF    0
#endif
#ifndef ON
#define ON     ( !OFF )
#endif

#define G_TASK_DISP_CNT_INIT        0ul
#define G_TASK_DISP_TICK_CNT_INI    0ul

/* Instruction Set Commands */
#define DISPLAY_IR_CLEAR_DISPLAY   0b00000001
#define DISPLAY_IR_ENTRY_MODE_SET  0b00000100
#define DISPLAY_IR_DISPLAY_CONTROL 0b00001000
#define DISPLAY_IR_FUNCTION_SET    0b00100000
#define DISPLAY_IR_SET_DDRAM_ADDR  0b10000000

/* Entry Mode Set Flags */
#define DISPLAY_IR_ENTRY_MODE_SET_INCREMENT 0b00000010
#define DISPLAY_IR_ENTRY_MODE_SET_DECREMENT 0b00000000
#define DISPLAY_IR_ENTRY_MODE_SET_SHIFT     0b00000001
#define DISPLAY_IR_ENTRY_MODE_SET_NO_SHIFT  0b00000000

/* Display Control Flags */
#define DISPLAY_IR_DISPLAY_CONTROL_DISPLAY_ON  0b00000100
#define DISPLAY_IR_DISPLAY_CONTROL_DISPLAY_OFF 0b00000000
#define DISPLAY_IR_DISPLAY_CONTROL_CURSOR_ON   0b00000010
#define DISPLAY_IR_DISPLAY_CONTROL_CURSOR_OFF  0b00000000
#define DISPLAY_IR_DISPLAY_CONTROL_BLINK_ON    0b00000001
#define DISPLAY_IR_DISPLAY_CONTROL_BLINK_OFF   0b00000000

/* Function Set Flags */
#define DISPLAY_IR_FUNCTION_SET_8BITS    0b00010000
#define DISPLAY_IR_FUNCTION_SET_4BITS    0b00000000
#define DISPLAY_IR_FUNCTION_SET_2LINES   0b00001000
#define DISPLAY_IR_FUNCTION_SET_1LINE    0b00000000
#define DISPLAY_IR_FUNCTION_SET_5x10DOTS 0b00000100
#define DISPLAY_IR_FUNCTION_SET_5x8DOTS  0b00000000

/* Line Addresses for 16x2 Display */
#define DISPLAY_16x2_LINE1_FIRST_CHARACTER_ADDRESS 0
#define DISPLAY_16x2_LINE2_FIRST_CHARACTER_ADDRESS 64

#define DISPLAY_RS_INSTRUCTION 0
#define DISPLAY_RS_DATA        1

#define DISPLAY_RW_WRITE 0
#define DISPLAY_RW_READ  1

/* Pin Mapping Constants (4-bit mode only) */
#define DISPLAY_PIN_RS  4
#define DISPLAY_PIN_RW  5
#define DISPLAY_PIN_EN  6
#define DISPLAY_PIN_D4 11
#define DISPLAY_PIN_D5 12
#define DISPLAY_PIN_D6 13
#define DISPLAY_PIN_D7 14

#define DISPLAY_DEL_37US	37ul
#define DISPLAY_DEL_01US	01ul

/* Buffer Size for Non-Blocking String Writes */
#define DISPLAY_TX_BUF_SIZE 128

/********************** internal data declaration ****************************/

/********************** internal data definition *****************************/
task_display_dta_t task_display_dta_list[] = {
    {ST_DISP_IDLE, false, {0}, {0}, 0, 0}
};

#define DISPLAY_DTA_QTY (sizeof(task_display_dta_list)/sizeof(task_display_dta_t))

const char *p_task_display = "Task Display (4-Bits Blocking Init + Non-Blocking TX)";

/********************** external data declaration ****************************/
uint32_t g_task_display_cnt;
volatile uint32_t g_task_display_tick_cnt;


/********************** internal functions declaration ***********************/
static void displayPinWrite( uint8_t pinName, int value );
static void displayDataBusWrite( uint8_t dataByte );
static void displayCodeWrite( bool type, uint8_t dataBus );
static void displayQueuePush( bool type, uint8_t data );
void display_delay_us(uint32_t delay_us);

/********************** external functions definition ************************/

void task_display_init(void *parameters)
{
    uint32_t index;
    task_display_dta_t *p_task_display_dta;

    /* Print out: Task Initialized */
    LOGGER_LOG("  %s is running - %s\r\n", GET_NAME(task_display_init), p_task_display);

    g_task_display_cnt = G_TASK_DISP_CNT_INIT;

    for (index = 0; DISPLAY_DTA_QTY > index; index++)
    {
        p_task_display_dta = &task_display_dta_list[index];

        p_task_display_dta->initial8BitCommunicationIsCompleted = false;
        p_task_display_dta->head = 0;
        p_task_display_dta->tail = 0;
        p_task_display_dta->state = ST_DISP_IDLE;
    }

    g_task_display_tick_cnt = G_TASK_DISP_TICK_CNT_INI;

    /* --- Secuencia de Inicialización Bloqueante --- */
    HAL_Delay(50);

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, DISPLAY_IR_FUNCTION_SET | DISPLAY_IR_FUNCTION_SET_8BITS );
    HAL_Delay(5);

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, DISPLAY_IR_FUNCTION_SET | DISPLAY_IR_FUNCTION_SET_8BITS );
    HAL_Delay(1);

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, DISPLAY_IR_FUNCTION_SET | DISPLAY_IR_FUNCTION_SET_8BITS );
    HAL_Delay(1);

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, DISPLAY_IR_FUNCTION_SET | DISPLAY_IR_FUNCTION_SET_4BITS );
    HAL_Delay(1);

    task_display_dta_list->initial8BitCommunicationIsCompleted = true;

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, DISPLAY_IR_FUNCTION_SET | DISPLAY_IR_FUNCTION_SET_4BITS | DISPLAY_IR_FUNCTION_SET_2LINES | DISPLAY_IR_FUNCTION_SET_5x8DOTS );
    HAL_Delay(1);

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, DISPLAY_IR_DISPLAY_CONTROL | DISPLAY_IR_DISPLAY_CONTROL_DISPLAY_OFF | DISPLAY_IR_DISPLAY_CONTROL_CURSOR_OFF | DISPLAY_IR_DISPLAY_CONTROL_BLINK_OFF );
    HAL_Delay(1);

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, DISPLAY_IR_CLEAR_DISPLAY );
    HAL_Delay(2);

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, DISPLAY_IR_ENTRY_MODE_SET | DISPLAY_IR_ENTRY_MODE_SET_INCREMENT | DISPLAY_IR_ENTRY_MODE_SET_NO_SHIFT );
    HAL_Delay(1);

    displayCodeWrite( DISPLAY_RS_INSTRUCTION, DISPLAY_IR_DISPLAY_CONTROL | DISPLAY_IR_DISPLAY_CONTROL_DISPLAY_ON | DISPLAY_IR_DISPLAY_CONTROL_CURSOR_OFF | DISPLAY_IR_DISPLAY_CONTROL_BLINK_OFF );
    HAL_Delay(1);
}

void task_display_update(void *parameters)
{
    uint32_t index;
    task_display_dta_t *p_task_display_dta;
    bool b_time_update_required = false;

    /* Update Task Display Counter */
    g_task_display_cnt++;

    /* Protect shared resource (g_task_display_tick_cnt) */
    __asm("CPSID i");   /* disable interrupts*/
    if (G_TASK_DISP_TICK_CNT_INI < g_task_display_tick_cnt)
    {
        g_task_display_tick_cnt--;
        b_time_update_required = true;
    }
    __asm("CPSIE i");   /* enable interrupts*/

    while (b_time_update_required)
    {
        /* Protect shared resource (g_task_display_tick_cnt) */
        __asm("CPSID i");   /* disable interrupts*/
        if (G_TASK_DISP_TICK_CNT_INI < g_task_display_tick_cnt)
        {
            g_task_display_tick_cnt--;
            b_time_update_required = true;
        }
        else
        {
            b_time_update_required = false;
        }
        __asm("CPSIE i");   /* enable interrupts*/

        for (index = 0; DISPLAY_DTA_QTY > index; index++)
        {
            /* Update Task Display Data Pointer */
            p_task_display_dta = &task_display_dta_list[index];

            switch (p_task_display_dta->state)
            {
                case ST_DISP_IDLE:
                    if (p_task_display_dta->head != p_task_display_dta->tail)
                    {
                        bool type = p_task_display_dta->tx_type[p_task_display_dta->tail];
                        uint8_t data = p_task_display_dta->tx_buffer[p_task_display_dta->tail];
                        p_task_display_dta->tail = (p_task_display_dta->tail + 1) % DISPLAY_TX_BUF_SIZE;

                        displayCodeWrite(type, data);
                    }
                    break;
                default:
                    p_task_display_dta->state = ST_DISP_IDLE;
                    break;
            }
        }
    }
}

/* API Calls (Non-Blocking via Queue) */

void displayCharPositionWrite( uint8_t charPositionX, uint8_t charPositionY )
{
    uint8_t target_addr = 0;
    switch( charPositionY ) {
        case 0:
            target_addr = DISPLAY_16x2_LINE1_FIRST_CHARACTER_ADDRESS + charPositionX;
            break;
        case 1:
            target_addr = DISPLAY_16x2_LINE2_FIRST_CHARACTER_ADDRESS + charPositionX;
            break;
        default:
            return; /* Out of bounds for 16x2 */
    }
    displayQueuePush( DISPLAY_RS_INSTRUCTION, DISPLAY_IR_SET_DDRAM_ADDR | target_addr );
}



void displayStringWrite( const char * str )
{
    while (*str) {
        displayQueuePush(DISPLAY_RS_DATA, *str++);
    }
}

void displayClear( void )
{
    displayQueuePush(DISPLAY_RS_INSTRUCTION, DISPLAY_IR_CLEAR_DISPLAY);
}

/********************** internal functions definition ************************/

static void displayQueuePush(bool type, uint8_t data)
{
    task_display_dta_t *p_dta = &task_display_dta_list[0];
    uint16_t next_head = (p_dta->head + 1) % DISPLAY_TX_BUF_SIZE;

    if (next_head != p_dta->tail) {
        p_dta->tx_buffer[p_dta->head] = data;
        p_dta->tx_type[p_dta->head] = type;
        p_dta->head = next_head;
    }
}

static void displayCodeWrite( bool type, uint8_t dataBus )
{
	if ( type == DISPLAY_RS_INSTRUCTION )
		displayPinWrite( DISPLAY_PIN_RS, DISPLAY_RS_INSTRUCTION );
	else
		displayPinWrite( DISPLAY_PIN_RS, DISPLAY_RS_DATA );
	displayPinWrite( DISPLAY_PIN_RW, DISPLAY_RW_WRITE );
	displayDataBusWrite( dataBus );
}

static void displayPinWrite( uint8_t pinName, int value )
{
    switch( pinName ) {
    	case DISPLAY_PIN_D4: HAL_GPIO_WritePin(D7_GPIO_Port, D7_Pin, value);   break;
		case DISPLAY_PIN_D5: HAL_GPIO_WritePin(D6_GPIO_Port, D6_Pin, value);   break;
		case DISPLAY_PIN_D6: HAL_GPIO_WritePin(D5_GPIO_Port, D5_Pin, value);   break;
		case DISPLAY_PIN_D7: HAL_GPIO_WritePin(D4_GPIO_Port, D4_Pin, value);   break;
		case DISPLAY_PIN_RS: HAL_GPIO_WritePin(D9_GPIO_Port, D9_Pin, value);   break;
		case DISPLAY_PIN_EN: HAL_GPIO_WritePin(D8_GPIO_Port, D8_Pin, value);   break;
        case DISPLAY_PIN_RW: break;
        default: break;
    }
}

static void displayDataBusWrite( uint8_t dataBus )
{
    task_display_dta_t *p_dta = &task_display_dta_list[0];

    /* Envía el Nibble Alto (High Nibble) */
    displayPinWrite( DISPLAY_PIN_EN, OFF );
    displayPinWrite( DISPLAY_PIN_D7, dataBus & 0b10000000 );
    displayPinWrite( DISPLAY_PIN_D6, dataBus & 0b01000000 );
    displayPinWrite( DISPLAY_PIN_D5, dataBus & 0b00100000 );
    displayPinWrite( DISPLAY_PIN_D4, dataBus & 0b00010000 );

    if (p_dta->initial8BitCommunicationIsCompleted == true) {
        displayPinWrite( DISPLAY_PIN_EN, ON );
        display_delay_us(DISPLAY_DEL_01US);

        displayPinWrite( DISPLAY_PIN_EN, OFF );
        display_delay_us(DISPLAY_DEL_37US);
        displayPinWrite( DISPLAY_PIN_D7, dataBus & 0b00001000 );
        displayPinWrite( DISPLAY_PIN_D6, dataBus & 0b00000100 );
        displayPinWrite( DISPLAY_PIN_D5, dataBus & 0b00000010 );
        displayPinWrite( DISPLAY_PIN_D4, dataBus & 0b00000001 );
    }
    displayPinWrite( DISPLAY_PIN_EN, ON );
    display_delay_us(DISPLAY_DEL_01US);

    displayPinWrite( DISPLAY_PIN_EN, OFF );
    display_delay_us(DISPLAY_DEL_37US);
}

void display_delay_us(uint32_t delay_us)
{
	uint32_t now = cycle_counter_time_us();
	uint32_t then = delay_us + now;

	while (now < then)
		now = cycle_counter_time_us();
}

/********************** end of file ******************************************/
