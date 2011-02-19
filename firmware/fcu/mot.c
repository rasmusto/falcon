#include "mot.h"

void init_mot_tx_pkt(volatile struct mot_tx_pkt_t * pkt)
{
    pkt->start = MOT_START;
    pkt->tgt_1 = 0;
    pkt->tgt_2 = 0;
    pkt->tgt_3 = 0;
    pkt->tgt_4 = 0;
    pkt->crc = crc((char *)pkt, 9, 7); //calculate the crc on the first 9 bytes of motor packet with divisor 7
}

void init_mot_rx_pkt(volatile struct mot_rx_pkt_t * pkt)
{
    pkt->start = 0;
    pkt->spd_1 = 0;
    pkt->spd_2 = 0;
    pkt->spd_3 = 0;
    pkt->spd_4 = 0;
    pkt->crc = 0;
}
