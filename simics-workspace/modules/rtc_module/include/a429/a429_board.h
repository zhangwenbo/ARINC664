/**
 * @file a429_board.h
 * @brief A429 API board functions
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

#ifndef A429_BOARD_H
#define A429_BOARD_H

#include <a429/a429_defines.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup board Board functions
 * Board-level functions.
 * @{
 */

/** Maximum length of the board's model string */
#define A429_MAX_MODEL_STRING 1024

/**
 * Directions available for channels on the board.
 */
typedef enum
{
    /** Receiver channel */
    A429_CHANNEL_RX,

    /** Transmitter channel */
    A429_CHANNEL_TX,
} A429ChannelDirection;

/**
 * Details of a particular board in the system.
 */
typedef struct
{
    /** Serial number of the board */
    uint64_t serial_number;

    /** Number of usable channels on the target board */
    uint8_t channel_count;

    /** Model of the target board */
    char model_string[A429_MAX_MODEL_STRING];
} A429BoardDetails;

/**
 * Resulting details from a self-test execution.
 */
typedef struct
{
    /** Non-zero if the test passed, zero if it failed */
    uint8_t passed;
} A429SelfTestResults;

/**
 * Configures a board and all of its channels based on a saved configuration from a
 * binary file.
 *
 * @param aBinPath path to binary serialized configuration file
 * @param aBoardHandle handle for the board to configure
 * @return success or failure status of the function call
 * @warning Any configuration that may have existed on the board and all channels
 *      before this operation will be lost in the process.  Any handles to objects on
 *      the board or channels will no longer be valid.
 * @see a429BoardGetChannel to obtain handles to the configured channels
 */
A429_API_FUNC A429Return a429BoardConfigBin(const char* aBinPath, A429Handle aBoardHandle);

/**
 * Configures a board and all of its channels based on a saved configuration from an
 * XML file.
 *
 * @param aSchemaPath path to the ait_429.xsd schema file
 * @param aXmlPath path to the XML data file
 * @param aXmlXPath XPath expression to extract the desired configuration
 * @param aBoardHandle handle for the board to configure
 * @return success or failure status of the function call
 * @warning Any configuration that may have existed on the board and all channels
 *      before this operation will be lost in the process.  Any handles to objects on the
 *      board or channels will no longer be valid.
 * @see a429BoardGetChannel to obtain handles to the configured channels
 */
A429_API_FUNC A429Return a429BoardConfigXml(const char* aSchemaPath, const char* aXmlPath,
        const char* aXmlXPath, A429Handle aBoardHandle);

/**
 * Gets a handle to a board based on the board's serial number.
 *
 * @param aSerialNumber serial number of the board to retrieve
 * @param[out] apBoardHandle the new handle for the board
 * @return success or failure status of the function call, @ref A429_ERROR_RESOURCE_NOT_FOUND
 *      if the board does not exist
 * @note The board must be closed by a429BoardClose() when no longer in use.
 * @see a429SystemGetSystemInfo to retrieve available serial numbers
 */
A429_API_FUNC A429Return a429BoardInitializeBySerialNumber(uint64_t aSerialNumber,
        A429Handle* apBoardHandle);

/**
 * Gets a handle to a board based on the board's index in the system.
 *
 * @param aIndex index of the board to retrieve
 * @param[out] apBoardHandle the new handle for the board
 * @return success or failure status of the function call, @ref A429_ERROR_RESOURCE_NOT_FOUND
 *      if the board does not exist
 * @note The board must be closed by a429BoardClose() when no longer in use.
 * @see a429SystemGetSystemInfo to determine the number of available boards
 */
A429_API_FUNC A429Return a429BoardInitializeByIndex(uint32_t aIndex, A429Handle* apBoardHandle);

/**
 * Closes the board and releases its resources back to the system.  The handle
 * given will be destroyed and cannot be used for subsequent API calls.
 *
 * @param[in,out] apBoardHandle handle of the board to relinquish use of
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429BoardClose(A429Handle* apBoardHandle);

/**
 * Resets the board to a default state.
 *
 * @param aBoardHandle handle of the board to reset
 * @return success or failure status of the function call
 * @warning Resetting the board will invalidate all handles produced by the board.
 */
A429_API_FUNC A429Return a429BoardReset(A429Handle aBoardHandle);

/**
 * Gets the handle for a configured channel on the board.  This channel will
 * be a receiver or transmitter channel depending on its current configuration.
 *
 * @param aBoardHandle handle of board to inspect
 * @param aChannelNumber number of the channel to find (1-indexed)
 * @param[out] aChannelHandle handle of the retrieved channel
 * @return success or failure status of the function call, @ref A429_ERROR_RESOURCE_NOT_FOUND
 *      if the channel is not configured
 * @note The handle must be destroyed by a429UtilsDestroyHandle() when no longer in use.
 */
A429_API_FUNC A429Return a429BoardGetChannel(A429Handle aBoardHandle, uint8_t aChannelNumber,
        A429Handle* aChannelHandle);
/**
 * Sets the given channel as either a transmitter or receiver.
 *
 * @param aBoardHandle handle of the board to modify
 * @param aChannelNumber number of the channel to modify (1-indexed)
 * @param aDirection channel's new direction
 * @return success or failure status of the function call
 * @warning Changing a channel's direction will cause the board to be reset.  This
 *      will invalidate all handles produced by the board.  This operation should
 *      be done before obtaining channel handles.
 * @note This operation should not be needed when configuring the board via
 *      datafiles.  Channel directions are automatically set in that case.
 */
