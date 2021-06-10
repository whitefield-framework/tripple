/*
 * Copyright (C) 2020 Authors of Tripple
 *
 * This file is subject to the terms and conditions. See the file LICENSE in
 * the top level directory for more details.
 */

/**
 * @ingroup     UAPI
 * @{
 *
 * @file
 * @brief       rpl control messages
 *
 * @}
 */

#ifndef _RPL_CTRL_MESSAGE_H_
#define _RPL_CTRL_MESSAGE_H_

#include <rpl_topology.h>
#include "rpl_papi.h"

/* RPL Control message option types */
#define RPL_CTRL_MSG_OPT_PAD1              0x00
#define RPL_CTRL_MSG_OPT_PADN              0x01
#define RPL_CTRL_MSG_OPT_DAG_MC            0x02
#define RPL_CTRL_MSG_OPT_RIO               0x03
#define RPL_CTRL_MSG_OPT_DODAG_CONFIG      0x04
#define RPL_CTRL_MSG_OPT_TARGET_IO         0x05
#define RPL_CTRL_MSG_OPT_TRANSIT_IO        0x06
#define RPL_CTRL_MSG_OPT_SIO               0x07
#define RPL_CTRL_MSG_OPT_PIO               0x08
#define RPL_CTRL_MSG_OPT_TARGET_DO         0x09


typedef struct _rpl_dio_message{
    uint8_t             rpl_instnace_id;
    uint8_t             dodag_version;
    rpl_rank_t          sender_rank;
    bool_t              isgrounded;
    uint8_t             mode_of_op;
    uint8_t             dodag_preference;
    uint8_t             dtsn;
    rpl_ipv6_address_t  dodag_id;
    rpl_dag_metric_container_t mc;
    rpl_dodag_prefix_t  prefix_information;
    rpl_dodag_configs_t dodag_config;
    rpl_routing_information_t  route_information;
}rpl_dio_message_t;

typedef struct _rpl_dis_message{
    rpl_ipv6_address_t  dodag_id;
    uint8_t             rpl_instance_id;
    uint8_t             version;
#define RPL_SIO_VER_PREDICATE          0x80
#define RPL_SIO_INSTANCEID_PREDICATE   0x40
#define RPL_SIO_DODAGID_PREDICATE      0x20
    uint8_t             flags;
}rpl_dis_message_t;

int rpl_dis_input(rpl_protocol_context rpl_context,
                    rpl_icmpv6_context_t *rcvd_msg_ctx);
int rpl_dio_input(rpl_protocol_context rpl_context,
                    rpl_icmpv6_context_t *rcvd_msg_ctx);
int rpl_dao_input(rpl_protocol_context rpl_context,
                    rpl_icmpv6_context_t *rcvd_msg_ctx);
int rpl_dao_ack_input(rpl_protocol_context rpl_context,
                    rpl_icmpv6_context_t *rcvd_msg_ctx);
int rpl_dco_input(rpl_protocol_context rpl_context,
                    rpl_icmpv6_context_t *rcvd_msg_ctx);
int rpl_dco_ack_input(rpl_protocol_context rpl_context,
                    rpl_icmpv6_context_t *rcvd_msg_ctx);

int rpl_send_dio(rpl_node_t *rplnode, rpl_instance_t *instance,
                rpl_ipv6_address_t *destination);


#endif /*_RPL_CTRL_MESSAGE_PARSER_H_*/

