/**
 * @file a429_rx.h
 * @brief A429 API receiver functions
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

#ifndef A429_RX_CHANNEL_H
#define A429_RX_CHANNEL_H

#include <a429/a429_defines.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup rx Receive functions
 * Receiver channel functions.
 * @{
 */

/**
 * Directives used by event handler call-backs to control event dispatch.
 */
typedef enum
{
    /**
     * Do nothing.  If the event is a threshold event, the threshold will not be updated
     * and will remain at the previous location.
     */
    A429_RX_DIRECTIVE_NONE,

    /**
     * Update the threshold to occur again.  This will update the current threshold value to
     * occur in another iteration of the configured percentage.  For example, if the threshold
     * percentage is 20%, updating it after an event will cause the event to occur again after
     * another 20% has been filled.
     */
    A429_RX_DIRECTIVE_UPDATE_THRESHOLD,
} A429RxEventDirective;

/**
 * Invoked as a receive buffer call-back function.
 *
 * @param aChannelHandle handle of the receive channel
 * @return directive to the event dispatch, see available values
 * @warning Do not retain the handle passed into this function, its validity is
 *      not guaranteed outside of a call-back invocation.
 * @see a429RxSetEventHandlerBufferFull
 * @see a429RxSetEventHandlerBufferThreshold
 * @see a429RxSetEventHandlerStartCapture
 */
typedef A429RxEventDirective (*A429_RECEIVER_CALLBACK)(A429Handle aChannelHandle);

/**
 * Types of errors that can occur on a single Rx buffer entry.
 */
typedef enum
{
    /** Bit count high/low error */
    A429_BIT_COUNT_ERROR = 1 << 0,

    /** Coding error */
    A429_CODING_ERROR = 1 << 1,

    /** Gap error */
    A429_GAP_ERROR = 1 << 2,

    /** Parity (even) error */
    A429_PARITY_ERROR = 1 << 3,

    /** Bit too short error */
    A429_SHORT_BIT_ERROR = 1 << 4,

    /** Bit too long error */
    A429_LONG_BIT_ERROR = 1 << 5,
} A429RxErrorTypes;

/**
 * An individual extended read buffer entry.
 */
typedef struct
{
    /** Raw ARINC-429 data word */
    uint32_t data;

    /** Time tag when this word was received */
    A429TimeTag time_tag;

    /** Bitmask of errors from @ref A429RxErrorTypes, 0 for no errors */
    uint32_t error_word;
} A429RxReadBufferEntry;

/**
 * Defines a receive channel based on a saved configuration from a binary file.
 *
 * @param aBinPath path to binary serialized configuration file
 * @param aChannelNumber channel number to apply the configuration to
 * @param aBoardHandle handle for the board on which to configure the channel
 * @param[out] apRxMonitorChannelHandle handle of the newly configured channel
 * @return success or failure status of the function call
 * @warning Any configuration that may have existed on the channel before this
 *      operation will be lost in the process.  Any handles to objects on those
 *      channels will no longer be valid.
 * @note The handles must be destroyed by a429UtilsDestroyHandle() when no longer in use.
 */
A429_API_FUNC A429Return a429RxConfigBin(const char* aBinPath, uint8_t aChannelNumber,
        A429Handle aBoardHandle, A429Handle* apRxMonitorChannelHandle);

/**
 * Defines a receive channel based on a saved configuration from an XML file.
 *
 * @param aSchemaPath path to the ait_429.xsd schema file
 * @param aXmlPath path to the XML data file
 * @param aXmlXPath XPath expression to extract the desired configuration
 * @param aChannelNumber channel number to apply the configuration to
 * @param aBoardHandle handle for the board on which to configure the channel
 * @param[out] apRxMonitorChannelHandle handle of the newly configured channel
 * @return success or failure status of the function call
 * @warning Any configuration that may have existed on the channel before this
 *      operation will be lost in the process.  Any handles to objects on those
 *      channels will no longer be valid.
 * @note The handles must be destroyed by a429UtilsDestroyHandle() when no longer in use.
 */
