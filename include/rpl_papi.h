/*
 * Copyright (C) 2020 Authors of Tripple
 *
 * This file is subject to the terms and conditions. See the file LICENSE in
 * the top level directory for more details.
 */

/**
 * @ingroup     PAPI
 * @{
 *
 * @file
 * @brief       Tripple Platform API exported header
 *
 * @}
 */

#ifndef _RPL_PAPI_H_
#define _RPL_PAPI_H_

#include "init.h"
#include "rpl.h"
#include "rpl_configurations.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Memory  Related Functions */
/* If some platform has its memory manager modules then 
    adopt it bu writting wrapper and register the below callbacks to handle the memory
    allocation
 */
typedef void *(*pfmem_alloc)(size_t memsize);
typedef void (*pfmem_free)(void *memory);

/*********************************
    Message Processing APIs 
  *********************************/
#define RPL_ICMPV6_MSG_TYPE           155
#define RPL_CTRL_MSG_CODE_DIS         0x00
#define RPL_CTRL_MSG_CODE_DIO         0x01
#define RPL_CTRL_MSG_CODE_DAO         0x02
#define RPL_CTRL_MSG_CODE_DAO_ACK     0x03
#define RPL_CTRL_MSG_CODE_DCO         0x04
#define RPL_CTRL_MSG_CODE_DCO_ACK     0x05

typedef struct _rpl_icmpv6_context{
    uint8_t *icmpv6_msg_buff;      /* ICMPv6 Message Buffer */
    uint16_t length;               /* ICMPv6 Message length */
    rpl_ipv6_address_t *src_addr;
    rpl_ipv6_address_t *dest_addr;
    void *upperlayer_context;
}rpl_icmpv6_context_t;

/* Callback to send ICMPV6 message */
typedef int (*pfrpl_send_rpl_message)(rpl_icmpv6_context_t *message_ctx);
typedef struct _rpl_upperlayer_hooks{
    pfrpl_send_rpl_message pfsendmsg;     
}rpl_upperlayer_hooks_t;


/* Modules initialization */
typedef void * rpl_protocol_context;
typedef struct _rpl_instance_info{
    rpl_ipv6_address_t dodag_id;
    rpl_ipv6_address_t prefix;
    uint8_t            prefix_length;
    uint8_t            instance_id;
    uint8_t            join_as_root;
    uint8_t            isGrounded;
    rpl_instance_configuration_t config;
}rpl_instance_info_t;
rpl_protocol_context rpl_init(rpl_node_configurations_t *config);
int rpl_add_root_instance(rpl_protocol_context rpl_ctx,
                    rpl_instance_info_t *instnace_info);
int rpl_start(rpl_protocol_context rpl_ctx);

int rpl_icmp6_handler(rpl_protocol_context rpl_ctx, 
					rpl_icmpv6_context_t *msg_context);

#ifdef __cplusplus
}
#endif

#endif /*_RPL_PAPI_H_*/

