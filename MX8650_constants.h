#ifndef MX8650_constants
#define MX8650_constants

// Operational Modes
#define SLEEP_MODE_ADDR 0x05
#define DISABLE_SLEEP 0xA0
#define SLEEP_MODE_1 0xB0
#define SLEEP_MODE_2 0xB8
#define FORCE_SLEEP_1 0xB2
#define FORCE_SLEEP_2 0xBC
#define FORCE_WAKEUP 0xB1

// DPI
#define DPI_ADDR 0x06
#define DPI_800 0x04
#define DPI_100 0x05
#define DPI_1200 0x06
#define DPI_1600 0x07

// Sleep Frequency
#define SLEEP1_FREQ_ADDR 0x0A
#define SLEEP2_FREQ_ADDR 0x0C
#define SLEEP_FREQ_LOW 0x02
#define SLEEP_FREQ_MED 0x7
#define SLEEP_FREQ_HIGH 0xF2
#define SLEEP1_FREQ_DEFAULT 0x72
#define SLEEP2_FREQ_DEFAULT 0x92

// Sleep Mode Enter Time
#define SLEEP_ENTER_TIME_ADDR 0x0B

// Image Threshold
#define IMG_THRES_ADDR 0x0D

// Image Recogonition Rate
#define IMG_RECG_ADDR 0x0E
#define IMG_RATE_HIGHEST 0xE0
#define IMG_RATE_HIGH 0x07
#define IMG_RATE_MED 0x05
#define IMG_RATE_LOW 0x09
#define IMG_RATE_LOWEST 0x0F

// Motion Status
#define MOTION_STATUS_ADDR 0x02
#define DELTA_X_ADDR 0x03
#define DELTA_Y_ADDR 0x04

// Image Quality
#define IMG_QUALITY_ADDR 0x07

// Operation State
#define OPERATION_STATE_ADDR 0x08

#endif