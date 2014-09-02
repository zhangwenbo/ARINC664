/**
 * @file a429_defines.h
 * @brief A429 API core type definitions
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

#ifndef A429_DEFINES_H
#define A429_DEFINES_H

#ifndef WIN32
#include <stdint.h>
#endif

/**
 * @defgroup core Core types
 * Core API type definitions.
 * @{
 */

#ifdef WIN32

/** Signed 8-bit integer type */
typedef char int8_t;

/** Unsigned 8-bit integer type */
typedef unsigned char uint8_t;

/** Signed 16-bit integer type */
typedef short int16_t;

/** Unsigned 16-bit integer type */
typedef unsigned short uint16_t;

#if defined( __LP64__ )
/** Signed 32-bit integer type */
typedef int int32_t;

/** Unsigned 32-bit integer type*/
typedef unsigned int uint32_t;
#else
/** Signed 32-bit integer type */
typedef long int32_t;

/** Unsigned 32-bit integer type */
typedef unsigned long uint32_t;
#endif /* !__LP64__ */

/** Signed 64-bit integer type */
typedef long long int64_t;

/** Unsigned 64-bit integer type */
typedef unsigned long long uint64_t;

/** Verification of datatype definitions.*/
static union
{
    char int8_t_incorrect [sizeof(int8_t) == 1 ? 1 : -1];
    char uint8_t_incorrect [sizeof(uint8_t) == 1 ? 1 : -1];
    char int16_t_incorrect [sizeof(int16_t) == 2 ? 1 : -1];
    char uint16_t_incorrect [sizeof(uint16_t) == 2 ? 1 : -1];
    char int32_t_incorrect [sizeof(int32_t) == 4 ? 1 : -1];
    char uint32_t_incorrect [sizeof(uint32_t) == 4 ? 1 : -1];
    char int64_t_incorrect [sizeof(int64_t) == 8 ? 1 : -1];
    char uint64_t_incorrect [sizeof(uint64_t) == 8 ? 1 : -1];
}StdintTypedefChecks;
#endif

#if defined(SWIG) || !defined(WIN32)
#if defined(__linux__) && defined(__GNUC__)
    #define A429_API_FUNC __attribute__ ((visibility ("default")))
#else
    #define A429_API_FUNC
#endif
#else
#ifdef EXPORT_A429_API
/** Used for importing/exporting symbols from a DLL in Windows. */
#define A429_API_FUNC __declspec(dllexport)
#else
/** Used for importing/exporting symbols from a DLL in Windows. */
#define A429_API_FUNC __declspec(dllimport)
#endif
#endif

/** Forward declaration of structure backing the A429Handle */
struct A429OpaqueHandle;

/** A handle by which resources are accessed */
typedef struct A429OpaqueHandle* A429Handle;

/** Maximum number of boards supported by the API */
#define A429_MAX_BOARD_COUNT 1024

/** Maximum number of supported channels */
#define A429_MAX_CHANNELS 64

/** Maximum number of channel handles configured at a time */
#define A429_MAX_CHANNEL_HANDLES A429_MAX_CHANNELS

/**
 * Indicates a channel speed selection.
 */
typedef enum
{
    /** High speed channel (100kHz) */
    A429_CHANNEL_SPEED_HIGH,

	/** Intermediate speed channel (50kHz) */
	A429_CHANNEL_SPEED_INTERMEDIATE,

    /** Low speed channel (12.5kHz) */
    A429_CHANNEL_SPEED_LOW,
} A429ChannelSpeed;

/**
 * Available debugging levels.
 */
typedef enum
{
    /** Print no debug information */
    A429_DEBUG_NONE,

    /** Print errors to stderr as they occur */
    A429_DEBUG_ERROR
} A429DebugLevel;

/**
 * Enumeration of potential values returned from API function calls.
 *
 * @see a429UtilsErrorString
 */
typedef enum
{
    /** The call was successful, no errors */
    A429_SUCCESS,

    /** A general error occurred */
    A429_ERROR,

    /** A required parameter was invalid */
    A429_ERROR_PARAM_INVALID,

    /** A required parameter was out of its valid range */
    A429_ERROR_PARAM_OUT_OF_RANGE,

    /** The loaded configuration was not valid or had an error */
    A429_ERROR_INVALID_CONFIGURATION,

    /** A requested resource does not exist */
    A429_ERROR_RESOURCE_NOT_FOUND,

    /** A requested operation is not supported on this platform */
    A429_ERROR_UNSUPPORTED_OPERATION,
} A429Return;

/**
 * Represents a point in time.
 */
typedef struct
{
    /** The day [0,365] */
    uint16_t day;

    /** The hour [0,24) */
    uint8_t hour;

    /** The minute [0,60) */
    uint8_t minute;

    /** The second [0,60) */
    uint8_t second;

    /** The microsecond [0,1000000) */
    uint32_t microsecond;
} A429TimeTag;

/**
 * Types of error injection available.
 */
typedef enum
{
    /** No error injection, send data as defined */
    A429_INJECT_NONE,

    /** Transfer an additional bit (33) with each data word */
    A429_INJECT_BIT_COUNT_HIGH,

    /** Transfer one less bit (31) than defined for each data word */
    A429_INJECT_BIT_COUNT_LOW,

    /** Change the inter-message gap to 3 bit times */
    A429_INJECT_GAP_ERROR,

    /** Use even parity, inverting the correct parity bit on each data word */
    A429_INJECT_PARITY_ERROR,
} A429ErrorInjectionType;

/** @} */

/**
 * @example api_loopback.c
 * @example xml_loopback.c
 */

#endif /* !A429_DEFINES_H */
