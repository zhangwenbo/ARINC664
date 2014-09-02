#ifndef OP_429_CARD_H
#define OP_429_CARD_H

#include <a429/a429_board.h>
#include <a429/a429_rx.h>
#include <a429/a429_tx.h>
#include <a429/a429_utils.h>

#include <stdio.h>
#include <string.h>

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

typedef struct _Rx_Data {
    OwUInt32 rx_data;
    OwUInt32 is_vaild;
} Rx_Data;

typedef struct _channel_state_t {
    OwUInt32 nr;
    A429Handle tx_channel;
    A429Handle rx_channel;
    OwUInt32 tx_data;
    Rx_Data rx;

    void (*constructor)(struct _channel_state_t *this, const A429Handle *board, OwUInt32 nr, const channel_conf_t* const conf);
    void (*stop)();
} channel_state_t;

typedef struct _channel_data_t {
    OwUInt32 channel_nr;
    OwUInt32 word;
} channel_data_t;

static void configure_tx(const A429Handle* const board, uint8_t channel_num, A429Handle* tx);
static void configure_rx(const A429Handle* const board, uint8_t channel_num, A429Handle* rx);
static void construct_channel_state_t(struct _channel_state_t *this, const A429Handle *board, OwUInt32 nr, const channel_conf_t* const conf);
static A429Handle init_board(uint64_t aSerialNumber);
static void init_channel_state(const A429Handle *board, const channel_conf_t* const chan_conf, int chan_conf_size);
void init_429_middleware(void);

static send_to_429_card(const channel_state_t* const channel_state);
void send_to_429(void *channel_nr, void *word);
void recv_from_429();
static recv_from_429_card();

#endif
