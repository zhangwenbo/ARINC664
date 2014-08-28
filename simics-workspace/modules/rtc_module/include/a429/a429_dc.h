/**
 * @file a429_dc.h
 * @brief A429 API data corrupter functions
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

#ifndef A429_DC_CHANNEL_H
#define A429_DC_CHANNEL_H

#include <a429/a429_defines.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup dc Data Corrupter functions
 * Data Corrupter channel functions.
 * @{
 */

/**
 * Options of the data corrupter corruption function.
 * <p>
 * A corruption function is applied to the data word before 
 * transmission as follows:
 * <code>
 * tx_word = ( (rx_word & and_mask) | or_mask) XOR xor_mask) + add_value
 * </code>
 * <p>
 * Where:
 * <dl>
 * <dt>rx_word</dt><dd>the received word about to be modified (from the source channel)</dd>
 * <dt>and_mask</dt><dd>mask to AND with the received word</dd>
 * <dt>or_mask</dt><dd>mask to OR with the modified word</dd>
 * <dt>xor_mask</dt><dd>mask to XOR with the modified word</dd>
 * <dt>add_value</dt><dd>value to be added to the modified word</dd>
 * <dt>tx_word</dt><dd>final computed word to be transmitted by the channel</dd>
 * </dl>
 *
 * @see a429DcSetCorruptionFunctionByLabel
 * @see a429DcSetCorruptionFunctionByLabelSdi
 */
typedef struct
{
    uint32_t and_mask;      /**< Value of the AND mask */
    uint32_t or_mask;       /**< Value of the OR mask */
    uint32_t xor_mask;      /**< Value of the XOR mask */
    uint32_t add_value;     /**< Value of the ADD value */
} A429DataCorruptionOptions;

/**
 * Defines a corrupter channel based on a saved configuration from a binary file.
 *
 * @param aBinPath path to binary serialized configuration file
 * @param aChannelNumber channel number to apply the configuration to
 * @param aBoardHandle handle for the board on which to configure the channel
 * @param[out] apTxDataCorrupterChannelHandle handle of the newly configured channel
 * @return success or failure status of the function call
 * @warning Any configuration that may have existed on the channel before this
 *      operation will be lost in the process.  Any handles to objects on those channels
 *      will no longer be valid.
 * @note The handles must be destroyed by a429UtilsDestroyHandle() when no longer in use.
 */
A429_API_FUNC A429Return a429DcConfigBin(const char* aBinPath, uint8_t aChannelNumber,
        A429Handle aBoardHandle, A429Handle* apTxDataCorrupterChannelHandle);

/**
 * Defines a corrupter channel based on a saved configuration from an XML file.
 *
 * @param aSchemaPath path to the ait_429.xsd schema file
 * @param aXmlPath path to the XML data file
 * @param aXmlXPath XPath expression to extract the desired configuration
 * @param aChannelNumber channel number to apply the configuration to
 * @param aBoardHandle handle for the board on which to configure the channel
 * @param[out] apTxDataCorrupterChannelHandle handle of the newly configured channel
 * @return success or failure status of the function call
 * @warning Any configuration that may have existed on the channel before this
 *      operation will be lost in the process.  Any handles to objects on those channels
 *      will no longer be valid.
 * @note The handles must be destroyed by a429UtilsDestroyHandle() when no longer in use.
 */
A429_API_FUNC A429Return a429DcConfigXml(const char* aSchemaPath, const char* aXmlPath,
        const char* aXmlXPath, uint8_t aChannelNumber, A429Handle aBoardHandle,
        A429Handle* apTxDataCorrupterChannelHandle);

