/**
 * @file a429_tx.h
 * @brief A429 API transmitter functions
 *
 *  - $HeadURL$
 *  - $Date$
 *  - $Revision$
 *  - $Author$
 *
 * Copyright (c) 2011 by Avionics Interface Technologies
 *  - Omaha, NE USA
 *  - Beavercreek, OH USA
 *  .
 * All rights reserved.  No part of this software may
 * be published, distributed, translated or otherwise
 * reproduced by any means or for any purpose without
 * the prior written consent of Avionics Interface Technologies. 
 */

#ifndef A429_TX_CHANNEL_H
#define A429_TX_CHANNEL_H

#include <a429/a429_defines.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup tx Transmit functions
 * Transmitter channel functions.
 * @{
 */

/**
 * Describes a channel's state regarding acyclic transfers.
 */
typedef enum
{
    /**
     * The channel is stopped.  Inserting an acyclic at this time will
     * only queue it for transfer once the channel is started.
     */
    A429_ACYCLIC_STOPPED,

    /** There is at least 1 active acyclic being transmitted. */
    A429_ACYCLIC_ACTIVE,

    /** The channel is running, but no acyclic transfer is running. */
    A429_ACYCLIC_IDLE,
} A429AcyclicTransferStatus;

/**
 * Selection of scheduled label transmission timing.
 *
 * @see A429ScheduledLabelOptions
 */
typedef enum
{
    /** Timing via a delay period */
    A429_LABEL_PERIOD,

    /** Timing via a number of transmissions per second */
    A429_LABEL_RATE
} A429ScheduledLabelTiming;

/**
 * Options available for a new acyclic transfer configuration.
 */
typedef struct
{
    /** The label that will be transmitting */
    uint8_t label;

    /** Optional SDI value to be transmitting */
    uint8_t sdi;

    /** Non-zero if SDI use is desired */
    uint8_t sdi_enabled;
} A429AcyclicTransferOptions;

/**
 * Options available for a new scheduled label configuration.
 */
typedef struct
{
    /** The label that will be transmitting */
    uint8_t label;

    /** Optional SDI value to be transmitting */
    uint8_t sdi;

    /** Non-zero if SDI use is desired */
    uint8_t sdi_enabled;

    /** Number of times to transmit the data buffer.  0 for continuous transmission. */
    uint16_t count;

    /**
     * Number of times per second to transmit the data buffer.  To use this
     * timing method, set the @ref timing field to @ref A429_LABEL_RATE.
     */
    double rate;

    /**
     * Delay in milliseconds between data buffer transmissions.  To use this
     * timing method, set the @ref timing field to @ref A429_LABEL_PERIOD.
     */
    uint32_t period;

    /** Selects which method of timing to use, rate or period */
    A429ScheduledLabelTiming timing;
} A429ScheduledLabelOptions;

/**
 * Defines a transmit channel based on a saved configuration from a binary file.
 *
 * @param aBinPath path to binary serialized configuration file
 * @param aChannelNumber channel number to apply the configuration to
 * @param aBoardHandle handle for the board on which to configure the channel
 * @param[out] apTxRateOrientedChannelHandle handle of the newly configured channel
 * @param[out] apRxMonitorChannelHandle handle of the newly configured channel's built-in
 *      monitor, will be set to NULL if the channel has no built-in monitor
 * @return success or failure status of the function call
 * @warning Any configuration that may have existed on the channel before this
 *      operation will be lost in the process.  Any handles to objects on those channels
 *      will no longer be valid.
 * @note The handles must be destroyed by a429UtilsDestroyHandle() when no longer in use.
 */
A429_API_FUNC A429Return a429TxConfigBin(const char* aBinPath, uint8_t aChannelNumber,
        A429Handle aBoardHandle, A429Handle* apTxRateOrientedChannelHandle,
        A429Handle* apRxMonitorChannelHandle);

/**
 * Defines a transmit channel based on a saved configuration from an XML file.
 *
 * @param aSchemaPath path to the ait_429.xsd schema file
 * @param aXmlPath path to the XML data file
 * @param aXmlXPath XPath expression to extract the desired configuration
 * @param aChannelNumber channel number to apply the configuration to
 * @param aBoardHandle handle for the board on which to configure the channel
 * @param[out] apTxRateOrientedChannelHandle handle of the newly configured channel
 * @param[out] apRxMonitorChannelHandle handle of the newly configured channel's built-in
 *      monitor, will be set to NULL if the channel has no built-in monitor
 * @return success or failure status of the function call
 * @warning Any configuration that may have existed on the channel before this
 *      operation will be lost in the process.  Any handles to objects on those channels
 *      will no longer be valid.
 * @note The handles must be destroyed by a429UtilsDestroyHandle() when no longer in use.
 */
A429_API_FUNC A429Return a429TxConfigXml(const char* aSchemaPath, const char* aXmlPath,
        const char* aXmlXPath, uint8_t aChannelNumber, A429Handle aBoardHandle,
        A429Handle* apTxRateOrientedChannelHandle, A429Handle* apRxMonitorChannelHandle);

#if 0
/**
 * Creates a new acyclic transfer on the transmit channel.
 *
 * @param aChannelHandle channel on which to create the new transfer
 * @param aOptions structure of options for the acyclic transfer
 * @param apData data array to copy and use as the data buffer
 * @param aSize size of the given data array
 * @param isCoerce if non-zero, the label and SDI in the transmitted data should be set
 *      to the value held by the transfer. if zero, keep the label and SDI as set in the
 *      given data words
 * @param[out] apTransferIndex index to the newly created transfer
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxCreateAcyclicTransfer(A429Handle aChannelHandle,
        A429AcyclicTransferOptions aOptions, const uint32_t* apData, uint32_t aSize,
        uint8_t isCoerce, uint32_t* apTransferIndex);
#endif

/**
 * Creates a new scheduled label transfer on the transmit channel.
 *
 * @param aChannelHandle channel on which to create the new transfer
 * @param aOptions structure of options for the scheduled label
 * @param apData data array to copy and use as the data buffer
 * @param aSize size of the given data array
 * @param isCoerce if non-zero, the label and SDI in the transmitted data should be set
 *      to the value held by the transfer. if zero, keep the label and SDI as set in the
 *      given data words
 * @param[out] apTransferHandle handle to the newly created transfer
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxCreateScheduledLabelTransfer(A429Handle aChannelHandle,
        A429ScheduledLabelOptions aOptions, const uint32_t* apData, uint32_t aSize,
        uint8_t isCoerce, A429Handle* apTransferHandle);

/**
 * Enables all transfers with the specified label for transmission on the channel.
 *
 * @param aChannelHandle handle to the channel to modify
 * @param aLabel label of transfers to enable
 * @param[out] apNumEnabled the number of transfers that were enabled
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxEnableLabel(A429Handle aChannelHandle, uint8_t aLabel,
        uint32_t* apNumEnabled);

/**
 * Disables all transfers with the specified label from transmission on the channel.
 *
 * @param aChannelHandle handle to the channel to modify
 * @param aLabel label of transfers to disable
 * @param[out] apNumDisabled the number of transfers that were disabled
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxDisableLabel(A429Handle aChannelHandle, uint8_t aLabel,
        uint32_t* apNumDisabled);

/**
 * Asynchronously send an array of data words.  It is possible that the entire array
 * may not be completely serviced, this is indicated via the words sent out-variable.
 *
 * @param aChannelHandle handle to the channel to modify
 * @param apWords array of data words to be sent
 * @param aNumWords size of the array of data words
 * @param[out] apWordsQueued the number of words that were queued for transmission
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxSendAsynchronousData(A429Handle aChannelHandle,
        const uint32_t* apWords, uint32_t aNumWords, uint32_t* apWordsQueued);

/**
 * Gets a handle to the acyclic transfer at the specified index.
 *
 * @param aChannelHandle handle to the channel to pull from
 * @param aTransferIndex index of the acyclic transfer to retrieve
 * @param[out] apTransferHandle the new handle for the acyclic transfer
 * @return success or failure status of the function call, @ref A429_ERROR_RESOURCE_NOT_FOUND
 *      if the transfer does not exist
 * @note The handle must be destroyed by a429UtilsDestroyHandle() when no longer in use.
 */
A429_API_FUNC A429Return a429TxGetAcyclicTransfer(A429Handle aChannelHandle,
        uint32_t aTransferIndex, A429Handle* apTransferHandle);

/**
 * Gets a handle to the acyclic transfer with the specified name.
 *
 * @param aChannelHandle handle to the channel to pull from
 * @param aTransferName name of the acyclic transfer to retrieve
 * @param[out] apTransferHandle the new handle for the acyclic transfer
 * @return success or failure status of the function call, @ref A429_ERROR_RESOURCE_NOT_FOUND
 *      if the transfer does not exist
 * @note The handle must be destroyed by a429UtilsDestroyHandle() when no longer in use.
 */
A429_API_FUNC A429Return a429TxGetAcyclicTransferByName(A429Handle aChannelHandle,
        const char* aTransferName, A429Handle* apTransferHandle);

/**
 * Inserts the selected acyclic transfer into the transmission on the channel. An acyclic
 * transfer can be inserted whether the channel is started or not, but if the channel is
 * stopped, the acyclic transfer will not go out until the channel is started.
 *
 * @param aChannelHandle handle to the channel to insert the acyclic on
 * @param aTransferIndex index of the acyclic transfer to insert
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxInsertAcyclicTransfer(A429Handle aChannelHandle,
        uint32_t aTransferIndex);

/**
 * Updates the data in the acyclic transfer's buffer.
 *
 * @param aTransferHandle handle to the acyclic transfer to update
 * @param apData array of new data for the acyclic
 * @param aSize size of the data array
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxSetAcyclicTransferData(A429Handle aTransferHandle,
        const uint32_t* apData, uint32_t aSize);

/**
 * Modifies the error injection setting of the acyclic transfer.
 *
 * @param aTransferHandle handle to the transfer to update
 * @param aErrorType type of error injection to being using for the transfer
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxSetAcyclicTransferErrorInjection(A429Handle aTransferHandle,
        A429ErrorInjectionType aErrorType);

/**
 * Gets the data from the acyclic transfer's buffer.
 *
 * @param aTransferHandle handle to the acyclic transfer to read from
 * @param[in,out] apData array to copy the acyclic data into
 * @param aSize size of the given data array
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxGetAcyclicTransferData(A429Handle aTransferHandle, uint32_t* apData,
        uint32_t aSize);

/**
 * Gets the size of the acyclic transfer's data buffer.
 *
 * @param aTransferHandle handle to the acyclic transfer to inspect
 * @param[out] apSize the size of the data buffer
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxGetAcyclicTransferSize(A429Handle aTransferHandle, uint32_t* apSize);

/**
 * Gets the status of acyclic transmission on the channel.
 *
 * @param aChannelHandle handle to the channel to insert the acyclic on
 * @param[out] apTransferStatus the channel's current acyclic status
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxGetAcyclicTransferStatus(A429Handle aChannelHandle,
        A429AcyclicTransferStatus* apTransferStatus);

/**
 * Gets a handle to the transfer configured with the given index.
 *
 * @param aChannelHandle handle to the channel to find the transfer in
 * @param aTransferIndex index of the transfer to retrieve
 * @param[out] apTransferHandle the new handle for the transfer
 * @return success or failure status of the function call, @ref A429_ERROR_RESOURCE_NOT_FOUND
 *      if the transfer does not exist
 * @note The handle must be destroyed by a429UtilsDestroyHandle() when no longer in use.
 */
A429_API_FUNC A429Return a429TxGetTransfer(A429Handle aChannelHandle, uint32_t aTransferIndex,
        A429Handle* apTransferHandle);

/**
 * Gets a handle to the transfer configured with the given name.
 *
 * @param aChannelHandle handle to the channel to find the transfer in
 * @param aTransferName name of the transfer to retrieve
 * @param[out] apTransferHandle the new handle for the transfer
 * @return success or failure status of the function call, @ref A429_ERROR_RESOURCE_NOT_FOUND
 *      if the transfer does not exist
 * @note The handle must be destroyed by a429UtilsDestroyHandle() when no longer in use.
 */
A429_API_FUNC A429Return a429TxGetTransferByName(A429Handle aChannelHandle,
        const char* aTransferName, A429Handle* apTransferHandle);

/**
 * Enables a particular transfer, allowing it to transmit.
 *
 * @param aTransferHandle handle of the transfer to enable
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxEnableTransfer(A429Handle aTransferHandle);

/**
 * Disables a particular transfer, preventing it from transmitting.
 *
 * @param aTransferHandle handle of the transfer to disable
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxDisableTransfer(A429Handle aTransferHandle);

/**
 * Updates the data in the scheduled label transfer's buffer.
 *
 * @param aTransferHandle handle to the transfer to update
 * @param apData array of new data for the transfer
 * @param aSize size of the data array
 * @param isCoerce if non-zero, the label and SDI should be reset to the value held
 *      by the transfer. if zero, keep the label and SDI as set in the given data words
 * @param[out] apWordsWritten the number of words written to the buffer, useful if the
 *      new buffer exceeds the size of the configured buffer
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxSetScheduledLabelData(A429Handle aTransferHandle,
        const uint32_t* apData, uint32_t aSize, uint8_t isCoerce, uint32_t* apWordsWritten);

/**
 * Updates the single-word of data in the scheduled label transfer's buffer.
 *
 * @note This is a utility function for dealing with single-word data buffers.
 * @param aTransferHandle handle to the transfer to update
 * @param aDatum new data word for the transfer
 * @param isCoerce if non-zero, the label and SDI should be reset to the value held
 *      by the transfer. if zero, keep the label and SDI as set in the given data words
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxSetScheduledLabelDatum(A429Handle aTransferHandle, uint32_t aDatum,
        uint8_t isCoerce);

/**
 * Modifies the error injection setting of the scheduled label transfer.
 *
 * @param aTransferHandle handle to the transfer to update
 * @param aErrorType type of error injection to being using for the transfer
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxSetScheduledLabelErrorInjection(A429Handle aTransferHandle,
        A429ErrorInjectionType aErrorType);

/**
 * Sets the schedule label transfer's transmit period.
 *
 * @param aTransferHandle handle to the transfer to update
 * @param aPeriod new transmit period for the transfer
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxSetScheduledLabelTransferPeriod(A429Handle aTransferHandle,
        uint32_t aPeriod);

/**
 * Sets the schedule label transfer's transmit rate.
 *
 * @param aTransferHandle handle to the transfer to update
 * @param aRate new transmit rate for the transfer
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxSetScheduledLabelTransferRate(A429Handle aTransferHandle,
        double aRate);

/**
 * Gets the data from the schedule label transfer's buffer.
 *
 * @param aTransferHandle handle to the transfer to read from
 * @param[in,out] apData array to copy the data into
 * @param aSize size of the given data array
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxGetScheduledLabelData(A429Handle aTransferHandle, uint32_t* apData,
        uint32_t aSize);

/**
 * Gets the size of the schedule label transfer's data buffer.
 *
 * @param aTransferHandle handle to the transfer to inspect
 * @param[out] apSize the size of the data buffer
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxGetScheduledLabelSize(A429Handle aTransferHandle, uint32_t* apSize);

/**
 * Gets the scheduled label transfer's transmit period.
 *
 * @param aTransferHandle handle to the transfer to inspect
 * @param[out] apPeriod the transmit period of the transfer
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxGetScheduledLabelPeriod(A429Handle aTransferHandle,
        uint32_t* apPeriod);

/**
 * Gets the scheduled label transfer's transmit rate.
 *
 * @param aTransferHandle handle to the transfer to inspect
 * @param[out] apRate the transmit rate of the transfer
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxGetScheduledLabelRate(A429Handle aTransferHandle, double* apRate);

/**
 * Updates the data in the block transfer's buffer.
 *
 * @param aTransferHandle handle to the transfer to update
 * @param apData array of new data for the transfer
 * @param aSize size of the data array
 * @param[out] apWordsWritten the number of words written to the buffer, useful if the
 *      new buffer exceeds the size of the configured buffer
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxSetBlockTransferData(A429Handle aTransferHandle,
        const uint32_t* apData, uint32_t aSize, uint32_t* apWordsWritten);

/**
 * Modifies the error injection setting of the block transfer.
 *
 * @param aTransferHandle handle to the transfer to update
 * @param aErrorType type of error injection to being using for the transfer
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxSetBlockTransferErrorInjection(A429Handle aTransferHandle,
        A429ErrorInjectionType aErrorType);

/**
 * Gets the data from the block transfer's buffer.
 *
 * @param aTransferHandle handle to the transfer to read from
 * @param[in,out] apData array to copy the data into
 * @param aSize size of the given data array
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxGetBlockTransferData(A429Handle aTransferHandle, uint32_t* apData,
        uint32_t aSize);

/**
 * Gets the size of the block transfer's data buffer.
 *
 * @param aTransferHandle handle to the transfer to inspect
 * @param[out] apSize the size of the data buffer
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429TxGetBlockTransferSize(A429Handle aTransferHandle, uint32_t* apSize);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* !A429_TX_CHANNEL_H */
