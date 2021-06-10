/**
 * @file
 * Tripple initialization API
 */

/*
 * Copyright (C) 2020 Authors of Tripple
 *
 * This file is subject to the terms and conditions. See the file LICENSE in
 * the top level directory for more details.
 */

/**
 * @ingroup     Core
 * @{
 *
 * @file
 * @brief       RPL Initialization
 *
 * @}
 */

#ifndef TRPL_HDR_INIT_H
#define TRPL_HDR_INIT_H

// #include "lwip/opt.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup rpl_version Version
 * @ingroup rpl
 * @{
 */

/** X.x.x: Major version of the stack */
#define TRPL_VERSION_MAJOR      0
/** x.X.x: Minor version of the stack */
#define TRPL_VERSION_MINOR      1
/** x.x.X: Revision of the stack */
#define TRPL_VERSION_REVISION   0
/** For release candidates, this is set to 1..254
* For official releases, this is set to 255 (TRPL_RC_RELEASE)
* For development versions (Git), this is set to 0 (TRPL_RC_DEVELOPMENT) */
#define TRPL_VERSION_RC         TRPL_RC_RELEASE

/** TRPL_VERSION_RC is set to TRPL_RC_RELEASE for official releases */
#define TRPL_RC_RELEASE         255
/** TRPL_VERSION_RC is set to TRPL_RC_DEVELOPMENT for Git versions */
#define TRPL_RC_DEVELOPMENT     0

#define TRPL_VERSION_IS_RELEASE     (TRPL_VERSION_RC == TRPL_RC_RELEASE)
#define TRPL_VERSION_IS_DEVELOPMENT (TRPL_VERSION_RC == TRPL_RC_DEVELOPMENT)
#define TRPL_VERSION_IS_RC          ((TRPL_VERSION_RC != TRPL_RC_RELEASE) && (TRPL_VERSION_RC != TRPL_RC_DEVELOPMENT))

/* Some helper defines to get a version string */
#define TRPL_VERSTR2(x) #x
#define TRPL_VERSTR(x) TRPL_VERSTR2(x)
#if TRPL_VERSION_IS_RELEASE
#define TRPL_VERSION_STRING_SUFFIX ""
#elif TRPL_VERSION_IS_DEVELOPMENT
#define TRPL_VERSION_STRING_SUFFIX "d"
#else
#define TRPL_VERSION_STRING_SUFFIX "rc" TRPL_VERSTR(TRPL_VERSION_RC)
#endif

/** Provides the version of the stack */
#define TRPL_VERSION   ((TRPL_VERSION_MAJOR) << 24   | (TRPL_VERSION_MINOR) << 16 | \
						(TRPL_VERSION_REVISION) << 8 | (TRPL_VERSION_RC))
/** Provides the version of the stack as string */
#define TRPL_VERSION_STRING     TRPL_VERSTR(TRPL_VERSION_MAJOR) "." TRPL_VERSTR(TRPL_VERSION_MINOR) "." TRPL_VERSTR(TRPL_VERSION_REVISION) TRPL_VERSION_STRING_SUFFIX

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif /* TRPL_HDR_INIT_H */
