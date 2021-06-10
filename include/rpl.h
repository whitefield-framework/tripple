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
 * @brief       RPL Core exported header
 *
 * @}
 */

#ifndef _RPL_H_
#define _RPL_H_

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

enum {
    SUCCESS = 0,
    FAILURE,
    
    // Add specific return codes here
    RPL_ERR_INSTANCE_ROOT_EXISTS,
};

typedef struct _rpl_ipv6_address{
union{
        uint8_t    addr8[16];
        uint16_t   addr16[8];
        uint32_t   addr32[4];
    }ip6addr;
}rpl_ipv6_address_t;

typedef rpl_ipv6_address_t rpl_ipv6_prefix; 

#ifdef __cplusplus
}
#endif

#endif // _RPL_H_

