#include "shared.h"

void print_mot_pkts(volatile struct mot_tx_pkt_t * tx_pkt, volatile struct mot_rx_pkt_t * rx_pkt);
void print_imu_pkts(volatile struct imu_tx_pkt_t * tx_pkt, volatile struct imu_rx_pkt_t * rx_pkt);
void process_rx_buf(volatile char * rx_buf);