A429_API_FUNC A429Return a429RxConfigXml(const char* aSchemaPath, const char* aXmlPath,
        const char* aXmlXPath, uint8_t aChannelNumber, A429Handle aBoardHandle,
        A429Handle* apRxMonitorChannelHandle);

/**
 * Creates a new label buffer on the channel.  All SDI values will be accepted by this buffer.
 *
 * @param aChannelHandle handle of the channel to create the buffer on
 * @param aLabel label of the new buffer
 * @param aEntryCount number of entries to store in the buffer
 * @param aCyclic if zero, the buffer will not be cyclic and will stop when full, if non-zero
 *      the buffer will be cyclic
 * @param aParity if zero, the parity bit will be treated as data, if non-zero it will be
 *      the parity bit
 * @return success or failure of the function call
 * @warning If a label buffer with the same label already existed on the channel, an error
 *      will be returned.
 */
A429_API_FUNC A429Return a429RxCreateLabelBuffer(A429Handle aChannelHandle, uint8_t aLabel,
        uint32_t aEntryCount, uint8_t aCyclic, uint8_t aParity);

/**
 * Creates a new label buffer on the channel.  Only the specific SDI value will be accepted by
 * this buffer.
 *
 * @param aChannelHandle handle of the channel to create the buffer on
 * @param aLabel label of the new buffer
 * @param aSdi SDI value of the new buffer
 * @param aEntryCount number of entries to store in the buffer
 * @param aCyclic if zero, the buffer will not be cyclic and will stop when full, if non-zero
 *      the buffer will be cyclic
 * @param aParity if zero, the parity bit will be treated as data, if non-zero it will be
 *      the parity bit
 * @return success or failure of the function call
 * @warning If a label buffer with the same label and SDI already existed on the channel, an
 *      error will be returned.
 */
A429_API_FUNC A429Return a429RxCreateLabelSdiBuffer(A429Handle aChannelHandle, uint8_t aLabel,
        uint8_t aSdi, uint32_t aEntryCount, uint8_t aCyclic, uint8_t aParity);

/**
 * Reads a number of pending entries from the receiver buffer.
 *
 * @param aChannelHandle handle to the channel to read from
 * @param[in,out] apDataBuffer array to fill with data words
 * @param aBufferSize size of the data buffer passed in
 * @param[out] apWordsRead number of entries set into the given array
 * @return success or failure status of the function call
 * @see a429RxReadEx for time stamps and error information along with the data
 */
A429_API_FUNC A429Return a429RxRead(A429Handle aChannelHandle, uint32_t* apDataBuffer,
        uint32_t aBufferSize, uint32_t* apWordsRead);

/**
 * Reads a number of pending entries from the receiver buffer along with time stamp and
 * error information.
 *
 * @param aChannelHandle handle to the channel to read from
 * @param[in,out] apDataBuffer array to fill with buffer entries
 * @param aBufferSize size of the data buffer passed in
 * @param[out] apEntriesRead number of entries set into the given array
 * @return success or failure status of the function call
 * @see a429RxRead if time stamps or error information is not relevant
 */
A429_API_FUNC A429Return a429RxReadEx(A429Handle aChannelHandle,
        A429RxReadBufferEntry* apDataBuffer, uint32_t aBufferSize, uint32_t* apEntriesRead);

/**
 * Gets a handle to the existing label buffer identified by the given label.
 *
 * @param aChannelHandle handle to the channel containing the label buffer
 * @param aLabel 8-bit label identifying the label buffer
 * @param[out] apLabelBufferHandle the new handle for the label buffer
 * @return success or failure status of the function call, @ref A429_ERROR_RESOURCE_NOT_FOUND
 *      if the label buffer does not exist
 * @note The handle must be destroyed by a429UtilsDestroyHandle() when no longer in use.
 */