A429_API_FUNC A429Return a429BoardSetChannelDirection(A429Handle aBoardHandle,
        uint8_t aChannelNumber, A429ChannelDirection aDirection);

/**
 * Configures a receive channel on the board.
 *
 * @param aBoardHandle handle of the board to configure
 * @param aChannelNumber channel number to use for the receiver (1-indexed)
 * @param aSpeed speed for the new channel to operate at
 * @param[out] apChannelHandle handle of the newly configured channel
 * @return success or failure status of the function call
 * @warning Any configuration that may have existed on the channel before this operation
 *      will be lost in the process.  Any handles to objects previously on the channel,
 *      as well as the channel itself will no longer be valid.
 * @note The channel handle must be destroyed by a429UtilsDestroyHandle() when no longer in use.
 */
A429_API_FUNC A429Return a429BoardConfigRxChannel(A429Handle aBoardHandle, uint8_t aChannelNumber,
        A429ChannelSpeed aSpeed, A429Handle* apChannelHandle);

/**
 * Configures a transmit channel on the board.
 *
 * @param aBoardHandle handle of the board to configure
 * @param aChannelNumber channel number to use for the transmitter (1-indexed)
 * @param aSpeed speed for the new channel to operate at
 * @param[out] apChannelHandle handle of the newly configured channel
 * @param isParityEnabled Non-zero to enable automatic parity, 0 to disable
 * @return success or failure status of the function call
 * @warning Any configuration that may have existed on the channel before this operation
 *      will be lost in the process.  Any handles to objects previously on the channel,
 *      as well as the channel itself will no longer be valid.
 * @note The channel handle must be destroyed by a429UtilsDestroyHandle() when no longer in use.
 */
A429_API_FUNC A429Return a429BoardConfigTxChannel(A429Handle aBoardHandle, uint8_t aChannelNumber,
        A429ChannelSpeed aSpeed, A429Handle* apChannelHandle, uint8_t isParityEnabled);

/**
 * Configures a data corrupter channel on the board.
 *
 * @param aBoardHandle handle of the board to configure
 * @param aChannelNumber channel number to use for the transmitter (1-indexed)
 * @param aSourceChannelNumber channel number of the receiver to use as the data 
 *      source for the corrupter (1-indexed)
 * @param aSpeed speed for the new channel to operate at
 * @param[out] apChannelHandle handle of the newly configured channel
 * @return success or failure status of the function call
 * @warning Any configuration that may have existed on the channel before this operation
 *      will be lost in the process.  Any handles to objects previously on the channel,
 *      as well as the channel itself will no longer be valid.
 * @note The channel handle must be destroyed by a429UtilsDestroyHandle() when no longer in use.
 */
A429_API_FUNC A429Return a429BoardConfigDcChannel(A429Handle aBoardHandle, uint8_t aChannelNumber,
        uint8_t aSourceChannelNumber, A429ChannelSpeed aSpeed, A429Handle* apChannelHandle);

/**
 * Causes the board to execute its internal self test. At the conclusion of the
 * test the board is reset and any previously set channel configurations are
 * lost and must be re-applied.
 *
 * @param aBoardHandle handle of the board to test
 * @param[out] apTestResults structure to populate with test results
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429BoardSelfTest(A429Handle aBoardHandle,
        A429SelfTestResults* apTestResults);

/**
 * Starts all configured receive and transmit channels on the board.
 *
 * @param aBoardHandle handle of the board to start
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429BoardStartBoard(A429Handle aBoardHandle);

/**
 * Stops all configured receive and transmit channels on the board.
 *
 * @param aBoardHandle handle of the board to stop
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429BoardStopBoard(A429Handle aBoardHandle);

/**
 * Starts (or 'arms') an individual channel.  When the channel actually begins receiving
 * (if Rx) or transmitting (if Tx) depends on the channel's configuration.
 *
 * @param aBoardHandle handle of the board
 * @param aChannel channel number to start
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429BoardStartChannel(A429Handle aBoardHandle, uint8_t aChannel);

/**
 * Stops an individual channel.
 *
 * @param aBoardHandle handle of the board
 * @param aChannel channel number to stop
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429BoardStopChannel(A429Handle aBoardHandle, uint8_t aChannel);

/**
 * Starts all configured transmit channels on the board.
 *
 * @param aBoardHandle handle of the board
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429BoardStartAllTxChannels(A429Handle aBoardHandle);

/**
 * Stops all transmit channels on the board.
 *
 * @param aBoardHandle handle of the board
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429BoardStopAllTxChannels(A429Handle aBoardHandle);

/**
 * Starts all configured receive channels on the board.
 *
 * @param aBoardHandle handle of the board
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429BoardStartAllRxChannels(A429Handle aBoardHandle);

/**
 * Stops all receive channels on the board.
 *
 * @param aBoardHandle handle of the board
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429BoardStopAllRxChannels(A429Handle aBoardHandle);

/**
 * Gets details about a particular board in the system.
 *
 * @param aBoardHandle handle of the board to inspect
 * @param[out] apBoardDetails structure to populate with board details
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429BoardGetBoardDetails(A429Handle aBoardHandle,
        A429BoardDetails* apBoardDetails);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* !A429_BOARD_H */