/**
 * Gets the source channel this corrupter is getting its data from.
 *
 * @param aChannelHandle handle of the channel to inspect
 * @param[out] apChannelNumber the source channel number (1-indexed)
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429DcGetSourceChannelNumber(A429Handle aChannelHandle,
        uint8_t* apChannelNumber);

/**
 * Sets the source channel this corrupter is getting its data from.
 *
 * @param aChannelHandle handle of the channel to inspect
 * @param aChannelNumber the source channel number (1-indexed)
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429DcSetSourceChannelNumber(A429Handle aChannelHandle,
        uint8_t aChannelNumber);

/**
 * Sets the corrupter to perform no corruption operations on the given label for
 * all SDI values within it.
 *
 * @param aChannelHandle handle of the channel to inspect
 * @param aLabel label on which to modify corruption behavior
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429DcSetNoOperationByLabel(A429Handle aChannelHandle,
        uint8_t aLabel);

/**
 * Sets the corrupter to perform no corruption operations on the specific
 * label and SDI pair.
 *
 * @param aChannelHandle handle of the channel to inspect
 * @param aLabel label on which to modify corruption behavior
 * @param aSdi sdi value on which to modify corruption behavior
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429DcSetNoOperationByLabelSdi(A429Handle aChannelHandle,
        uint8_t aLabel, uint8_t aSdi);

/**
 * Sets the corrupter to remove the given label for all SDI values within it from 
 * the data stream.
 *
 * @param aChannelHandle handle of the channel to inspect
 * @param aLabel label on which to modify corruption behavior
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429DcSetLabelRemovedByLabel(A429Handle aChannelHandle,
        uint8_t aLabel);

/**
 * Sets the corrupter to remove the given label and SDI pair from the data stream.
 *
 * @param aChannelHandle handle of the channel to inspect
 * @param aLabel label on which to modify corruption behavior
 * @param aSdi sdi value on which to modify corruption behavior
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429DcSetLabelRemovedByLabelSdi(A429Handle aChannelHandle,
        uint8_t aLabel, uint8_t aSdi);

/**
 * Sets the corrupter to insert an extra bit on the given label for all SDI
 * values within it.
 *
 * @param aChannelHandle handle of the channel to inspect
 * @param aLabel label on which to modify corruption behavior
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429DcSetBitInsertionByLabel(A429Handle aChannelHandle,
        uint8_t aLabel);

/**
 * Sets the corrupter to insert an extra bit on the specific label and SDI pair.
 *
 * @param aChannelHandle handle of the channel to inspect
 * @param aLabel label on which to modify corruption behavior
 * @param aSdi sdi value on which to modify corruption behavior
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429DcSetBitInsertionByLabelSdi(A429Handle aChannelHandle,
        uint8_t aLabel, uint8_t aSdi);

/**
 * Sets the corrupter to remove a bit from the given label for all SDI values 
 * within it.
 *
 * @param aChannelHandle handle of the channel to inspect
 * @param aLabel label on which to modify corruption behavior
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429DcSetBitRemovalByLabel(A429Handle aChannelHandle,
        uint8_t aLabel);

/**
 * Sets the corrupter to remove a bit from the specific label and SDI pair.
 *
 * @param aChannelHandle handle of the channel to inspect
 * @param aLabel label on which to modify corruption behavior
 * @param aSdi sdi value on which to modify corruption behavior
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429DcSetBitRemovalByLabelSdi(A429Handle aChannelHandle,
        uint8_t aLabel, uint8_t aSdi);

/**
 * Sets the corrupter to introduce a parity error on the given label for all SDI
 * values within it.
 *
 * @param aChannelHandle handle of the channel to inspect
 * @param aLabel label on which to modify corruption behavior
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429DcSetParityErrorByLabel(A429Handle aChannelHandle,
        uint8_t aLabel);

/**
 * Sets the corrupter to introduce a parity error on the specific label and SDI
 * pair.
 *
 * @param aChannelHandle handle of the channel to inspect
 * @param aLabel label on which to modify corruption behavior
 * @param aSdi sdi value on which to modify corruption behavior
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429DcSetParityErrorByLabelSdi(A429Handle aChannelHandle,
        uint8_t aLabel, uint8_t aSdi);

/**
 * Sets the corrupter to apply a corruption function on the given label for all SDI
 * values within it.
 *
 * @param aChannelHandle handle of the channel to inspect
 * @param aLabel label on which to modify corruption behavior
 * @param aOptions the options to use for the corruption function
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429DcSetCorruptionFunctionByLabel(A429Handle aChannelHandle,
        uint8_t aLabel, A429DataCorruptionOptions aOptions);

/**
 * Sets the corrupter to apply a corruption function on the specific label and SDI
 * pair.
 *
 * @param aChannelHandle handle of the channel to inspect
 * @param aLabel label on which to modify corruption behavior
 * @param aSdi sdi value on which to modify corruption behavior
 * @param aOptions the options to use for the corruption function
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429DcSetCorruptionFunctionByLabelSdi(A429Handle aChannelHandle,
        uint8_t aLabel, uint8_t aSdi, A429DataCorruptionOptions aOptions);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* !A429_DC_CHANNEL_H */
