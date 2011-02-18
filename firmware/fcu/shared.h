/* LED bitmasks */
#define LED_1_RED_ON()      PORTA.OUTSET=PIN4_bm;
#define LED_1_RED_OFF()     PORTA.OUTCLR=PIN4_bm;
#define LED_1_GREEN_ON()    PORTF.OUTSET=PIN4_bm;
#define LED_1_GREEN_OFF()   PORTF.OUTCLR=PIN4_bm;
#define LED_2_RED_ON()      PORTA.OUTSET=PIN5_bm;
#define LED_2_RED_OFF()     PORTA.OUTCLR=PIN5_bm;
#define LED_2_GREEN_ON()    PORTF.OUTSET=PIN5_bm;
#define LED_2_GREEN_OFF()   PORTF.OUTCLR=PIN5_bm;
#define LED_3_RED_ON()      PORTA.OUTSET=PIN6_bm;
#define LED_3_RED_OFF()     PORTA.OUTCLR=PIN6_bm;
#define LED_3_GREEN_ON()    PORTF.OUTSET=PIN6_bm;
#define LED_3_GREEN_OFF()   PORTF.OUTCLR=PIN6_bm;
#define LED_4_RED_ON()      PORTA.OUTSET=PIN7_bm;
#define LED_4_RED_OFF()     PORTA.OUTCLR=PIN7_bm;
#define LED_4_GREEN_ON()    PORTF.OUTSET=PIN7_bm;
#define LED_4_GREEN_OFF()   PORTF.OUTCLR=PIN7_bm;

#define MOT_START 0b01011111

#define IMU_START 0xFACE

/* Data Structures */
struct mot_tx_pkt_t
{
    volatile uint8_t start;
    volatile uint16_t tgt_1;
    volatile uint16_t tgt_2;
    volatile uint16_t tgt_3;
    volatile uint16_t tgt_4;
    volatile uint8_t crc;
};

struct mot_rx_pkt_t
{
    volatile uint8_t start;
    volatile uint16_t spd_1;
    volatile uint16_t spd_2;
    volatile uint16_t spd_3;
    volatile uint16_t spd_4;
    volatile uint8_t crc;
};

struct imu_tx_pkt_t
{
    volatile uint16_t start;
};

struct imu_rx_pkt_t
{
    volatile uint8_t start;
    volatile uint8_t chksum;
    volatile int16_t pitch_tmp;
    volatile int16_t pitch;
    volatile int16_t yaw;
    volatile int16_t yaw_tmp;
    volatile int16_t z_accel;
    volatile int16_t y_accel;
    volatile int16_t x_accel;
    volatile int16_t roll;
};

volatile char usb_rx_buf[128];
volatile uint8_t usb_rx_count = 0;
volatile uint8_t usb_rx_buf_rdy = 0;

volatile char xbee_rx_buf[128];
volatile uint8_t xbee_rx_count = 0;
volatile uint8_t xbee_rx_buf_rdy = 0;

volatile struct mot_tx_pkt_t mot_tx;
volatile struct mot_rx_pkt_t mot_rx;

volatile struct imu_tx_pkt_t imu_tx;
volatile struct imu_rx_pkt_t imu_rx;

volatile struct pid_info pid;

volatile uint8_t print_status_flag = 1;

volatile uint8_t bat_voltage_raw;
volatile float bat_voltage_human;
