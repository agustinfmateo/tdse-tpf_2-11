/*
 * @file   : task_eeprom¿.c
 */

/********************** inclusions *******************************************/
/* Project includes. */
#include "main.h"
#include <string.h>

/* Demo includes. */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes. */
#include "app.h"
#include "task_eeprom_attribute.h"
#include "task_eeprom_interface.h"
#include "task_menu_attribute.h"

/********************** macros and definitions *******************************/
#define G_TASK_EEP_CNT_INIT			0ul
#define G_TASK_EEP_TICK_CNT_INI		0ul

#define DEL_EEPROM_WRITE_MS         5ul

#define PAGE_SIZE 					64     // in Bytes
#define PAGE_NUM  					512    // number of pages
#define TOTAL_SIZE                  (PAGE_SIZE * PAGE_NUM)
#define EEPROM_START_PAGE			0x0000
#define EMPTY_SLOT 					0xFFFFFFFF

#define SIZE_OPENING     			(sizeof(sys_cfg_opening_t)) 								// Tamaño de la estructura opening
#define SIZE_SLOT_CYCLIC 			(sizeof(sys_cfg_save_t))									// Tamaño de la estructura save
#define MAX_SLOTS_CYCLIC            ((TOTAL_SIZE - MEM_ADDR_CYCLIC_INIT) / SIZE_SLOT_CYCLIC)	// Cuantas veces se puede guardar sin dar vuelta


// EEPROM ADDRESS (8bits)
#define EEPROM_ADDR 				0xA0
#define MEM_ADDR_OPENING            0x0000
#define EEPROM_I2C 					&hi2c1
#define MEM_ADDR_CYCLIC_INIT        (SIZE_OPENING)

/********************** internal data declaration ****************************/
const task_eeprom_cfg_t task_eeprom_cfg_list[] = {
	{EEPROM_ADDR, EEPROM_START_PAGE,  PAGE_SIZE,  DEL_EEPROM_WRITE_MS}
};

task_eeprom_dta_t task_eeprom_dta_list[] = {
	{0, ST_EEPROM_IDLE, EV_EEPROM_NONE, MEM_ADDR_OPENING, NULL, 0, 0, 0}
};

#define EEPROM_CFG_QTY	(sizeof(task_eeprom_cfg_list)/sizeof(task_eeprom_cfg_t))
#define EEPROM_DTA_QTY	(sizeof(task_eeprom_dta_list)/sizeof(task_eeprom_dta_t))

static volatile bool g_i2c_op_complete = true;
static uint8_t erase_buffer[PAGE_SIZE];

/********************** internal functions declaration ***********************/

static uint16_t calc_cyclic_addr(uint16_t slot_idx);
static void find_latest_slot(task_eeprom_dta_t *dta, sys_cfg_save_t *p_data_sv);
static int8_t write_eeprom(task_eeprom_dta_t *dta, uint16_t addr, uint8_t* data, uint16_t size);
static int8_t read_eeprom(uint16_t addr, uint8_t* data, uint16_t size);
static int8_t read_eeprom_blocking(uint16_t addr, uint8_t* data, uint16_t size);
static bool write_chunk(task_eeprom_dta_t *dta);

/********************** internal data definition *****************************/
const char *p_task_eeprom 		= "Task eeprom (eeprom Statechart)";
const char *p_task_eeprom_ 		= "Non-Blocking & Update By Time Code";

/********************** external data declaration ****************************/
uint32_t g_task_eeprom_cnt;
volatile uint32_t g_task_eeprom_tick_cnt;

extern I2C_HandleTypeDef hi2c1;


//Esto hay que borrarlo cuando decidamos donde poner las estructuras
//
//
sys_cfg_opening_t sys_op;
sys_cfg_save_t sys_cfg;



