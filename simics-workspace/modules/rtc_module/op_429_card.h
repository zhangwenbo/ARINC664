#ifndef OP_429_CARD_H
#define OP_429_CARD_H

#include <a429/a429_board.h>
#include <a429/a429_rx.h>
#include <a429/a429_tx.h>
#include <a429/a429_utils.h>

#include <stdio.h>

#ifndef PRIu64
#define PRIu64 "I64u"
#endif

typedef unsigned char OwUInt8;
typedef unsigned long OwUInt32;

// NOTE: channel numbers are 1-indexed.
typedef struct _channel_conf_t {
    OwUInt8 tx_nr;
    OwUInt8 rx_nr;
} channel_conf_t;

#define MAX_CHANNELS 16

typedef struct _channel_state_t {
    OwUInt32 nr;
    A429Handle tx_channel;
    A429Handle rx_channel;
    OwUInt32 *tx_fifo;
    OwUInt32 *rx_fifo;

    void (*constructor)(struct _channel_state_t *this, const A429Handle *board, OwUInt32 nr, const channel_conf_t* const conf);
    void (*stop)();
} channel_state_t;


static void configure_tx(A429Handle board, uint8_t channel_num, A429Handle* tx);
static void configure_rx(A429Handle board, uint8_t channel_num, A429Handle* rx);
static void construct_channel_state_t(struct _channel_state_t *this, const A429Handle *board, OwUInt32 nr, const channel_conf_t* const conf);
static A429Handle init_board(uint64_t aSerialNumber);
void init_channel_state(const A429Handle *board, channel_conf_t *chan_conf, int chan_conf_size);
void init_429_middleware(void);


#endif
