/**
 * @file a429_utils.h
 * @brief A429 API utility functions.
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

#ifndef A429_UTILS_H
#define A429_UTILS_H

#include <a429/a429_defines.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup utils Utility functions
 * Miscellaneous utility functions.
 * @{
 */

/**
 * Sets the debugging output level for the API.  This will affect messages
 * printed during execution that may aid in debugging.
 * <p>
 * Debug level can be changed on the fly, at any time.
 *
 * @param aLevel the new debug level
 */
A429_API_FUNC void a429UtilsSetDebugLevel(A429DebugLevel aLevel);

/**
 * Reclaims resources allocated by the given handle.  After this call
 * the handle will no longer be valid for use in the API.
 *
 * @param[in,out] apHandle handle to destroy
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429UtilsDestroyHandle(A429Handle* apHandle);

/**
 * Gets a string message that describes a return code.
 *
 * @param aCode return code to describe
 * @return message that describes the return code
 */
A429_API_FUNC const char* a429UtilsErrorString(A429Return aCode);

/**
 * Gets the channel number of the channel referenced by the given handle. The
 * referenced channel can be of any type.
 *
 * @param aChannelHandle handle to a channel to inspect
 * @param[out] apChannelNumber channel number (1-indexed)
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429UtilsGetChannelNumber(A429Handle aChannelHandle,
        uint8_t* apChannelNumber);

/**
 * Gets BCD data encoded in the ARINC-429 data word.
 *
 * @param aWord ARINC-429 data word
 * @return value of the BCD data
 */
A429_API_FUNC uint32_t a429UtilsGetBcdData(uint32_t aWord);

/**
 * Gets the 8-bit label of the ARINC-429 data word.
 *
 * @param aWord ARINC-429 data word
 * @return label from the data word
 */
A429_API_FUNC uint8_t a429UtilsGetLabel(uint32_t aWord);

/**
 * Gets the value of the parity bit in the ARINC-429 data word.
 *
 * @param aWord ARINC-429 data word
 * @return value of parity bit (0 or 1)
 */
A429_API_FUNC uint8_t a429UtilsGetParityBit(uint32_t aWord);

/**
 * Gets the 2-bit SDI value in the ARINC-429 data word.
 *
 * @param aWord ARINC-429 data word
 * @return SDI value
 */
A429_API_FUNC uint8_t a429UtilsGetSdi(uint32_t aWord);

/**
 * Gets the 19-bit signed BNR data from the ARINC-429 data word.
 *
 * @param aWord ARINC-429 data word
 * @return value of the 19-bit signed data
 */
A429_API_FUNC int32_t a429UtilsGetSigned19BitData(uint32_t aWord);

/**
 * Gets the 21-bit signed BNR data from the ARINC-429 data word.
 *
 * @param aWord ARINC-429 data word
 * @return value of the 21-bit signed data
 */
A429_API_FUNC int32_t a429UtilsGetSigned21BitData(uint32_t aWord);

/**
 * Gets the 2-bit SSM value in the ARINC-429 data word.
 *
 * @param aWord ARINC-429 data word
 * @return SSM value
 */
A429_API_FUNC uint8_t a429UtilsGetSsm(uint32_t aWord);

/**
 * Gets the 19-bit unsigned BNR value from the ARINC-429 data word.
 *
 * @param aWord ARINC-429 data word
 * @return 19-bit unsigned data from the word
 */
A429_API_FUNC uint32_t a429UtilsGetUnsigned19BitData(uint32_t aWord);

/**
 * Gets the 21-bit unsigned BNR value from the ARINC-429 data word.
 *
 * @param aWord ARINC-429 data word
 * @return 21-bit unsigned data from the word
 */
A429_API_FUNC uint32_t a429UtilsGetUnsigned21BitData(uint32_t aWord);

/**
 * Gets the 23-bit unsigned BNR value from the ARINC-429 data word.
 *
 * @param aWord ARINC-429 data word
 * @return 23-bit unsigned data from the word
 */