/********************** external functions definition ************************/
void task_eeprom_init(void *parameters)
{
	uint32_t index;
	task_eeprom_dta_t *p_task_eeprom_dta;
	task_eeprom_st_t state;
	task_eeprom_ev_t event;

	/* Print out: Task Initialized */
	LOGGER_LOG("  %s is running - %s\r\n", GET_NAME(task_eeprom_init), p_task_eeprom);
	LOGGER_LOG("  %s is a %s\r\n", GET_NAME(task_eeprom), p_task_eeprom_);

	g_task_eeprom_cnt = G_TASK_EEP_CNT_INIT;

	/* Print out: Task execution counter */
	LOGGER_LOG("   %s = %lu\r\n", GET_NAME(g_task_eeprom_cnt), g_task_eeprom_cnt);

	for (index = 0; EEPROM_DTA_QTY > index; index++)
	{
		/* Update Task eeprom Configuration & Data Pointer */
		p_task_eeprom_dta = &task_eeprom_dta_list[index];

		/* Print out: Index & Task execution FSM */
		LOGGER_LOG("   %s = %lu", GET_NAME(index), index);

		state = p_task_eeprom_dta->state;
		LOGGER_LOG("   %s = %lu", GET_NAME(state), (uint32_t)state);

		event = p_task_eeprom_dta->event;
		LOGGER_LOG("   %s = %lu", GET_NAME(event), (uint32_t)event);

		LOGGER_LOG("  Init: Last ID: %lu, Slot: %d\r\n", p_task_eeprom_dta->current_id, p_task_eeprom_dta->current_slot_id);
	}

	g_task_eeprom_tick_cnt = G_TASK_EEP_TICK_CNT_INI;
}

