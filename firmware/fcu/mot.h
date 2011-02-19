#define MOT_START 0b01011111

/* Function Prototypes */
void init_mot_tx_pkt(volatile struct mot_tx_pkt_t * pkt);
void init_mot_rx_pkt(volatile struct mot_rx_pkt_t * pkt);

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
