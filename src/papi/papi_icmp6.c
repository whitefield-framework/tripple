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
 * @brief       RPL ICMPv6 handlers
 *
 * @}
 */

#include <rpl_papi.h>
#include <rpl_ctrl_message.h>

#define RPL_ICMPV6_HEADER_SIZE 4U

/**
 * @brief RPL Message handler
 *
 * @return SUCCESS/FAILURE
 */
int rpl_icmp6_handler(rpl_protocol_context rpl_context,
                        rpl_icmpv6_context_t *message_ctx)
{
    uint8_t msg_type;
    uint8_t msg_code;
    int retval = SUCCESS;
    
    /* Validate the Inputs */
    if ((NULL == message_ctx) || (NULL == message_ctx->icmpv6_msg_buff)){
        return FAILURE;
    }

    if (message_ctx->length < RPL_ICMPV6_HEADER_SIZE){
        return FAILURE;
    }

    msg_type = message_ctx->icmpv6_msg_buff[0];
    msg_code = message_ctx->icmpv6_msg_buff[1];

    /* Validate the type */
    if (msg_type != RPL_ICMPV6_MSG_TYPE){
        return FAILURE;
    }

    switch (msg_code){
        case RPL_CTRL_MSG_CODE_DIS:
            retval = rpl_dis_input(rpl_context, message_ctx);
            break;
        case RPL_CTRL_MSG_CODE_DIO:
            retval = rpl_dio_input(rpl_context, message_ctx);
            break;
        case RPL_CTRL_MSG_CODE_DAO:
            retval = rpl_dao_input(rpl_context, message_ctx);
            break;
        case RPL_CTRL_MSG_CODE_DAO_ACK:
            retval = rpl_dao_ack_input(rpl_context, message_ctx);
            break;
        case RPL_CTRL_MSG_CODE_DCO:
            retval = rpl_dco_input(rpl_context, message_ctx);
            break;
        case RPL_CTRL_MSG_CODE_DCO_ACK:
            retval = rpl_dco_ack_input(rpl_context, message_ctx);
            break;
        default:
            retval = FAILURE;
            
    }

    return retval;
}

