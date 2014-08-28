#include <op_429_card.h>

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

channel_state_t inited_channel[MAX_CHANNELS] = {
    {0, {0}, {0}, NULL, NULL, &construct_channel_state_t, NULL},
    {0, {0}, {0}, NULL, NULL, &construct_channel_state_t, NULL},
    {0, {0}, {0}, NULL, NULL, &construct_channel_state_t, NULL},
    {0, {0}, {0}, NULL, NULL, &construct_channel_state_t, NULL},
    {0, {0}, {0}, NULL, NULL, &construct_channel_state_t, NULL},
    {0, {0}, {0}, NULL, NULL, &construct_channel_state_t, NULL},
    {0, {0}, {0}, NULL, NULL, &construct_channel_state_t, NULL},
    {0, {0}, {0}, NULL, NULL, &construct_channel_state_t, NULL},
    {0, {0}, {0}, NULL, NULL, &construct_channel_state_t, NULL},
    {0, {0}, {0}, NULL, NULL, &construct_channel_state_t, NULL},
    {0, {0}, {0}, NULL, NULL, &construct_channel_state_t, NULL},
    {0, {0}, {0}, NULL, NULL, &construct_channel_state_t, NULL},
    {0, {0}, {0}, NULL, NULL, &construct_channel_state_t, NULL},
    {0, {0}, {0}, NULL, NULL, &construct_channel_state_t, NULL},
    {0, {0}, {0}, NULL, NULL, &construct_channel_state_t, NULL},
    {0, {0}, {0}, NULL, NULL, &construct_channel_state_t, NULL},
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

static void configure_rx(A429Handle board, uint8_t channel_num, A429Handle* rx) {
    A429Return rc = A429_SUCCESS;

    /* create the receive channel */
    rc = a429BoardConfigRxChannel(board, channel_num, A429_CHANNEL_SPEED_LOW, rx);
    if (A429_SUCCESS != rc) {
        fprintf(stderr, "Failed to configure receive channel: %s\n", a429UtilsErrorString(rc));
        exit(1);
    }
}

static void construct_channel_state_t(struct _channel_state_t *this, const A429Handle *board, OwUInt32 nr, const channel_conf_t* const conf) {
    A429Return rc = A429_SUCCESS;
    
    this->nr = nr;

    configure_tx(board, conf->tx_nr, &this->tx_channel);
    rc = a429BoardStartChannel(this->tx_channel, conf->tx_nr); /* notice the second param, I'am not true */
    if (rc != A429_SUCCESS) {
        fprintf(stderr, "Failed to start transmit channel %d: %s\n", conf->tx_nr, a429UtilsErrorString(rc));
        exit(1);
    }

    configure_rx(board, conf->rx_nr, &this->rx_channel);
    rc = a429BoardStartChannel(this->rx_channel, conf->rx_nr); /* notice the second param, I'am not true */
    if (rc != A429_SUCCESS) {
        fprintf(stderr, "Failed to start receive channel %d: %s\n", conf->rx_nr, a429UtilsErrorString(rc));
        exit(1);
    }    
}

static A429Handle init_board(uint64_t aSerialNumber) {
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

    fprintf(stdout, "Found '%s' (serial #%" PRIu64 ")\n", details.model_string, details.serial_number);
    return board;
}

void init_channel_state(const A429Handle *board, channel_conf_t *chan_conf, int chan_conf_size) {
    A429Return rc = A429_SUCCESS;

    int i = 0;
    for (; i < chan_conf_size; i++) {
        /* set the expected channel directions */
        rc = a429BoardSetChannelDirection(*board, chan_conf[i].tx_nr, A429_CHANNEL_TX);
        if (A429_SUCCESS != rc) {
            fprintf(stderr, "Failed to set tx channel direction: %s\n", a429UtilsErrorString(rc));
            a429BoardClose(board);
            exit(1);
        }
        
        rc = a429BoardSetChannelDirection(*board, chan_conf[i].rx_nr, A429_CHANNEL_RX);
        if (A429_SUCCESS != rc) {
            fprintf(stderr, "Failed to set rx channel direction: %s\n", a429UtilsErrorString(rc));
            a429BoardClose(board);
            exit(1);
        }
    }

    for (i = 0; i < chan_conf_size; i++) { /* can be merged? */
        (inited_channel[i].constructor)(&inited_channel[i], board, i, &chan_conf[i]);
    }
}

void init_429_middleware(void) {
    uint64_t aSerialNumber = 0; /* How to get? */
    A429Handle board = init_board(aSerialNumber);
    init_channel_state(&board, g_channel_conf, MAX_CHANNELS);
}
