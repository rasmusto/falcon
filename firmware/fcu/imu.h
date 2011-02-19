#define IMU_START 0xFACE

/* Function Prototypes */
void init_imu_tx_pkt(volatile struct imu_tx_pkt_t * pkt);
void init_imu_rx_pkt(volatile struct imu_rx_pkt_t * pkt);
void request_imu_pkt();

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
