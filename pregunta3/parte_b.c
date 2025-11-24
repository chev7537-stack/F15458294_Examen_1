Según la hoja de datos del nRF52840, la dirección base del periférico GPIO PORT0 es:
GPIO0_BASE = 0x50000000
Los registros del PUERTO0 tienen los siguientes offsets:

| Registro | Offset |
|---------|--------|
| OUT     | 0x504 |
| OUTSET  | 0x508 |
| OUTCLR  | 0x50C |
| IN      | 0x510 |
| DIR     | 0x514 |
| DIRSET  | 0x518 |
| DIRCLR  | 0x51C |


#include <stdint.h>

#define GPIO0_BASE     0x50000000UL

//Punteros 
#define GPIO0_OUT      (*(volatile uint32_t *)(GPIO0_BASE + 0x504))
#define GPIO0_OUTSET   (*(volatile uint32_t *)(GPIO0_BASE + 0x508))
#define GPIO0_OUTCLR   (*(volatile uint32_t *)(GPIO0_BASE + 0x50C))
#define GPIO0_IN       (*(volatile uint32_t *)(GPIO0_BASE + 0x510))
#define GPIO0_DIR      (*(volatile uint32_t *)(GPIO0_BASE + 0x514))
#define GPIO0_DIRSET   (*(volatile uint32_t *)(GPIO0_BASE + 0x518))
#define GPIO0_DIRCLR   (*(volatile uint32_t *)(GPIO0_BASE + 0x51C))
