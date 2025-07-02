{
  "graph": {
    "cells": [
      {
        "position": {
          "x": 0,
          "y": 0
        },
        "size": {
          "height": 10,
          "width": 10
        },
        "angle": 0,
        "type": "Statechart",
        "id": "78749915-0da0-40a2-862f-9e8d94c7c68e",
        "linkable": false,
        "z": 1,
        "attrs": {
          "name": {
            "text": "Persianas Copy Copy Export"
          },
          "specification": {
            "text": "@EventDriven\n@SuperSteps(no)\n\ninterface: \n    in event Enter\n    in event Escape\n    in event Next\n    var speed: integer\n    var hour_d: integer\n    var hour_u: integer\n    var minutes_d: integer\n    var minutes_u: integer\n    var open_hour_d: integer\n    var open_hour_u: integer\n    var open_minutes_d: integer\n    var open_minutes_u: integer\n    var close_hour_d: integer\n    var close_hour_u: integer\n    var close_minutes_d: integer\n    var close_minutes_u: integer\n    var timer: integer\n    var mem_empty: boolean = true\n    \n    in event OP_DISPLAY_MAIN\n    in event OP_DISPLAY_MENU1_MOTOR\n    in event OP_DISPLAY_MENU2_POWER\n    in event OP_DISPLAY_MENU2_SPEED\n    in event OP_DISPLAY_MENU2_SPIN\n    in event OP_DISPLAY_POWER_ON\n    in event OP_DISPLAY_POWER_OFF\n    in event OP_DISPLAY_SPEED\n    in event OP_DISPLAY_SPEED_UP\n    in event OP_DISPLAY_SPIN_LEFT\n    in event OP_DISPLAY_SPIN_RIGHT\n    in event OP_SET_POWER_ON\n    in event OP_SET_POWER_OFF\n    in event OP_SET_SPEED\n    in event OP_SET_SPIN_LEFT\n    in event OP_SET_SPIN_RIGHT\n    in event OP_TIMER_SET\n    in event OP_TIMER_DOWN\n    in event OP_DISPLAY_VARIABLE_SAVED\n"
          }
        }
      },
      {
        "type": "State",
        "position": {
          "x": -7365,
          "y": -2006
        },
        "size": {
          "height": 1459,
          "width": 8022
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "z": 478,
        "id": "3cfb7f52-da5c-4527-9e83-7a3cc84d8f3b",
        "embeds": [
          "8313cc69-3032-4ffe-993b-081fc214de10",
          "fcf4dc95-69ab-40a9-8413-2560d9b32679",
          "103ab626-ad36-436b-bde4-c0659546e60a"
        ],
        "attrs": {
          "name": {
            "text": "State",
            "fontSize": 12
          }
        }
      },
      {
        "type": "Region",
        "position": {
          "x": -7344,
          "y": -1984.2083320617676
        },
        "size": {
          "height": 1436.2083320617676,
          "width": 458.95975397780455
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "parent": "3cfb7f52-da5c-4527-9e83-7a3cc84d8f3b",
        "z": 479,
        "id": "8313cc69-3032-4ffe-993b-081fc214de10",
        "embeds": [
          "1111c3e7-3ee1-4c5e-aca4-70e35689c1c3",
          "b91056f1-4f2f-4e9e-b3db-b59c173cb553",
          "945205d4-71d1-411e-ab20-25210692299e"
        ],
        "attrs": {
          "name": {
            "text": "Sensors"
          }
        }
      },
      {
        "type": "Region",
        "position": {
          "x": -6885.040246022196,
          "y": -1984
        },
        "size": {
          "height": 1436,
          "width": 6790
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "parent": "3cfb7f52-da5c-4527-9e83-7a3cc84d8f3b",
        "z": 641,
        "id": "fcf4dc95-69ab-40a9-8413-2560d9b32679",
        "embeds": [
          "a801054b-3095-4a99-b0d0-d656408296e2",
          "d28b0dd9-c63d-47df-9f34-8c527bc0d329",
          "c18563a1-264d-4034-b2f8-2d5f697e4413",
          "3a39ce94-0243-4aaa-8e41-6185fb9b8119",
          "d19d7b46-5fa7-4452-83db-0fd04d039216",
          "2f2afba0-6fdd-4bff-8d99-32d8bbf3b664",
          "de06f673-8dda-41d5-8720-2761ce0ab346",
          "cc5371b2-291b-4131-b280-4e02cbc4f1ad"
        ],
        "attrs": {
          "name": {
            "text": "System"
          }
        }
      },
      {
        "type": "Choice",
        "position": {
          "x": -3678.890172168068,
          "y": -1805.4166641235352
        },
        "size": {
          "width": 15,
          "height": 15
        },
        "angle": 0,
        "fixedRatio": true,
        "embedable": false,
        "linkable": true,
        "parent": "fcf4dc95-69ab-40a9-8413-2560d9b32679",
        "z": 642,
        "id": "d19d7b46-5fa7-4452-83db-0fd04d039216",
        "attrs": {}
      },
      {
        "type": "State",
        "position": {
          "x": -6768.1909134829675,
          "y": -1450.2083320617676
        },
        "size": {
          "height": 838,
          "width": 4099
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "parent": "fcf4dc95-69ab-40a9-8413-2560d9b32679",
        "z": 645,
        "id": "2f2afba0-6fdd-4bff-8d99-32d8bbf3b664",
        "embeds": [
          "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d"
        ],
        "attrs": {
          "name": {
            "text": "SET_UP",
            "fontSize": 12
          }
        }
      },
      {
        "type": "Transition",
        "source": {
          "id": "d19d7b46-5fa7-4452-83db-0fd04d039216"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 412,
              "dy": 14.6666259765625
            },
            "name": "topLeft"
          },
          "id": "2f2afba0-6fdd-4bff-8d99-32d8bbf3b664",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "fcf4dc95-69ab-40a9-8413-2560d9b32679",
        "z": 679,
        "id": "3a39ce94-0243-4aaa-8e41-6185fb9b8119",
        "attrs": {}
      },
      {
        "type": "Entry",
        "position": {
          "x": -3419.2033724411212,
          "y": -2252
        },
        "size": {
          "height": 18,
          "width": 18
        },
        "angle": 0,
        "entryKind": "Initial",
        "fixedRatio": true,
        "embedable": false,
        "linkable": true,
        "z": 680,
        "id": "e4f37b5b-3c0f-4de3-8cc7-d1a2c3e08676",
        "embeds": [
          "f106206b-8dba-4267-ab30-1e576f81f136"
        ],
        "attrs": {}
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": -3419.2033724411212,
          "y": -2237
        },
        "parent": "e4f37b5b-3c0f-4de3-8cc7-d1a2c3e08676",
        "z": 681,
        "id": "f106206b-8dba-4267-ab30-1e576f81f136",
        "attrs": {
          "label": {
            "refX": "50%",
            "refY": "50%",
            "textVerticalAnchor": "middle",
            "textAnchor": "middle"
          }
        }
      },
      {
        "type": "Transition",
        "source": {
          "id": "e4f37b5b-3c0f-4de3-8cc7-d1a2c3e08676"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 3729,
              "dy": 14
            },
            "name": "topLeft"
          },
          "id": "3cfb7f52-da5c-4527-9e83-7a3cc84d8f3b",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "z": 682,
        "id": "539bc2be-59cd-438a-ade0-d4d76b014d14",
        "attrs": {}
      },
      {
        "type": "Region",
        "position": {
          "x": -95.04024602219579,
          "y": -1984.2083320617676
        },
        "size": {
          "height": 1436.2083320617676,
          "width": 771.0402460221956
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "parent": "3cfb7f52-da5c-4527-9e83-7a3cc84d8f3b",
        "z": 690,
        "id": "103ab626-ad36-436b-bde4-c0659546e60a",
        "embeds": [
          "47c8660c-cc52-4416-8a28-4ece0766cb7c",
          "109a28d4-cb23-4e88-8e17-19f57e075383",
          "7af180cc-b4e0-4784-ba28-06aaa3e4d940"
        ],
        "attrs": {
          "name": {
            "text": "Actuators"
          }
        }
      },
      {
        "type": "Entry",
        "position": {
          "x": -7230,
          "y": -1917.6249961853027
        },
        "size": {
          "height": 18,
          "width": 18
        },
        "angle": 0,
        "entryKind": "Initial",
        "fixedRatio": true,
        "embedable": false,
        "linkable": true,
        "parent": "8313cc69-3032-4ffe-993b-081fc214de10",
        "z": 713,
        "id": "b91056f1-4f2f-4e9e-b3db-b59c173cb553",
        "embeds": [
          "b5d75739-28bf-4734-b7d5-04d5435f6beb"
        ],
        "attrs": {}
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": -7230,
          "y": -1902.6249961853027
        },
        "parent": "b91056f1-4f2f-4e9e-b3db-b59c173cb553",
        "z": 714,
        "id": "b5d75739-28bf-4734-b7d5-04d5435f6beb",
        "attrs": {
          "label": {
            "refX": "50%",
            "refY": "50%",
            "textVerticalAnchor": "middle",
            "textAnchor": "middle"
          }
        }
      },
      {
        "type": "State",
        "position": {
          "x": -7143,
          "y": -1850.6249961853027
        },
        "size": {
          "height": 60,
          "width": 60
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "parent": "8313cc69-3032-4ffe-993b-081fc214de10",
        "z": 716,
        "id": "945205d4-71d1-411e-ab20-25210692299e",
        "attrs": {
          "name": {
            "text": "Stat",
            "fontSize": 12
          }
        }
      },
      {
        "type": "Transition",
        "source": {
          "id": "b91056f1-4f2f-4e9e-b3db-b59c173cb553"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 20,
              "dy": 37.6666259765625
            },
            "name": "topLeft"
          },
          "id": "945205d4-71d1-411e-ab20-25210692299e",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "8313cc69-3032-4ffe-993b-081fc214de10",
        "z": 717,
        "id": "1111c3e7-3ee1-4c5e-aca4-70e35689c1c3",
        "attrs": {}
      },
      {
        "type": "State",
        "position": {
          "x": 1239.034758780741,
          "y": -1576
        },
        "size": {
          "height": 60,
          "width": 60
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "parent": "103ab626-ad36-436b-bde4-c0659546e60a",
        "z": 718,
        "id": "109a28d4-cb23-4e88-8e17-19f57e075383",
        "attrs": {
          "name": {
            "text": "State",
            "fontSize": 12
          }
        }
      },
      {
        "type": "Entry",
        "position": {
          "x": 1166.034758780741,
          "y": -1741
        },
        "size": {
          "height": 18,
          "width": 18
        },
        "angle": 0,
        "entryKind": "Initial",
        "fixedRatio": true,
        "embedable": false,
        "linkable": true,
        "parent": "103ab626-ad36-436b-bde4-c0659546e60a",
        "z": 720,
        "id": "7af180cc-b4e0-4784-ba28-06aaa3e4d940",
        "embeds": [
          "df11d85c-190d-49d9-8492-d728456067e6"
        ],
        "attrs": {}
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": 1166.034758780741,
          "y": -1726
        },
        "parent": "7af180cc-b4e0-4784-ba28-06aaa3e4d940",
        "z": 721,
        "id": "df11d85c-190d-49d9-8492-d728456067e6",
        "attrs": {
          "label": {
            "refX": "50%",
            "refY": "50%",
            "textVerticalAnchor": "middle",
            "textAnchor": "middle"
          }
        }
      },
      {
        "type": "Transition",
        "source": {
          "id": "7af180cc-b4e0-4784-ba28-06aaa3e4d940"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 37.5125846862793,
              "dy": 39.6666259765625
            },
            "name": "topLeft"
          },
          "id": "109a28d4-cb23-4e88-8e17-19f57e075383",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "103ab626-ad36-436b-bde4-c0659546e60a",
        "z": 722,
        "id": "47c8660c-cc52-4416-8a28-4ece0766cb7c",
        "attrs": {}
      },
      {
        "type": "Entry",
        "position": {
          "x": -4067.465241219259,
          "y": -1899.4166641235352
        },
        "size": {
          "height": 18,
          "width": 18
        },
        "angle": 0,
        "entryKind": "Initial",
        "fixedRatio": true,
        "embedable": false,
        "linkable": true,
        "parent": "fcf4dc95-69ab-40a9-8413-2560d9b32679",
        "z": 723,
        "id": "de06f673-8dda-41d5-8720-2761ce0ab346",
        "embeds": [
          "2736c072-882f-43b6-ba9b-e037f4540cda"
        ],
        "attrs": {}
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": -4067.465241219259,
          "y": -1884.4166641235352
        },
        "parent": "de06f673-8dda-41d5-8720-2761ce0ab346",
        "z": 724,
        "id": "2736c072-882f-43b6-ba9b-e037f4540cda",
        "attrs": {
          "label": {
            "refX": "50%",
            "refY": "50%",
            "textVerticalAnchor": "middle",
            "textAnchor": "middle"
          }
        }
      },
      {
        "type": "Transition",
        "source": {
          "id": "de06f673-8dda-41d5-8720-2761ce0ab346"
        },
        "target": {
          "id": "d19d7b46-5fa7-4452-83db-0fd04d039216"
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "fcf4dc95-69ab-40a9-8413-2560d9b32679",
        "z": 725,
        "id": "c18563a1-264d-4034-b2f8-2d5f697e4413",
        "attrs": {}
      },
      {
        "type": "Region",
        "position": {
          "x": -6767.1909134829675,
          "y": -1428.4166641235352
        },
        "size": {
          "height": 815.2083320617676,
          "width": 4097
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "z": 856,
        "id": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "embeds": [
          "ddd404ed-a408-4de2-8d41-cbf79e5011ab",
          "83dece5f-95dc-42c8-b225-560bea8d7a3a",
          "af5862aa-42db-48ff-aa26-48cc21345d48",
          "682610d7-81a1-479b-b493-4b394648f46b",
          "1b3cdcb5-a178-4649-8840-5ca74fd40ce3",
          "34aebcea-297d-4d3c-bfc5-10f502ad167c",
          "f9a590d6-6ba8-495a-bf4b-18c6d12a7744",
          "d6e6ad74-7ad9-49d7-863d-290ab53f15c2",
          "22bc8093-9dd4-495d-a5ae-df8b128638ba",
          "798214af-9db6-4c44-bc0f-0bb9883e5bb8",
          "76cb4bf8-fe57-4e09-9ec7-db9acf06233d",
          "b4483ac9-b5b3-4210-be0c-28c78797530e",
          "dd8f0cc5-e342-4ccd-b5ae-dfa1ae96230e",
          "09f10164-9828-43ee-9b98-0fff969a86f5",
          "29444d94-1153-44d6-9a5e-28d514bef020",
          "60336102-2887-4f25-b80e-446173d2f255",
          "15312cb2-d4f5-47c9-b1fc-870e1d676851",
          "527a6928-6946-4e85-8230-71f526a750d2",
          "aa1824ff-db6a-4877-9bc0-7ee36bd23df8",
          "90c7cf94-f0e0-4383-8941-d20861ed4abd",
          "9ea5e691-edd6-4be0-92cf-1b278eb56d26",
          "988c73ca-f22e-45d5-9ed8-4cef6030e24e",
          "faba7475-c979-4669-8e8b-c067175a4c94",
          "85abb698-b083-470e-b932-d0cea12e6ac6",
          "10105e2e-3d4c-4dca-ad4e-f25be3928ddd",
          "4b0bab63-e2f5-4d9c-a5f8-ec7272b5ad2d",
          "fccfd330-0f21-4239-a8da-7ba05e4747e4",
          "5f5bdf47-c9b9-46c1-8920-779ac2c8c1f4",
          "6d7cf6db-e720-4170-8880-2a001d4f144a",
          "fab2319f-ff23-4b7e-adba-839db6b7f1ad",
          "c2e07b75-8159-458e-a337-9646199e350c",
          "91eda6c2-32c1-4921-9c65-8140ab342690",
          "d1d650ee-6343-47ef-a2ba-bb818fdec6ab",
          "009339c5-38cc-494b-9317-318f535ffa6e",
          "50d1728c-8187-4b4b-9d8d-2b7a385f1798",
          "1b4f0010-512c-43c1-94fc-5120f5fd8bf2",
          "63ffbe75-37e0-4e2d-ae54-9f6df1826d3d",
          "4fe1e069-f6f0-4988-98c8-02144affcae6",
          "de3f5b70-e88e-4bd0-9026-134b9f9f5838",
          "d4407a33-cc4c-4625-a2ca-5a89030f5333",
          "02efecec-77a2-4a51-9984-68a5c731e1e6",
          "8bad82b9-f363-420a-b675-e07a77175295",
          "a8ae3f47-04bb-4f63-aea9-eb180e4eac99",
          "7f670e3d-a17f-4e23-86ee-8d1d98efcadd",
          "b663631b-d56d-45ae-a26c-101d2e8d3dbd",
          "8d620304-3b92-4db2-8358-fc19c564fb95",
          "60387e87-a2c2-44f4-ad47-46ae944a142d",
          "c656703e-4518-4192-b296-75cb2c84addb",
          "576a25de-512c-4eb1-a9af-ec7aaf168af1",
          "043477b0-85fb-4004-ad27-0f5282b74e89",
          "af2f1df4-3d8e-4b3e-afe5-aedd806d6df5"
        ],
        "parent": "2f2afba0-6fdd-4bff-8d99-32d8bbf3b664",
        "attrs": {}
      },
      {
        "type": "Entry",
        "position": {
          "x": -6659.1909134829675,
          "y": -1399.2083320617676
        },
        "size": {
          "height": 18,
          "width": 18
        },
        "angle": 0,
        "entryKind": "Initial",
        "fixedRatio": true,
        "embedable": false,
        "linkable": true,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "z": 857,
        "id": "009339c5-38cc-494b-9317-318f535ffa6e",
        "embeds": [
          "50be906a-4eeb-48a2-8ff0-09dd33b7174c"
        ],
        "attrs": {}
      },
      {
        "type": "State",
        "position": {
          "x": -6670.1909134829675,
          "y": -1202.2083320617676
        },
        "size": {
          "height": 78,
          "width": 206
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "z": 858,
        "id": "50d1728c-8187-4b4b-9d8d-2b7a385f1798",
        "embeds": [
          "086147b7-9da4-40a4-9f2e-f62ae8fe2803"
        ],
        "attrs": {
          "name": {
            "text": "ST_CONF_TIME_SELECT_HOUR_DEC",
            "fontSize": 12
          },
          "specification": {
            "text": "entry[(hour_d==2) && (hour_u>3)]/hour_u=3\nentry[hour_d==3]/hour_d=0"
          }
        }
      },
      {
        "type": "State",
        "position": {
          "x": -6427.1909134829675,
          "y": -1202.2083320617676
        },
        "size": {
          "height": 76,
          "width": 205
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "z": 859,
        "id": "1b4f0010-512c-43c1-94fc-5120f5fd8bf2",
        "embeds": [
          "12f61339-b63b-473c-b957-9de16936af43"
        ],
        "attrs": {
          "name": {
            "text": "ST_CONF_TIME_SELECT_HOUR_UN",
            "fontSize": 12
          },
          "specification": {
            "text": "entry[(hour_d==2) && (hour_u==4)]/hour_u=0\nentry[hour_u==10]/hour_u=0"
          }
        }
      },
      {
        "type": "State",
        "position": {
          "x": -6513.1909134829675,
          "y": -1349.6041660308838
        },
        "size": {
          "height": 60,
          "width": 672
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "z": 860,
        "id": "63ffbe75-37e0-4e2d-ae54-9f6df1826d3d",
        "attrs": {
          "name": {
            "text": "ST_CONF_TIME",
            "fontSize": 12
          }
        }
      },
      {
        "type": "State",
        "position": {
          "x": -5387.1909134829675,
          "y": -1347.4166641235352
        },
        "size": {
          "height": 60,
          "width": 971
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "z": 866,
        "id": "4fe1e069-f6f0-4988-98c8-02144affcae6",
        "attrs": {
          "name": {
            "text": "ST_CONF_OPEN_TIME",
            "fontSize": 12
          }
        }
      },
      {
        "type": "State",
        "position": {
          "x": -6169.965241219259,
          "y": -1202.2083320617676
        },
        "size": {
          "height": 60,
          "width": 217
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "z": 868,
        "id": "de3f5b70-e88e-4bd0-9026-134b9f9f5838",
        "embeds": [
          "269f4c47-45f8-45f4-af24-564f2755b3bc"
        ],
        "attrs": {
          "name": {
            "text": "ST_CONF_TIME_SELECT_MINUTES_DEC",
            "fontSize": 12
          },
          "specification": {
            "text": "entry[minutes_d==6]/minutes_d=0"
          }
        }
      },
      {
        "type": "State",
        "position": {
          "x": -5909.1909134829675,
          "y": -1202.2083320617676
        },
        "size": {
          "height": 60,
          "width": 226.33334350585938
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "z": 871,
        "id": "d4407a33-cc4c-4625-a2ca-5a89030f5333",
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "embeds": [
          "f64829c2-525f-4376-b320-649640bc51ea"
        ],
        "attrs": {
          "name": {
            "text": "ST_CONF_TIME_SELECT_MINUTES_UN",
            "fontSize": 12
          },
          "specification": {
            "text": "entry[minutes_u==10]/minutes_u=0"
          }
        }
      },
      {
        "type": "State",
        "position": {
          "x": -5546.416585746676,
          "y": -1190.4166641235352
        },
        "size": {
          "height": 102,
          "width": 227
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "z": 875,
        "id": "02efecec-77a2-4a51-9984-68a5c731e1e6",
        "embeds": [
          "1c0e1b65-b5ed-4ee6-8aa8-e4086d14a4f4"
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {
          "name": {
            "text": "ST_CONF_OPEN_TIME_SELECT_HOUR_DEC",
            "fontSize": 12
          },
          "specification": {
            "text": "entry[(open_hour_d==2) && (open_hour_u>3)]/open_hour_u=3\nentry[open_hour_d==3]/open_hour_d=0"
          }
        }
      },
      {
        "type": "State",
        "position": {
          "x": -5284.416585746676,
          "y": -1190.4166641235352
        },
        "size": {
          "height": 104,
          "width": 227
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "z": 876,
        "id": "8bad82b9-f363-420a-b675-e07a77175295",
        "embeds": [
          "c29780fb-5ffa-45f8-80e2-8c03d6869b27"
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {
          "name": {
            "text": "ST_CONF_OPEN_TIME_SELECT_HOUR_UN",
            "fontSize": 12
          },
          "specification": {
            "text": "entry[(open_hour_d==2) && (open_hour_u==4)]/open_hour_u=0\nentry[open_hour_u==10]/open_hour_u=0"
          }
        }
      },
      {
        "type": "State",
        "position": {
          "x": -4942.965241219259,
          "y": -1183
        },
        "size": {
          "height": 73,
          "width": 246
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "z": 878,
        "id": "a8ae3f47-04bb-4f63-aea9-eb180e4eac99",
        "embeds": [
          "cf5c6595-aff1-4a03-8580-7ad4b42f9d22"
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {
          "name": {
            "text": "ST_CONF_OPEN_TIME_SELECT_MINUTES_DEC",
            "fontSize": 12
          },
          "specification": {
            "text": "entry[open_minutes_d==6]/open_minutes_d=0"
          }
        }
      },
      {
        "type": "State",
        "position": {
          "x": -4588.965241219259,
          "y": -1174
        },
        "size": {
          "height": 64,
          "width": 242
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "z": 880,
        "id": "7f670e3d-a17f-4e23-86ee-8d1d98efcadd",
        "embeds": [
          "ee6fd568-db37-4cbb-8e9e-2cdee3001490"
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {
          "name": {
            "text": "ST_CONF_OPEN_TIME_SELECT_MINUTES_UN",
            "fontSize": 12
          },
          "specification": {
            "text": "entry[open_minutes_u==10]/open_minutes_u=0"
          }
        }
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": -6659.1909134829675,
          "y": -1384.2083320617676
        },
        "parent": "009339c5-38cc-494b-9317-318f535ffa6e",
        "z": 891,
        "id": "50be906a-4eeb-48a2-8ff0-09dd33b7174c",
        "attrs": {
          "label": {
            "refX": "50%",
            "refY": "50%",
            "textVerticalAnchor": "middle",
            "textAnchor": "middle"
          }
        }
      },
      {
        "type": "Transition",
        "source": {
          "id": "a8ae3f47-04bb-4f63-aea9-eb180e4eac99"
        },
        "target": {
          "id": "7f670e3d-a17f-4e23-86ee-8d1d98efcadd"
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "z": 892,
        "id": "90c7cf94-f0e0-4383-8941-d20861ed4abd",
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "8bad82b9-f363-420a-b675-e07a77175295"
        },
        "target": {
          "id": "a8ae3f47-04bb-4f63-aea9-eb180e4eac99"
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "z": 892,
        "id": "9ea5e691-edd6-4be0-92cf-1b278eb56d26",
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "02efecec-77a2-4a51-9984-68a5c731e1e6"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 59.2255859375,
              "dy": 44.875
            },
            "name": "topLeft"
          },
          "id": "8bad82b9-f363-420a-b675-e07a77175295",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "z": 892,
        "id": "988c73ca-f22e-45d5-9ed8-4cef6030e24e",
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "de3f5b70-e88e-4bd0-9026-134b9f9f5838"
        },
        "target": {
          "id": "d4407a33-cc4c-4625-a2ca-5a89030f5333"
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "z": 892,
        "id": "10105e2e-3d4c-4dca-ad4e-f25be3928ddd",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "7f670e3d-a17f-4e23-86ee-8d1d98efcadd"
        },
        "target": {
          "id": "4fe1e069-f6f0-4988-98c8-02144affcae6",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 890.2255859375,
              "dy": 45.4166259765625,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Escape"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "29444d94-1153-44d6-9a5e-28d514bef020",
        "z": 892,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "a8ae3f47-04bb-4f63-aea9-eb180e4eac99"
        },
        "target": {
          "id": "4fe1e069-f6f0-4988-98c8-02144affcae6",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 555.2255859375,
              "dy": 31.4166259765625,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Escape"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "60336102-2887-4f25-b80e-446173d2f255",
        "z": 892,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "8bad82b9-f363-420a-b675-e07a77175295"
        },
        "target": {
          "id": "4fe1e069-f6f0-4988-98c8-02144affcae6",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 221.2255859375,
              "dy": 31.4166259765625,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Escape"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "15312cb2-d4f5-47c9-b1fc-870e1d676851",
        "z": 892,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "02efecec-77a2-4a51-9984-68a5c731e1e6"
        },
        "target": {
          "id": "4fe1e069-f6f0-4988-98c8-02144affcae6",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 21.2255859375,
              "dy": 49.4166259765625,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Escape"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "527a6928-6946-4e85-8230-71f526a750d2",
        "z": 892,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "4fe1e069-f6f0-4988-98c8-02144affcae6"
        },
        "target": {
          "id": "02efecec-77a2-4a51-9984-68a5c731e1e6",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 26.451171875,
              "dy": 14.75,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Enter"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "aa1824ff-db6a-4877-9bc0-7ee36bd23df8",
        "z": 892,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "d4407a33-cc4c-4625-a2ca-5a89030f5333"
        },
        "target": {
          "id": "63ffbe75-37e0-4e2d-ae54-9f6df1826d3d",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 652.2255859375,
              "dy": 46.6041259765625,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Escape"
              }
            },
            "position": {
              "distance": 0.500000335242877,
              "offset": -32,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "85abb698-b083-470e-b932-d0cea12e6ac6",
        "z": 892,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "de3f5b70-e88e-4bd0-9026-134b9f9f5838"
        },
        "target": {
          "id": "63ffbe75-37e0-4e2d-ae54-9f6df1826d3d",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 453.2255859375,
              "dy": 33.6041259765625,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Escape"
              }
            },
            "position": {
              "distance": 0.534329205823035,
              "offset": -29,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "4b0bab63-e2f5-4d9c-a5f8-ec7272b5ad2d",
        "z": 892,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "63ffbe75-37e0-4e2d-ae54-9f6df1826d3d"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 33,
              "dy": 9
            },
            "name": "topLeft"
          },
          "id": "4fe1e069-f6f0-4988-98c8-02144affcae6",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "z": 892,
        "id": "5f5bdf47-c9b9-46c1-8920-779ac2c8c1f4",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "1b4f0010-512c-43c1-94fc-5120f5fd8bf2"
        },
        "target": {
          "id": "de3f5b70-e88e-4bd0-9026-134b9f9f5838"
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "z": 892,
        "id": "fccfd330-0f21-4239-a8da-7ba05e4747e4",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "1b4f0010-512c-43c1-94fc-5120f5fd8bf2"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 127.2255859375,
              "dy": 34.6041259765625
            },
            "name": "topLeft"
          },
          "id": "63ffbe75-37e0-4e2d-ae54-9f6df1826d3d",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Escape"
              }
            },
            "position": {
              "distance": 0.534329205823035,
              "offset": 24,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "z": 892,
        "id": "c2e07b75-8159-458e-a337-9646199e350c",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "d4407a33-cc4c-4625-a2ca-5a89030f5333"
        },
        "target": {
          "id": "50d1728c-8187-4b4b-9d8d-2b7a385f1798",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 1.2255859375,
              "dy": 38.2083740234375,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "faba7475-c979-4669-8e8b-c067175a4c94",
        "z": 892,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "vertices": [
          {
            "x": -5662.965241219259,
            "y": -1180
          },
          {
            "x": -5662.965241219259,
            "y": -1084
          },
          {
            "x": -6141.965241219259,
            "y": -1058
          },
          {
            "x": -6697.965241219259,
            "y": -1084
          }
        ],
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "63ffbe75-37e0-4e2d-ae54-9f6df1826d3d"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 62.2255859375,
              "dy": 26.875
            },
            "name": "topLeft"
          },
          "id": "50d1728c-8187-4b4b-9d8d-2b7a385f1798",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Enter"
              }
            },
            "position": {
              "distance": 0.48957637668049536,
              "offset": 9,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "vertices": [
          {
            "x": -6495.965241219259,
            "y": -1269
          },
          {
            "x": -6535.965241219259,
            "y": -1249
          }
        ],
        "z": 892,
        "id": "91eda6c2-32c1-4921-9c65-8140ab342690",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "50d1728c-8187-4b4b-9d8d-2b7a385f1798"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 31.2255859375,
              "dy": 62.9375
            },
            "name": "topLeft"
          },
          "id": "63ffbe75-37e0-4e2d-ae54-9f6df1826d3d",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Escape"
              }
            },
            "position": {
              "distance": 0.4605280744953226,
              "offset": 25,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "vertices": [
          {
            "x": -6521,
            "y": -1229
          }
        ],
        "z": 892,
        "id": "6d7cf6db-e720-4170-8880-2a001d4f144a",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "50d1728c-8187-4b4b-9d8d-2b7a385f1798"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 59.2255859375,
              "dy": 44.875
            },
            "name": "topLeft"
          },
          "id": "1b4f0010-512c-43c1-94fc-5120f5fd8bf2",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "z": 892,
        "id": "fab2319f-ff23-4b7e-adba-839db6b7f1ad",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "009339c5-38cc-494b-9317-318f535ffa6e"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 20,
              "dy": 35.111083984375
            },
            "name": "topLeft"
          },
          "id": "63ffbe75-37e0-4e2d-ae54-9f6df1826d3d",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "z": 892,
        "id": "d1d650ee-6343-47ef-a2ba-bb818fdec6ab",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "50d1728c-8187-4b4b-9d8d-2b7a385f1798"
        },
        "target": {
          "id": "50d1728c-8187-4b4b-9d8d-2b7a385f1798",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 163.2255859375,
              "dy": 54.2083740234375,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Enter/hour_d = (hour_d%3)+1"
              }
            },
            "position": {
              "distance": 0.48703613395067036,
              "offset": 18,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "086147b7-9da4-40a4-9f2e-f62ae8fe2803",
        "z": 892,
        "parent": "50d1728c-8187-4b4b-9d8d-2b7a385f1798",
        "vertices": [
          {
            "x": -6648.965241219259,
            "y": -1099
          }
        ],
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "1b4f0010-512c-43c1-94fc-5120f5fd8bf2"
        },
        "target": {
          "id": "1b4f0010-512c-43c1-94fc-5120f5fd8bf2",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 181.2255859375,
              "dy": 54.2083740234375,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Enter/hour_u = (hour_u%10)+1"
              }
            },
            "position": {
              "distance": 0.46830008684137703,
              "offset": 17,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "12f61339-b63b-473c-b957-9de16936af43",
        "z": 893,
        "parent": "1b4f0010-512c-43c1-94fc-5120f5fd8bf2",
        "vertices": [
          {
            "x": -6401.965241219259,
            "y": -1108
          }
        ],
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "de3f5b70-e88e-4bd0-9026-134b9f9f5838"
        },
        "target": {
          "id": "de3f5b70-e88e-4bd0-9026-134b9f9f5838",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 201,
              "dy": 52.2083740234375,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Enter/minutes_d = (minutes_d%6)+1"
              }
            },
            "position": {
              "distance": 0.4902525276691886,
              "offset": 15,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "269f4c47-45f8-45f4-af24-564f2755b3bc",
        "z": 894,
        "parent": "de3f5b70-e88e-4bd0-9026-134b9f9f5838",
        "vertices": [
          {
            "x": -6152.965241219259,
            "y": -1125
          }
        ],
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "d4407a33-cc4c-4625-a2ca-5a89030f5333"
        },
        "target": {
          "id": "d4407a33-cc4c-4625-a2ca-5a89030f5333",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 202.2255859375,
              "dy": 56.2083740234375,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Enter/minutes_u = (minutes_u%10) + 1"
              }
            },
            "position": {
              "distance": 0.5090958187940914,
              "offset": 15,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "f64829c2-525f-4376-b320-649640bc51ea",
        "z": 895,
        "parent": "d4407a33-cc4c-4625-a2ca-5a89030f5333",
        "vertices": [
          {
            "x": -5895.965241219259,
            "y": -1123
          }
        ],
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "02efecec-77a2-4a51-9984-68a5c731e1e6"
        },
        "target": {
          "id": "02efecec-77a2-4a51-9984-68a5c731e1e6",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 163.2255859375,
              "dy": 54.2083740234375,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Enter/open_hour_d = (open_hour_d%3)+1"
              }
            },
            "position": {
              "distance": 0.48703613395067036,
              "offset": 18,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "1c0e1b65-b5ed-4ee6-8aa8-e4086d14a4f4",
        "z": 896,
        "vertices": [
          {
            "x": -5503.04,
            "y": -1073
          }
        ],
        "parent": "02efecec-77a2-4a51-9984-68a5c731e1e6",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "8bad82b9-f363-420a-b675-e07a77175295"
        },
        "target": {
          "id": "8bad82b9-f363-420a-b675-e07a77175295",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 181.2255859375,
              "dy": 54.2083740234375,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Enter/open_hour_u = (open_hour_u%10)+1"
              }
            },
            "position": {
              "distance": 0.46830008684137703,
              "offset": 17,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "c29780fb-5ffa-45f8-80e2-8c03d6869b27",
        "z": 897,
        "vertices": [
          {
            "x": -5242.96,
            "y": -1049
          }
        ],
        "parent": "8bad82b9-f363-420a-b675-e07a77175295",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "a8ae3f47-04bb-4f63-aea9-eb180e4eac99"
        },
        "target": {
          "id": "a8ae3f47-04bb-4f63-aea9-eb180e4eac99",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 201,
              "dy": 52.2083740234375,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Enter/open_minutes_d = (open_minutes_d%6)+1"
              }
            },
            "position": {
              "distance": 0.4902525276691886,
              "offset": 15,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "cf5c6595-aff1-4a03-8580-7ad4b42f9d22",
        "z": 898,
        "vertices": [
          {
            "x": -4903.04,
            "y": -1068
          }
        ],
        "parent": "a8ae3f47-04bb-4f63-aea9-eb180e4eac99",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "7f670e3d-a17f-4e23-86ee-8d1d98efcadd"
        },
        "target": {
          "id": "7f670e3d-a17f-4e23-86ee-8d1d98efcadd",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 202.2255859375,
              "dy": 56.2083740234375,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Enter/open_minutes_u = (open_minutes_u%10) + 1"
              }
            },
            "position": {
              "distance": 0.5090958187940914,
              "offset": 15,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "ee6fd568-db37-4cbb-8e9e-2cdee3001490",
        "z": 899,
        "vertices": [
          {
            "x": -4555.96,
            "y": -1069
          }
        ],
        "parent": "7f670e3d-a17f-4e23-86ee-8d1d98efcadd",
        "attrs": {}
      },
      {
        "type": "State",
        "position": {
          "x": -4047.965241219259,
          "y": -1352.4166641235352
        },
        "size": {
          "height": 60,
          "width": 971
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "z": 900,
        "id": "b663631b-d56d-45ae-a26c-101d2e8d3dbd",
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {
          "name": {
            "text": "ST_CONF_CLOSE_TIME",
            "fontSize": 12
          }
        }
      },
      {
        "type": "State",
        "position": {
          "x": -4207.1909134829675,
          "y": -1195.4166641235352
        },
        "size": {
          "height": 103,
          "width": 229
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "z": 901,
        "id": "8d620304-3b92-4db2-8358-fc19c564fb95",
        "embeds": [
          "a4cbb7e9-1365-4390-9e15-87a18dc09267"
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {
          "name": {
            "text": "ST_CONF_CLOSE_TIME_SELECT_HOUR_DEC",
            "fontSize": 12
          },
          "specification": {
            "text": "entry[(close_hour_d==2) && (close_hour_u>3)]/close_hour_u=3\nentry[close_hour_d==3]/close_hour_d=0"
          }
        }
      },
      {
        "type": "State",
        "position": {
          "x": -3603.7395689555506,
          "y": -1188
        },
        "size": {
          "height": 73,
          "width": 246
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "z": 903,
        "id": "60387e87-a2c2-44f4-ad47-46ae944a142d",
        "embeds": [
          "1a688d9b-86b4-4136-a093-28023035e0a7"
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {
          "name": {
            "text": "ST_CONF_CLOSE_TIME_SELECT_MINUTES_DEC",
            "fontSize": 12
          },
          "specification": {
            "text": "entry[close_minutes_d==6]/close_minutes_d=0"
          }
        }
      },
      {
        "type": "State",
        "position": {
          "x": -3249.7395689555506,
          "y": -1179
        },
        "size": {
          "height": 64,
          "width": 242
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "z": 904,
        "id": "c656703e-4518-4192-b296-75cb2c84addb",
        "embeds": [
          "1f7c4d31-9217-4752-a445-0b7c7e124ae1"
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {
          "name": {
            "text": "ST_CONF_CLOSE_TIME_SELECT_MINUTES_UN",
            "fontSize": 12
          },
          "specification": {
            "text": "entry[close_minutes_u==10]/close_minutes_u=0"
          }
        }
      },
      {
        "type": "Transition",
        "source": {
          "id": "b663631b-d56d-45ae-a26c-101d2e8d3dbd"
        },
        "target": {
          "id": "8d620304-3b92-4db2-8358-fc19c564fb95",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 26.451171875,
              "dy": 14.75,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Enter"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "09f10164-9828-43ee-9b98-0fff969a86f5",
        "z": 905,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "8d620304-3b92-4db2-8358-fc19c564fb95"
        },
        "target": {
          "id": "b663631b-d56d-45ae-a26c-101d2e8d3dbd",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 21.2255859375,
              "dy": 49.4166259765625,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Escape"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "dd8f0cc5-e342-4ccd-b5ae-dfa1ae96230e",
        "z": 906,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "60387e87-a2c2-44f4-ad47-46ae944a142d"
        },
        "target": {
          "id": "b663631b-d56d-45ae-a26c-101d2e8d3dbd",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 555.2255859375,
              "dy": 31.4166259765625,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Escape"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "b4483ac9-b5b3-4210-be0c-28c78797530e",
        "z": 908,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "c656703e-4518-4192-b296-75cb2c84addb"
        },
        "target": {
          "id": "b663631b-d56d-45ae-a26c-101d2e8d3dbd",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 890.2255859375,
              "dy": 45.4166259765625,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Escape"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "76cb4bf8-fe57-4e09-9ec7-db9acf06233d",
        "z": 909,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "60387e87-a2c2-44f4-ad47-46ae944a142d"
        },
        "target": {
          "id": "c656703e-4518-4192-b296-75cb2c84addb"
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "z": 912,
        "id": "798214af-9db6-4c44-bc0f-0bb9883e5bb8",
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "8d620304-3b92-4db2-8358-fc19c564fb95"
        },
        "target": {
          "id": "8d620304-3b92-4db2-8358-fc19c564fb95",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 163.2255859375,
              "dy": 54.2083740234375,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Enter/close_hour_d = (close_hour_d%3)+1"
              }
            },
            "position": {
              "distance": 0.48703613395067036,
              "offset": 18,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "a4cbb7e9-1365-4390-9e15-87a18dc09267",
        "z": 913,
        "vertices": [
          {
            "x": -4163.81,
            "y": -1079
          }
        ],
        "parent": "8d620304-3b92-4db2-8358-fc19c564fb95",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "60387e87-a2c2-44f4-ad47-46ae944a142d"
        },
        "target": {
          "id": "60387e87-a2c2-44f4-ad47-46ae944a142d",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 201,
              "dy": 52.2083740234375,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Enter/close_minutes_d = (close_minutes_d%6)+1"
              }
            },
            "position": {
              "distance": 0.4902525276691886,
              "offset": 15,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "1a688d9b-86b4-4136-a093-28023035e0a7",
        "z": 915,
        "vertices": [
          {
            "x": -3563.81,
            "y": -1078
          }
        ],
        "parent": "60387e87-a2c2-44f4-ad47-46ae944a142d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "c656703e-4518-4192-b296-75cb2c84addb"
        },
        "target": {
          "id": "c656703e-4518-4192-b296-75cb2c84addb",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 202.2255859375,
              "dy": 56.2083740234375,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Enter/close_minutes_u = (close_minutes_u%10) + 1"
              }
            },
            "position": {
              "distance": 0.5090958187940914,
              "offset": 15,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "1f7c4d31-9217-4752-a445-0b7c7e124ae1",
        "z": 916,
        "vertices": [
          {
            "x": -3216.73,
            "y": -1075
          }
        ],
        "parent": "c656703e-4518-4192-b296-75cb2c84addb",
        "attrs": {}
      },
      {
        "type": "State",
        "position": {
          "x": -1586.1909134829675,
          "y": -1376.6041660308838
        },
        "size": {
          "height": 521,
          "width": 1091
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "z": 917,
        "id": "cc5371b2-291b-4131-b280-4e02cbc4f1ad",
        "embeds": [
          "9ddd4f12-f6c6-440b-8cbf-66a99ffa14c1"
        ],
        "parent": "fcf4dc95-69ab-40a9-8413-2560d9b32679",
        "attrs": {
          "name": {
            "text": "NORMAL",
            "fontSize": 12
          }
        }
      },
      {
        "type": "Region",
        "position": {
          "x": -1585.1909134829675,
          "y": -1354.8124980926514
        },
        "size": {
          "height": 498.2083320617676,
          "width": 1089
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "parent": "cc5371b2-291b-4131-b280-4e02cbc4f1ad",
        "z": 918,
        "id": "9ddd4f12-f6c6-440b-8cbf-66a99ffa14c1",
        "embeds": [
          "4f385db5-42bf-4551-b8bd-c2f56c8acea8",
          "d5b15b74-5fec-42a6-b5ed-96efdd0727bb",
          "8df27b42-4cec-4c95-b2d5-02b4a158e91f",
          "a6ce0791-fdfe-4d84-bcab-2087a99f1083",
          "3b7bc201-b511-41fd-8c6d-b09331fc334e",
          "7c62766a-832b-48ac-9df1-697991eb1370",
          "ce7d1c0b-5842-453a-86cd-121cd5795b07",
          "d431ae35-dac9-419f-89bc-c0d7cccdc058",
          "4b223d2d-3984-4fbc-bd4b-66c88c58ed47",
          "1a531597-b982-4e14-b2db-5cc95c196fad",
          "9a958f9d-3954-427d-b969-129f7ebda32f",
          "c5419e76-78ce-4c98-afe0-ab91559b7d74",
          "1ca041a1-d9ab-4bd6-ba92-9a7f55699f61"
        ],
        "attrs": {}
      },
      {
        "type": "State",
        "position": {
          "x": -863.1909134829675,
          "y": -1259.6041660308838
        },
        "size": {
          "height": 60,
          "width": 60
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "parent": "9ddd4f12-f6c6-440b-8cbf-66a99ffa14c1",
        "z": 919,
        "id": "4b223d2d-3984-4fbc-bd4b-66c88c58ed47",
        "attrs": {
          "name": {
            "text": "ST_MAIN",
            "fontSize": 12
          }
        }
      },
      {
        "type": "Entry",
        "position": {
          "x": -871.1909134829675,
          "y": -1331.6041660308838
        },
        "size": {
          "height": 18,
          "width": 18
        },
        "angle": 0,
        "entryKind": "Initial",
        "fixedRatio": true,
        "embedable": false,
        "linkable": true,
        "parent": "9ddd4f12-f6c6-440b-8cbf-66a99ffa14c1",
        "z": 920,
        "id": "1a531597-b982-4e14-b2db-5cc95c196fad",
        "embeds": [
          "422b7e04-ce55-4ecd-8adb-fa8535280a6f"
        ],
        "attrs": {}
      },
      {
        "type": "State",
        "position": {
          "x": -915.1909134829675,
          "y": -1112.6041660308838
        },
        "size": {
          "height": 60,
          "width": 109
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "parent": "9ddd4f12-f6c6-440b-8cbf-66a99ffa14c1",
        "z": 921,
        "id": "9a958f9d-3954-427d-b969-129f7ebda32f",
        "attrs": {
          "name": {
            "text": "ST_MODE_TIME",
            "fontSize": 12
          }
        }
      },
      {
        "type": "State",
        "position": {
          "x": -1481.1909134829675,
          "y": -1097.6041660308838
        },
        "size": {
          "height": 60,
          "width": 102.375
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "parent": "9ddd4f12-f6c6-440b-8cbf-66a99ffa14c1",
        "z": 922,
        "id": "c5419e76-78ce-4c98-afe0-ab91559b7d74",
        "attrs": {
          "name": {
            "text": "ST_MODE_MANUAL",
            "fontSize": 12
          }
        }
      },
      {
        "type": "State",
        "position": {
          "x": -643.1909134829675,
          "y": -1110.6041660308838
        },
        "size": {
          "height": 62,
          "width": 111
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "parent": "9ddd4f12-f6c6-440b-8cbf-66a99ffa14c1",
        "z": 923,
        "id": "1ca041a1-d9ab-4bd6-ba92-9a7f55699f61",
        "attrs": {
          "name": {
            "text": "ST_MODE_LIGHT",
            "fontSize": 12
          }
        }
      },
      {
        "type": "NodeLabel",
        "label": true,
        "size": {
          "width": 15,
          "height": 15
        },
        "position": {
          "x": -871.1909134829675,
          "y": -1316.6041660308838
        },
        "parent": "1a531597-b982-4e14-b2db-5cc95c196fad",
        "z": 932,
        "id": "422b7e04-ce55-4ecd-8adb-fa8535280a6f",
        "attrs": {
          "label": {
            "refX": "50%",
            "refY": "50%",
            "textVerticalAnchor": "middle",
            "textAnchor": "middle"
          }
        }
      },
      {
        "type": "Transition",
        "source": {
          "id": "1ca041a1-d9ab-4bd6-ba92-9a7f55699f61"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 36.2255859375,
              "dy": 46.2083740234375
            },
            "name": "topLeft"
          },
          "id": "c5419e76-78ce-4c98-afe0-ab91559b7d74",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "9ddd4f12-f6c6-440b-8cbf-66a99ffa14c1",
        "vertices": [
          {
            "x": -1016.965241219259,
            "y": -983.3958339691162
          }
        ],
        "z": 933,
        "id": "4f385db5-42bf-4551-b8bd-c2f56c8acea8",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "c5419e76-78ce-4c98-afe0-ab91559b7d74"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 56,
              "dy": 29.6666259765625
            },
            "name": "topLeft"
          },
          "id": "9a958f9d-3954-427d-b969-129f7ebda32f",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "9ddd4f12-f6c6-440b-8cbf-66a99ffa14c1",
        "z": 933,
        "id": "7c62766a-832b-48ac-9df1-697991eb1370",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "9a958f9d-3954-427d-b969-129f7ebda32f"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 56,
              "dy": 27.6666259765625
            },
            "name": "topLeft"
          },
          "id": "1ca041a1-d9ab-4bd6-ba92-9a7f55699f61",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "9ddd4f12-f6c6-440b-8cbf-66a99ffa14c1",
        "z": 933,
        "id": "3b7bc201-b511-41fd-8c6d-b09331fc334e",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "1ca041a1-d9ab-4bd6-ba92-9a7f55699f61"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 42,
              "dy": 39
            },
            "name": "topLeft"
          },
          "id": "4b223d2d-3984-4fbc-bd4b-66c88c58ed47",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Escape"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "9ddd4f12-f6c6-440b-8cbf-66a99ffa14c1",
        "vertices": [
          {
            "x": -579.1909134829675,
            "y": -1220.6041660308838
          }
        ],
        "z": 933,
        "id": "d5b15b74-5fec-42a6-b5ed-96efdd0727bb",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "9a958f9d-3954-427d-b969-129f7ebda32f"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 26,
              "dy": 35
            },
            "name": "topLeft"
          },
          "id": "4b223d2d-3984-4fbc-bd4b-66c88c58ed47",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Escape"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "9ddd4f12-f6c6-440b-8cbf-66a99ffa14c1",
        "z": 933,
        "id": "8df27b42-4cec-4c95-b2d5-02b4a158e91f",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "c5419e76-78ce-4c98-afe0-ab91559b7d74"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 24,
              "dy": 43
            },
            "name": "topLeft"
          },
          "id": "4b223d2d-3984-4fbc-bd4b-66c88c58ed47",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Escape"
              }
            },
            "position": {
              "distance": 0.5087947942194684,
              "offset": 19,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "9ddd4f12-f6c6-440b-8cbf-66a99ffa14c1",
        "vertices": [
          {
            "x": -1204.1909134829675,
            "y": -1216.6041660308838
          }
        ],
        "z": 933,
        "id": "a6ce0791-fdfe-4d84-bcab-2087a99f1083",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "1a531597-b982-4e14-b2db-5cc95c196fad"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 23,
              "dy": 32.6666259765625
            },
            "name": "topLeft"
          },
          "id": "4b223d2d-3984-4fbc-bd4b-66c88c58ed47",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {},
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "9ddd4f12-f6c6-440b-8cbf-66a99ffa14c1",
        "z": 933,
        "id": "d431ae35-dac9-419f-89bc-c0d7cccdc058",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "4b223d2d-3984-4fbc-bd4b-66c88c58ed47"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 52,
              "dy": 32.6666259765625
            },
            "name": "topLeft"
          },
          "id": "c5419e76-78ce-4c98-afe0-ab91559b7d74",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Enter"
              }
            },
            "position": {
              "distance": 0.44522692641007894,
              "offset": 23,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "9ddd4f12-f6c6-440b-8cbf-66a99ffa14c1",
        "vertices": [
          {
            "x": -1527.1909134829675,
            "y": -1238.6041660308838
          }
        ],
        "z": 933,
        "id": "ce7d1c0b-5842-453a-86cd-121cd5795b07",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "2f2afba0-6fdd-4bff-8d99-32d8bbf3b664"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 386,
              "dy": 14
            },
            "name": "topLeft"
          },
          "id": "cc5371b2-291b-4131-b280-4e02cbc4f1ad",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Escape"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "fcf4dc95-69ab-40a9-8413-2560d9b32679",
        "z": 933,
        "id": "a801054b-3095-4a99-b0d0-d656408296e2",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "d19d7b46-5fa7-4452-83db-0fd04d039216"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 756,
              "dy": 17
            },
            "name": "topLeft"
          },
          "id": "cc5371b2-291b-4131-b280-4e02cbc4f1ad",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "[mem_empty == false]"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "fcf4dc95-69ab-40a9-8413-2560d9b32679",
        "vertices": [
          {
            "x": -3290.890172168068,
            "y": -1797.8866641235352
          },
          {
            "x": -2786.890172168068,
            "y": -1538.4166641235352
          }
        ],
        "z": 933,
        "id": "d28b0dd9-c63d-47df-9f34-8c527bc0d329",
        "attrs": {}
      },
      {
        "type": "State",
        "position": {
          "x": -2833.1909134829675,
          "y": -1349.6041660308838
        },
        "size": {
          "height": 60,
          "width": 135.36458587646484
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "z": 934,
        "id": "576a25de-512c-4eb1-a9af-ec7aaf168af1",
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {
          "name": {
            "text": "ST_SPEED_OPEN-CLOSE",
            "fontSize": 12
          }
        }
      },
      {
        "type": "Transition",
        "source": {
          "id": "576a25de-512c-4eb1-a9af-ec7aaf168af1"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 30.2255859375,
              "dy": 45.2083740234375
            },
            "name": "topLeft"
          },
          "id": "63ffbe75-37e0-4e2d-ae54-9f6df1826d3d",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "vertices": [
          {
            "x": -5343.965241219259,
            "y": -701
          },
          {
            "x": -6683.965241219259,
            "y": -701
          },
          {
            "x": -6727.965241219259,
            "y": -1289
          }
        ],
        "z": 935,
        "id": "22bc8093-9dd4-495d-a5ae-df8b128638ba",
        "attrs": {}
      },
      {
        "type": "State",
        "position": {
          "x": -2980.965241219259,
          "y": -1349.6041660308838
        },
        "size": {
          "height": 60,
          "width": 101
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "z": 936,
        "id": "043477b0-85fb-4004-ad27-0f5282b74e89",
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {
          "name": {
            "text": "ST_CONF_LIGHT",
            "fontSize": 12
          }
        }
      },
      {
        "type": "Transition",
        "source": {
          "id": "043477b0-85fb-4004-ad27-0f5282b74e89"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 38,
              "dy": 19.4285888671875
            },
            "name": "topLeft"
          },
          "id": "576a25de-512c-4eb1-a9af-ec7aaf168af1",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "z": 937,
        "id": "d6e6ad74-7ad9-49d7-863d-290ab53f15c2",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "4fe1e069-f6f0-4988-98c8-02144affcae6"
        },
        "target": {
          "id": "b663631b-d56d-45ae-a26c-101d2e8d3dbd",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 36.96533203125,
              "dy": 16.083251953125,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "f9a590d6-6ba8-495a-bf4b-18c6d12a7744",
        "z": 938,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "7f670e3d-a17f-4e23-86ee-8d1d98efcadd"
        },
        "target": {
          "id": "02efecec-77a2-4a51-9984-68a5c731e1e6",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 186.41650390625,
              "dy": 72.4166259765625,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "34aebcea-297d-4d3c-bfc5-10f502ad167c",
        "z": 939,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "vertices": [
          {
            "x": -4312,
            "y": -1141
          },
          {
            "x": -5588,
            "y": -989
          }
        ],
        "attrs": {}
      },
      {
        "type": "State",
        "position": {
          "x": -3919,
          "y": -1194
        },
        "size": {
          "height": 104,
          "width": 227
        },
        "angle": 0,
        "fixedRatio": false,
        "embedable": true,
        "linkable": true,
        "z": 940,
        "id": "af2f1df4-3d8e-4b3e-afe5-aedd806d6df5",
        "embeds": [
          "4e8df50e-c505-417a-9666-64796b3917e8"
        ],
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {
          "name": {
            "text": "ST_CONF_CLOSE_TIME_SELECT_HOUR_UN",
            "fontSize": 12
          },
          "specification": {
            "text": "entry[(close_hour_d==2) && (close_hour_u==4)]/close_hour_u=0\nentry[close_hour_u==10]/close_hour_u=0"
          }
        }
      },
      {
        "type": "Transition",
        "source": {
          "id": "8d620304-3b92-4db2-8358-fc19c564fb95"
        },
        "target": {
          "anchor": {
            "args": {
              "rotate": true,
              "dx": 59.2255859375,
              "dy": 44.875
            },
            "name": "topLeft"
          },
          "id": "af2f1df4-3d8e-4b3e-afe5-aedd806d6df5",
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "z": 941,
        "id": "af5862aa-42db-48ff-aa26-48cc21345d48",
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "af2f1df4-3d8e-4b3e-afe5-aedd806d6df5"
        },
        "target": {
          "id": "60387e87-a2c2-44f4-ad47-46ae944a142d"
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "z": 941,
        "id": "682610d7-81a1-479b-b493-4b394648f46b",
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "af2f1df4-3d8e-4b3e-afe5-aedd806d6df5"
        },
        "target": {
          "id": "b663631b-d56d-45ae-a26c-101d2e8d3dbd",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 221.2255859375,
              "dy": 31.4166259765625,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Escape"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "1"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "1b3cdcb5-a178-4649-8840-5ca74fd40ce3",
        "z": 941,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "af2f1df4-3d8e-4b3e-afe5-aedd806d6df5"
        },
        "target": {
          "id": "af2f1df4-3d8e-4b3e-afe5-aedd806d6df5",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 181.2255859375,
              "dy": 54.2083740234375,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Enter/close_hour_u = (close_hour_u%10)+1"
              }
            },
            "position": {
              "distance": 0.46830008684137703,
              "offset": 17,
              "angle": 0
            }
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "4e8df50e-c505-417a-9666-64796b3917e8",
        "z": 941,
        "vertices": [
          {
            "x": -3877.5390865170325,
            "y": -1055.5833358764648
          }
        ],
        "parent": "af2f1df4-3d8e-4b3e-afe5-aedd806d6df5",
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "c656703e-4518-4192-b296-75cb2c84addb"
        },
        "target": {
          "id": "8d620304-3b92-4db2-8358-fc19c564fb95",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 191.19091796875,
              "dy": 72.4166259765625,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "3"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "83dece5f-95dc-42c8-b225-560bea8d7a3a",
        "z": 942,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "vertices": [
          {
            "x": -2967,
            "y": -1143
          },
          {
            "x": -4246,
            "y": -1009
          }
        ],
        "attrs": {}
      },
      {
        "type": "Transition",
        "source": {
          "id": "b663631b-d56d-45ae-a26c-101d2e8d3dbd"
        },
        "target": {
          "id": "043477b0-85fb-4004-ad27-0f5282b74e89",
          "anchor": {
            "name": "topLeft",
            "args": {
              "dx": 22.96533203125,
              "dy": 38.9375,
              "rotate": true
            }
          },
          "priority": true
        },
        "router": {
          "name": "orthogonal",
          "args": {
            "padding": 8
          }
        },
        "connector": {
          "name": "rounded"
        },
        "labels": [
          {
            "attrs": {
              "text": {
                "text": "Next"
              }
            },
            "position": {}
          },
          {
            "attrs": {
              "label": {
                "text": "2"
              }
            }
          },
          {
            "attrs": {}
          },
          {
            "attrs": {}
          }
        ],
        "id": "ddd404ed-a408-4de2-8d41-cbf79e5011ab",
        "z": 943,
        "parent": "33b60e45-8d4e-4021-8ca4-8cdc6d27d82d",
        "attrs": {}
      }
    ]
  },
  "genModel": {
    "generator": {
      "type": "create::c",
      "features": {
        "Outlet": {
          "targetProject": "",
          "targetFolder": "",
          "libraryTargetFolder": "",
          "skipLibraryFiles": "",
          "apiTargetFolder": ""
        },
        "LicenseHeader": {
          "licenseText": ""
        },
        "FunctionInlining": {
          "inlineReactions": false,
          "inlineEntryActions": false,
          "inlineExitActions": false,
          "inlineEnterSequences": false,
          "inlineExitSequences": false,
          "inlineChoices": false,
          "inlineEnterRegion": false,
          "inlineExitRegion": false,
          "inlineEntries": false
        },
        "OutEventAPI": {
          "observables": false,
          "getters": false
        },
        "IdentifierSettings": {
          "moduleName": "PersianasCopyCopy",
          "statemachinePrefix": "persianasCopyCopy",
          "separator": "_",
          "headerFilenameExtension": "h",
          "sourceFilenameExtension": "c"
        },
        "Tracing": {
          "enterState": "",
          "exitState": "",
          "generic": ""
        },
        "Includes": {
          "useRelativePaths": false,
          "generateAllSpecifiedIncludes": false
        },
        "GeneratorOptions": {
          "userAllocatedQueue": false,
          "metaSource": false
        },
        "GeneralFeatures": {
          "timerService": false,
          "timerServiceTimeType": ""
        },
        "Debug": {
          "dumpSexec": false
        }
      }
    }
  }
}