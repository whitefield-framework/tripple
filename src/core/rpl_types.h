/*
 * Copyright (C) 2020 Authors of Tripple
 *
 * This file is subject to the terms and conditions. See the file LICENSE in
 * the top level directory for more details.
 */

/**
 * @ingroup     CORE
 * @{
 *
 * @file
 * @brief       data types and constants
 *
 * @}
 */

#ifndef _RPL_TYPES_H_
#define _RPL_TYPES_H_

#include <stdint.h>
#include <init.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#define RPL_TRUE           1
#define RPL_FALSE          0

/* Standard Data Types */
/*typedef long                    long_t;
typedef unsigned long           ulong_t;
typedef long long               int64_t;
typedef unsigned long long      uint64_t;*/
typedef uint8_t                 bool_t;
typedef uint16_t                rpl_rank_t;


/* User Defined Data Types */

#ifdef __cplusplus
}
#endif

#endif /*_RPL_TYPES_H_*/