A429_API_FUNC uint32_t a429UtilsGetUnsigned23BitData(uint32_t aWord);

/**
 * Encodes and sets the given value into the ARINC-429 data word.
 *
 * @param aWord ARINC-429 data word
 * @param aData value to encode and place into the data field as BCD
 * @return modified ARINC-429 data word
 */
A429_API_FUNC uint32_t a429UtilsSetBcdData(uint32_t aWord, uint32_t aData);

/**
 * Sets the given label into the ARINC-429 data word.
 *
 * @param aWord ARINC-429 data word
 * @param aLabel label to set into the data word
 * @return modified ARINC-429 data word
 */
A429_API_FUNC uint32_t a429UtilsSetLabel(uint32_t aWord, uint8_t aLabel);

/**
 * Sets the parity bit in the ARINC-429 data word to maintain odd
 * parity.
 *
 * @param aWord ARINC-429 data word
 * @return modified ARINC-429 data word
 */
A429_API_FUNC uint32_t a429UtilsSetOddParity(uint32_t aWord);

/**
 * Sets the parity bit in the ARINC-429 data word to the desired value.
 *
 * @param aWord ARINC-429 data word
 * @param aParityBit the desired parity bit value
 * @return modified ARINC-429 data word
 */
A429_API_FUNC uint32_t a429UtilsSetParityBit(uint32_t aWord, uint8_t aParityBit);

/**
 * Sets the 2-bit SDI value of the ARINC-429 data word to the desired value.
 *
 * @param aWord ARINC-429 data word
 * @param aSdi the desired 2-bit SDI value
 * @return modified ARINC-429 data word
 */
A429_API_FUNC uint32_t a429UtilsSetSdi(uint32_t aWord, uint8_t aSdi);

/**
 * Sets the signed 19-bit BNR value into the ARINC-429 data word.
 *
 * @param aWord ARINC-429 data word
 * @param aData signed value to set into data word
 * @return modified ARINC-429 data word
 */
A429_API_FUNC uint32_t a429UtilsSetSigned19BitData(uint32_t aWord, int32_t aData);

/**
 * Sets the signed 21-bit BNR value into the ARINC-429 data word.
 *
 * @param aWord ARINC-429 data word
 * @param aData signed value to set into data word
 * @return modified ARINC-429 data word
 */
A429_API_FUNC uint32_t a429UtilsSetSigned21BitData(uint32_t aWord, int32_t aData);

/**
 * Sets the 2-bit SSM value of the ARINC-429 data word to the desired value.
 *
 * @param aWord ARINC-429 data word
 * @param aSsm the desired 2-bit SSM value
 * @return modified ARINC-429 data word
 */
A429_API_FUNC uint32_t a429UtilsSetSsm(uint32_t aWord, uint8_t aSsm);

/**
 * Sets the unsigned 19-bit BNR value into the ARINC-429 data word.
 *
 * @param aWord ARINC-429 data word
 * @param aData unsigned value to set into data word
 * @return modified ARINC-429 data word
 */
A429_API_FUNC uint32_t a429UtilsSetUnsigned19BitData(uint32_t aWord, uint32_t aData);

/**
 * Sets the unsigned 21-bit BNR value into the ARINC-429 data word.
 *
 * @param aWord ARINC-429 data word
 * @param aData unsigned value to set into data word
 * @return modified ARINC-429 data word
 */
A429_API_FUNC uint32_t a429UtilsSetUnsigned21BitData(uint32_t aWord, uint32_t aData);

/**
 * Sets the unsigned 23-bit BNR value into the ARINC-429 data word.
 *
 * @param aWord ARINC-429 data word
 * @param aData unsigned value to set into data word
 * @return modified ARINC-429 data word
 */
A429_API_FUNC uint32_t a429UtilsSetUnsigned23BitData(uint32_t aWord, uint32_t aData);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* !A429_UTILS_H */