void task_eeprom_update(void *parameters)
{
	uint32_t index;
	const task_eeprom_cfg_t *p_task_eeprom_cfg;
	task_eeprom_dta_t *p_task_eeprom_dta;
	bool b_time_update_required = false;

	/* Update Task eeprom Counter */
	g_task_eeprom_cnt++;

	/* Protect shared resource (g_task_eeprom_tick_cnt) */
	__asm("CPSID i");	/* disable interrupts*/
    if (G_TASK_EEP_TICK_CNT_INI < g_task_eeprom_tick_cnt)
    {
    	g_task_eeprom_tick_cnt--;
    	b_time_update_required = true;
    }
    __asm("CPSIE i");	/* enable interrupts*/

    while (b_time_update_required)
    {
		/* Protect shared resource (g_task_eeprom_tick_cnt) */
		__asm("CPSID i");	/* disable interrupts*/
		if (G_TASK_EEP_TICK_CNT_INI < g_task_eeprom_tick_cnt)
		{
			g_task_eeprom_tick_cnt--;
			b_time_update_required = true;
		}
		else
		{
			b_time_update_required = false;
		}
		__asm("CPSIE i");	/* enable interrupts*/

    	for (index = 0; EEPROM_DTA_QTY > index; index++)
		{
    		/* Update Task eeprom Configuration & Data Pointer */
    		p_task_eeprom_cfg = &task_eeprom_cfg_list[index];
			p_task_eeprom_dta = &task_eeprom_dta_list[index];

			switch (p_task_eeprom_dta->state)
			{
				case ST_EEPROM_IDLE:

					if (p_task_eeprom_dta->event == EV_EEPROM_NONE) break;

					if (p_task_eeprom_dta->event == EV_EEPROM_SAVE_OPENING)
					{
						g_i2c_op_complete = false;

						write_eeprom(p_task_eeprom_dta, MEM_ADDR_OPENING, (uint8_t*)&sys_op, SIZE_OPENING);
						p_task_eeprom_dta->state = ST_EEPROM_WAIT_TX;
						p_task_eeprom_dta->event = EV_EEPROM_NONE;
					}
					else if (p_task_eeprom_dta->event == EV_EEPROM_SAVE_CYCLIC)
					{
						g_i2c_op_complete = false;

						uint16_t next_slot = p_task_eeprom_dta->current_slot_id + 1;
						if (next_slot >= MAX_SLOTS_CYCLIC) next_slot = 0;
						uint16_t addr = calc_cyclic_addr(next_slot);

						p_task_eeprom_dta->current_id++;
						sys_cfg.data_id = p_task_eeprom_dta->current_id;

						write_eeprom(p_task_eeprom_dta, addr, (uint8_t*)&sys_cfg, SIZE_SLOT_CYCLIC);
						p_task_eeprom_dta->current_slot_id = next_slot;
						p_task_eeprom_dta->state = ST_EEPROM_WAIT_TX;
						p_task_eeprom_dta->event = EV_EEPROM_NONE;
					}
					else if (p_task_eeprom_dta->event == EV_EEPROM_LOAD_REQ){
						g_i2c_op_complete = false;

						read_eeprom(MEM_ADDR_OPENING, (uint8_t*)&sys_op, SIZE_OPENING);
						p_task_eeprom_dta->state = ST_EEPROM_WAIT_RX;
						p_task_eeprom_dta->event = EV_EEPROM_NONE;
					}

					else if (p_task_eeprom_dta->event == EV_EEPROM_ERASE_ALL)
					{
						g_i2c_op_complete = false;
						LOGGER_LOG("Formatting in progress...\r\n");
						memset(erase_buffer, 0xFF, PAGE_SIZE); // crea un buffer para eliminar una página a la vez

						p_task_eeprom_dta->wr_addr = 0;
						p_task_eeprom_dta->state = ST_EEPROM_ERASE_RUNNING;
					}

					break;

				case ST_EEPROM_WAIT_TX:

					if(!g_i2c_op_complete) break;

					p_task_eeprom_dta->tick = p_task_eeprom_cfg->tick_write_delay;
					p_task_eeprom_dta->state = ST_EEPROM_WRITE_CYCLE;

					break;

				case ST_EEPROM_WAIT_RX:

					if(!g_i2c_op_complete) break;

					p_task_eeprom_dta->state = ST_EEPROM_IDLE;

					break;

				case ST_EEPROM_WRITE_CYCLE:
					if (p_task_eeprom_dta->tick > 0) p_task_eeprom_dta->tick--;

					if(p_task_eeprom_dta->tick == 0){
						if(write_chunk(p_task_eeprom_dta))
						{
							p_task_eeprom_dta->state = ST_EEPROM_WAIT_TX;
						}
						else if (p_task_eeprom_dta->event == EV_EEPROM_ERASE_ALL){
							p_task_eeprom_dta->state = ST_EEPROM_ERASE_RUNNING;
						}
						else {
							p_task_eeprom_dta->state = ST_EEPROM_IDLE;
							p_task_eeprom_dta->event = EV_EEPROM_NONE;
						}
					}
					break;

				case ST_EEPROM_ERASE_RUNNING:
					if(p_task_eeprom_dta->wr_addr >= TOTAL_SIZE){
						LOGGER_LOG("Formatting Complete.\r\n")
						p_task_eeprom_dta->current_id = 0;
						p_task_eeprom_dta->current_slot_id = 0;
						p_task_eeprom_dta->state = ST_EEPROM_IDLE;
						p_task_eeprom_dta->event = EV_EEPROM_NONE;
						break;
					}

					g_i2c_op_complete = false;

					write_eeprom(p_task_eeprom_dta, p_task_eeprom_dta->wr_addr, erase_buffer, PAGE_SIZE);
					p_task_eeprom_dta->state = ST_EEPROM_WAIT_TX;
					break;

				default:
					p_task_eeprom_dta->state = ST_EEPROM_IDLE;
					break;
			}
		}
    }
}

bool eeprom_check_and_load(task_eeprom_id_t identifier, sys_cfg_opening_t *p_data_op, sys_cfg_save_t *p_data_sv) {
	task_eeprom_dta_t *p_task_eeprom_dta = &task_eeprom_dta_list[identifier];
	uint8_t *p_bytes = (uint8_t*)p_data_op;	// Se castea (uint8_t*) dado que i2c trabaja en streams de bytes

    read_eeprom_blocking(MEM_ADDR_OPENING, p_bytes, SIZE_OPENING);

    for (uint16_t i = 0; i < SIZE_OPENING; i++) {
        if (p_bytes[i] != 0xFF) {
            find_latest_slot(p_task_eeprom_dta, p_data_sv);
        	return true;
        }
    }
    return false;
}


void HAL_I2C_MemTxCpltCallback(I2C_HandleTypeDef *hi2c) {
	if (hi2c == &hi2c1) g_i2c_op_complete = true;
}

void HAL_I2C_MemRxCpltCallback(I2C_HandleTypeDef *hi2c) {
	if (hi2c == &hi2c1) g_i2c_op_complete = true;
}

/********************** internal functions definition ************************/

