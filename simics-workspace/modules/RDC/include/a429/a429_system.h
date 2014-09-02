/**
 * @file a429_system.h
 * @brief A429 API system functions
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

#ifndef A429_SYSTEM_H
#define A429_SYSTEM_H

#include <a429/a429_defines.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup system System functions
 * System-level functions.
 * @{
 */

/** Maximum length of the version string */
#define A429_MAX_VERSION_STRING 256

/**
 * System information.
 */
typedef struct
{
    /** The number of boards currently installed in-system */
    uint32_t board_count;

    /** Serial numbers of installed boards (valid up to board_count) */
    uint64_t serial_numbers[A429_MAX_BOARD_COUNT];
} A429SystemInfo;

/**
 * API version information.
 */
typedef struct
{
    /**
     * A human-readable dotted-notation version string.
     * <p>
     * Example: 3.8.0.250
     */
    char string[A429_MAX_VERSION_STRING];

    /**
     * The major version number.  Changed when a significant re-design of the API
     * is done.  Changes to this typically break backwards compatibility.
     */
    uint32_t major;

    /**
     * The minor version number.  Changed when a feature enhancement or major bug
     * fix occurs.  Minor version changes are intended to maintain backwards compatibility.
     */
    uint32_t minor;

    /**
     * The maintenance version number.  Changed when a minor bug fix occurs.
     */
    uint32_t maint;

    /**
     * The build revision.  Intended for internal use.
     */
    uint32_t revision;
} A429VersionInfo;

/**
 * Gets information about the hardware available in the system.
 *
 * @param[out] apSystemInfo system information structure
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429SystemGetSystemInfo(A429SystemInfo* apSystemInfo);

/**
 * Gets information about the version of the API.
 *
 * @param[out] apVersionInfo version information structure
 * @return success or failure status of the function call
 */
A429_API_FUNC A429Return a429SystemGetVersionInfo(A429VersionInfo* apVersionInfo);

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* !A429_SYSTEM_H */
