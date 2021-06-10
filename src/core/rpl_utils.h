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
 * @brief       Common utility functions
 *
 * @}
 */

#ifndef _RPL_UTILS_H_
#define _RPL_UTILS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include<rpl_topology.h>

#define RPL_UTIL_IS_ADDR_MULTICAST(address) \
    (((address)->ip6addr.addr8[0]) == 0xFF)

rpl_instance_t *rpl_find_instnace(rpl_node_t *rpl_node, uint8_t instance_id);


#ifdef __cplusplus
}
#endif

#endif /*_RPL_UTILS_H_*/