static uint16_t calc_cyclic_addr(uint16_t slot_idx) {
    return MEM_ADDR_CYCLIC_INIT + (slot_idx * SIZE_SLOT_CYCLIC);
}

static bool write_chunk(task_eeprom_dta_t *dta) {

    if (dta->wr_bytes_left == 0) return false;

    uint16_t space_in_page = PAGE_SIZE - (dta->wr_addr % PAGE_SIZE);
    uint16_t chunk = (dta->wr_bytes_left <= space_in_page) ? dta->wr_bytes_left : space_in_page; // como mucho escribe lo restante en la página

    g_i2c_op_complete = false;

    if (HAL_I2C_Mem_Write_IT(EEPROM_I2C, EEPROM_ADDR, dta->wr_addr, I2C_MEMADD_SIZE_16BIT, dta->wr_ptr, chunk) != HAL_OK) {
        return false;
    }

    dta->wr_addr += chunk;
    dta->wr_ptr += chunk;
    dta->wr_bytes_left -= chunk;

    return true;
}


static int8_t write_eeprom(task_eeprom_dta_t *dta, uint16_t addr, uint8_t* data, uint16_t size) {
    dta->wr_addr = addr;
    dta->wr_ptr = data;
    dta->wr_bytes_left = size;

    if (write_chunk(dta)) {
        return 0;
    }
    return -1;
}

static int8_t read_eeprom(uint16_t addr, uint8_t* data, uint16_t size) {

    g_i2c_op_complete = false;

    if (HAL_I2C_Mem_Read_IT(EEPROM_I2C, EEPROM_ADDR, addr, I2C_MEMADD_SIZE_16BIT, data, size) != HAL_OK) {
        g_i2c_op_complete = true;
        return -1;
    }
    return 0;
}

static int8_t read_eeprom_blocking(uint16_t addr, uint8_t* data, uint16_t size) {

    if(HAL_I2C_Mem_Read(EEPROM_I2C, EEPROM_ADDR, addr, I2C_MEMADD_SIZE_16BIT, data, size, 100) == HAL_OK) {
        return 0;
    }
    return -1;
}


//Es bloqueante pero se ejecuta en cada ciclo, sólo en el init
static uint32_t read_id(uint16_t slot) {
    uint32_t temp_id = 0;
    uint16_t addr = calc_cyclic_addr(slot);
    read_eeprom_blocking(addr, (uint8_t*)&temp_id, sizeof(uint32_t));
    return temp_id;
}

static void find_latest_slot(task_eeprom_dta_t *dta, sys_cfg_save_t *p_data_sv) {
    uint16_t low = 0;
    uint16_t high = MAX_SLOTS_CYCLIC - 1;

    uint32_t val_first = read_id(low);
    uint32_t val_last  = read_id(high);

    // Memoria vacia
    if (val_first == EMPTY_SLOT) {
        dta->current_id = 0;
        dta->current_slot_id = 0;
        return;
    }

    // Memoria incompleta
    if (val_last == EMPTY_SLOT) {
        uint16_t ans = 0;
        while (low <= high) {
            uint16_t mid = low + (high - low) / 2;
            if (read_id(mid) != EMPTY_SLOT) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        dta->current_slot_id = ans;
    }

    // Memoria llena y rotada cíclicamente
    else {
        // Si esta justo llena
        if (val_first < val_last) {
            dta->current_slot_id = high;
        }
        else {
            // Busco el mínimo, chequeando donde se produce la ruptura
            while (low < high) {
                uint16_t mid = low + (high - low) / 2;

                if (read_id(mid) > read_id(high)) {
                    low = mid + 1;
                }
                else {
                    high = mid;
                }
            }

            // Al terminar low apunta al mínimo, por lo que el máximo es el anterior
            if (low == 0) {
                dta->current_slot_id = MAX_SLOTS_CYCLIC - 1;
            } else {
                dta->current_slot_id = low - 1;
            }
        }
    }
    dta->current_id = read_id(dta->current_slot_id);
    read_eeprom_blocking(calc_cyclic_addr(dta->current_slot_id), (uint8_t*)&p_data_sv, sizeof(sys_cfg_save_t));
}

/********************** end of file ******************************************/