A429_API_FUNC A429Return a429RxGetLabelBufferByLabel(A429Handle aChannelHandle, uint8_t aLabel,
        A429Handle* apLabelBufferHandle);

/**
 * Gets a handle to the existing label buffer identified by the given label and SDI pair.
 *
 * @param aChannelHandle handle to the channel containing the label buffer
 * @param aLabel 8-bit label identifying the label buffer
 * @param aSdi 4-bit SDI value identifying the label buffer
 * @param[out] apLabelBufferHandle the new handle for the label buffer
 * @return success or failure status of the function call, @ref A429_ERROR_RESOURCE_NOT_FOUND
 *      if the label buffer does not exist
 * @note The handle must be destroyed by a429UtilsDestroyHandle() when no longer in use.
 */
A429_API_FUNC A429Return a429RxGetLabelBufferByLabelSdi(A429Handle aChannelHandle, uint8_t aLabel,
        uint8_t aSdi, A429Handle* apLabelBufferHandle);

/**
 * Gets a handle to the existing label buffer identified by the given name.
 *
 * @param aChannelHandle handle to the channel containing the label buffer
 * @param aName name assigned to the label buffer
 * @param[out] apLabelBufferHandle the new handle for the label buffer
 * @return success or failure status of the function call, @ref A429_ERROR_RESOURCE_NOT_FOUND
 *      if the label buffer does not exist
 * @note The handle must be destroyed by a429UtilsDestroyHandle() when no longer in use.
 */
A429_API_FUNC A429Return a429RxGetLabelBufferByName(A429Handle aChannelHandle, const char* aName,
        A429Handle* apLabelBufferHandle);

/**
 * Reads a number of pending entries from the label buffer.
 *
 * @param aLabelBufferHandle handle to the label buffer to read from
 * @param[in,out] apDataBuffer array to fill with data words
 * @param aBufferSize size of the data buffer passed in
 * @param[out] apWordsRead number of entries set into the given array
 * @return success or failure status of the function call
 * @note The array passed to this function must be 64-bit aligned
 */
A429_API_FUNC A429Return a429RxReadLabelBuffer(A429Handle aLabelBufferHandle,
        uint32_t* apDataBuffer, uint32_t aBufferSize, uint32_t* apWordsRead);

/**
 * Sets an event handler call-back to be notified when a specific receive channel's
 * buffer becomes full.
 *
 * @note Only one event handler can be installed on a channel at a time, adding
 *      multiple event handlers will cause the previous handler to be replaced.
 * @param aChannelHandle handle of the channel to watch
 * @param apCallback pointer to call-back function
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429RxSetEventHandlerBufferFull(A429Handle aChannelHandle,
        A429_RECEIVER_CALLBACK apCallback);

/**
 * Sets an event handler call-back to be notified when a specific receive channel's
 * buffer becomes full to a certain threshold.
 *
 * @note Only one event handler can be installed on a channel at a time, adding
 *      multiple event handlers will cause the previous handler to be replaced.
 * @param aChannelHandle handle of the channel to watch
 * @param apCallback pointer to call-back function
 * @param aPercentage percentage-full the buffer should be for the event
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429RxSetEventHandlerBufferThreshold(A429Handle aChannelHandle,
        A429_RECEIVER_CALLBACK apCallback, float aPercentage);

/**
 * Sets an event handler call-back to be notified when a specific receive channel
 * starts.
 *
 * @note Only one event handler can be installed on a channel at a time, adding
 *      multiple event handlers will cause the previous handler to be replaced.
 * @param aChannelHandle handle of the channel to watch
 * @param apCallback pointer to call-back function
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429RxSetEventHandlerStartCapture(A429Handle aChannelHandle,
        A429_RECEIVER_CALLBACK apCallback);

/**
 * Removes the event handler call-back configured on the receive channel.
 *
 * @param aChannelHandle handle of the channel to modify
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429RxRemoveEventHandler(A429Handle aChannelHandle);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* !A429_RX_CHANNEL_H */
