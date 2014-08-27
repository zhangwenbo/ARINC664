#include <a429/a429_board.h>
#include <a429/a429_rx.h>
#include <a429/a429_tx.h>
#include <a429/a429_utils.h>

// NOTE: channel numbers are 1-indexed.
typedef struct _channel_conf_t {
    OwUInt8 tx_nr;
    OwUInt8 rx_nr;
} channel_conf_t;

#define MAX_CHANNELS 16

channel_conf_t g_channel_conf[MAX_CHANNELS] = {
    {1, 17},
    {2, 18},
    {3, 19},
    {4, 20},
    {5, 21},
    {6, 22},
    {7, 23},
    {8, 24},
    {9, 25},
    {10, 26},
    {11, 27},
    {12, 28},
    {13, 29},
    {14, 30},
    {15, 31},
    {16, 32}
};

typedef struct _channel_state_t {
    OwUInt32 nr;
    A429Handle tx_channel;
    A429Handle rx_channel;
    vector<OwUInt32> tx_fifo;
    vector<OwUInt32> rx_fifo;
    
    void (*channel_state_t)(struct _channel_state_t *this, const A429Handle *board, OwUInt32 nr, const channel_conf_t *conf);
    void (*stop)();
} channel_state_t;

channel_state_t inited_channel[MAX_CHANNELS] {
    {0, {0}, {0}, 0, 0, &init_channel_state_t, NULL},
    {0, {0}, {0}, 0, 0, &init_channel_state_t, NULL},
    {0, {0}, {0}, 0, 0, &init_channel_state_t, NULL},
    {0, {0}, {0}, 0, 0, &init_channel_state_t, NULL},
    {0, {0}, {0}, 0, 0, &init_channel_state_t, NULL},
    {0, {0}, {0}, 0, 0, &init_channel_state_t, NULL},
    {0, {0}, {0}, 0, 0, &init_channel_state_t, NULL},
    {0, {0}, {0}, 0, 0, &init_channel_state_t, NULL},
    {0, {0}, {0}, 0, 0, &init_channel_state_t, NULL},
    {0, {0}, {0}, 0, 0, &init_channel_state_t, NULL},
    {0, {0}, {0}, 0, 0, &init_channel_state_t, NULL},
    {0, {0}, {0}, 0, 0, &init_channel_state_t, NULL},
    {0, {0}, {0}, 0, 0, &init_channel_state_t, NULL},
    {0, {0}, {0}, 0, 0, &init_channel_state_t, NULL},
    {0, {0}, {0}, 0, 0, &init_channel_state_t, NULL},
    {0, {0}, {0}, 0, 0, &init_channel_state_t, NULL}
};

static void configure_tx(A429Handle board, uint8_t channel_num, A429Handle* tx) {
    A429Return rc = A429_SUCCESS;

    /* create the transmit channel */
    rc = a429BoardConfigTxChannel(board, channel_num, A429_CHANNEL_SPEED_LOW, tx, 1);
    if (A429_SUCCESS != rc) {
        fprintf(stderr, "Failed to configure transmit channel: %s\n", a429UtilsErrorString(rc));
        exit(1);
    }
}

static void configure_rx(A429Handle board, uint8_t channel_num, A429Handle* rx,
        A429Handle* label) {
    A429Return rc = A429_SUCCESS;

    /* create the receive channel */
    rc = a429BoardConfigRxChannel(board, channel_num, A429_CHANNEL_SPEED_LOW, rx);
    if (A429_SUCCESS != rc) {
        fprintf(stderr, "Failed to configure receive channel: %s\n", a429UtilsErrorString(rc));
        exit(1);
    }
}

static void init_channel_state_t(struct _channel_state_t *this, const A429Handle *board, OwUInt32 nr, const channel_conf_t *conf) {
    A429Return rc = A429_SUCCESS;
    
    this->nr = nr;

    configure_tx(board, conf.tx_nr, &this->tx_channel);
    rc = a429BoardStartChannel(this->tx_channel, conf.tx_nr); /* notice the second param, I'am not true */
    if (rc != A429_SUCCESS) {
        fprintf(stderr, "Failed to start transmit channel %d: %s\n", conf.tx_nr, a429UtilsErrorString(rc));
        exit(1);
    }

    configure_rx(board, conf.rx_nr, &this->rx_channel);
    rc = a429BoardStartChannel(this->rx_channel, conf.rx_nr); /* notice the second param, I'am not true */
    if (rc != A429_SUCCESS) {
        fprintf(stderr, "Failed to start receive channel %d: %s\n", conf.rx_nr, a429UtilsErrorString(rc));
        exit(1);
    }    
}

static A429Handle init_board(void) {
    A429Return rc = A429_SUCCESS;
    A429Handle board = { 0 };
    A429BoardDetails details = { 0 };
    A429Handle rx = { 0 };
    A429Handle tx = { 0 };
    
#if 1
    /* enable debug output */
    a429UtilsSetDebugLevel(A429_DEBUG_ERROR);
#endif

    /* no serial?  grab the 0th board. */
    if (0 == aSerialNumber) {
        rc = a429BoardInitializeByIndex(0, &board);
    } else {
        rc = a429BoardInitializeBySerialNumber(aSerialNumber, &board);
    }

    if (A429_SUCCESS != rc) {
        fprintf(stderr, "Unable to find a board: %s\n", a429UtilsErrorString(rc));
        exit(1);
    }

    /* print a little detail about the board */
    rc = a429BoardGetBoardDetails(board, &details);
    if (A429_SUCCESS != rc) {
        fprintf(stderr, "Failed to retrieve board details: %s\n", a429UtilsErrorString(rc));
        a429BoardClose(&board);
        exit(1);
    }

    printf("Found '%s' (serial #%" PRIu64 ")\n", details.model_string, details.serial_number);
    return board;
}

void func(channel_conf_t *input, int input_len) {
    A429Return rc = A429_SUCCESS;
    A429Handle board = init_board();

    int i = 0;
    for (; i < input_len; i++) {
        /* set the expected channel directions */
        rc = a429BoardSetChannelDirection(board, input[i].tx_nr, A429_CHANNEL_TX);
        if (A429_SUCCESS != rc) {
            fprintf(stderr, "Failed to set tx channel direction: %s\n", a429UtilsErrorString(rc));
            a429BoardClose(&board);
            exit(1);
        }
        
        rc = a429BoardSetChannelDirection(board, input[i].rx_nr, A429_CHANNEL_RX);
        if (A429_SUCCESS != rc) {
            fprintf(stderr, "Failed to set rx channel direction: %s\n", a429UtilsErrorString(rc));
            a429BoardClose(&board);
            exit(1);
        }
    }

    for (i = 0; i < input_len; i++) {
        inited_channel[i].(channel_state_t)(&inited_channel[i], &board, i, input[i]);
    }
}
