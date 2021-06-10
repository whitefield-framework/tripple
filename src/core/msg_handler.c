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
 * @brief       RPL Message handler
 *
 * @}
 */

#include "rpl.h"
#include "rpl_ctrl_message.h"
#include "rpl_utils.h"

#define RPL_MSG_ICMPV6_HEADER_SIZE          4U
#define RPL_DIS_MSG_BASE_OBJ_SIZE           2U
#define RPL_CTRL_MSG_OPTIONS_FIXED_SIZE     2U
#define RPL_CTRL_MSG_OPT_PAD1_LEN           1U
#define RPL_SIO_VID_MASK                    0xE0

/**
 * @brief RPL Message handler
 *
 * @return SUCCESS/FAILURE
 */

/*
  0                                     1                                     2
  0  1  2  3  4  5  6   7  8  9   0   1  2  3  4  5  6  7   8  9  0  1  2  3
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
| Flags | Reserved | Option(s)...
+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

Options: Pad1, PadN and Solicited Information Option

 RPL_Instance ID(1) + Flag(1) + DODAG_ID (16) + Version Number (1) = 19 
 */

#define RPL_SIO_OPTION_DATA_SIZE   19U
static int rpl_parse_solicited_info_option_data(uint8_t *msg_buffer,
                    uint16_t offset, uint16_t opt_data_length,
                    rpl_dis_message_t *dis_msg)
{
    uint16_t cur_index = offset;

    if (opt_data_length < RPL_SIO_OPTION_DATA_SIZE){
        return FAILURE;
    }

    dis_msg->rpl_instance_id = msg_buffer[cur_index++];
    dis_msg->flags = msg_buffer[cur_index++];
    memcpy(dis_msg->dodag_id.ip6addr.addr8, (msg_buffer + cur_index), 
        sizeof(dis_msg->dodag_id));

    return SUCCESS;
    
}

static void rpl_handle_mcast_dis(rpl_node_t *rplnode,
    rpl_icmpv6_context_t *rcvd_msg_ctx, rpl_dis_message_t *dis_msg)
{
    rpl_instance_t *instance;

    /* Check if Solicited Information is present or not.
            If its present but all predicate are not set then no need to reset 
            the trickle just return 
        */
    if (dis_msg->flags & RPL_SIO_VID_MASK){
        /* If all predicate are not set then return */
        if (dis_msg->flags & RPL_SIO_VID_MASK !=
            (RPL_SIO_VER_PREDICATE | RPL_SIO_INSTANCEID_PREDICATE |
                RPL_SIO_DODAGID_PREDICATE)){
            return;
        }

        /* Find the RPL Instnace By uisng the instnace-id received in the SIO */
        instance = rpl_find_instnace(rplnode, dis_msg->rpl_instance_id);
        if (NULL == instance){
            return;
        }

        if (instance->dodag.node_role == RPL_NODE_TYPE_LEAF 
            || memcmp(&(instance->dodag.dodag_id), &(dis_msg->dodag_id),
                    sizeof(rpl_ipv6_address_t)) ||
             instance->dodag.dodag_version != dis_msg->version){
            return;
        }

        /* Reste the DIO trickle timer */
    }
    else{
        /* Scan All the RPL Instnaces and reset the trickle timer , if the node 
                  is not a leaf node in that instance*/
        instance = rplnode->rpl_instance_list;
        while (instance){
            if (instance->dodag.node_role != RPL_NODE_TYPE_LEAF){
                /* Reset the DIO trickle TImer */
            }

            instance = instance->next;
        }
    }  
}

static void rpl_handle_ucast_dis(rpl_node_t *rplnode,
    rpl_icmpv6_context_t *rcvd_msg_ctx, rpl_dis_message_t *dis_msg)
{
    rpl_instance_t *cur_instance;
    
    /* For Unicast DIS if Solicited Information is not present then just send 
           the unicast DIO */
    if (dis_msg->flags & RPL_SIO_VID_MASK){
        if (dis_msg->flags & RPL_SIO_INSTANCEID_PREDICATE){
            cur_instance = rpl_find_instnace(rplnode, dis_msg->rpl_instance_id);
            if (NULL == cur_instance){
                return;
            }

            /* If DODAG and Version Predicate are valid check them else
                        send a DIO using this instnace */
            if ((dis_msg->flags & RPL_SIO_DODAGID_PREDICATE &&
                memcmp(&(cur_instance->dodag.dodag_id), &(dis_msg->dodag_id),
                    sizeof(rpl_ipv6_address_t))) ||
                ((dis_msg->flags & RPL_SIO_VER_PREDICATE) &&
                cur_instance->dodag.dodag_version != dis_msg->version)){
                return;
            }
                
            /* Send DIO Message to the destination address */
            rpl_send_dio(rplnode, cur_instance, rcvd_msg_ctx->dest_addr);
        }
    }
    else{
        /* Should we send the DIO message for each of the RPL instnace a Node 
                  is part of ?*/
        cur_instance = rplnode->rpl_instance_list;
        while(cur_instance){
            rpl_send_dio(rplnode, cur_instance, rcvd_msg_ctx->dest_addr);
            cur_instance = cur_instance->next;
        }
    }

    return;
}

static int rpl_handle_dis(rpl_protocol_context rpl_context,
    rpl_icmpv6_context_t *rcvd_msg_ctx, rpl_dis_message_t *dis_msg)
{
    rpl_node_t *rplnode = (rpl_node_t *)rpl_context;
    if (RPL_UTIL_IS_ADDR_MULTICAST(rcvd_msg_ctx->dest_addr)){
       rpl_handle_mcast_dis(rplnode, rcvd_msg_ctx, dis_msg);
    }
    else{
        /* Unicast DIS */
        rpl_handle_ucast_dis(rplnode, rcvd_msg_ctx, dis_msg);
    }

    return SUCCESS;
}

int rpl_dis_input(rpl_protocol_context rpl_context,
                    rpl_icmpv6_context_t *rcvd_msg_ctx)
{
    uint8_t    *msg_buffer = (rcvd_msg_ctx->icmpv6_msg_buff + 
                                RPL_MSG_ICMPV6_HEADER_SIZE);
    uint16_t   msg_length = rcvd_msg_ctx->length - RPL_MSG_ICMPV6_HEADER_SIZE;
    uint16_t   opts_length;
    uint8_t    cur_index;
    uint8_t    opt_type;
    uint8_t    cur_opt_length;
    rpl_dis_message_t dis_msg;
    int retval = SUCCESS;

    /* Validate Base Object Length */
    if (msg_length < RPL_DIS_MSG_BASE_OBJ_SIZE){
        return FAILURE;
    }

    opts_length = msg_length - RPL_DIS_MSG_BASE_OBJ_SIZE;
    cur_index = RPL_DIS_MSG_BASE_OBJ_SIZE;
    if (opts_length > 0){
        while (opts_length >= RPL_CTRL_MSG_OPTIONS_FIXED_SIZE){
            /* Get the Option Type and Length */
            opt_type = msg_buffer[cur_index++];
            if (opt_type == RPL_CTRL_MSG_OPT_PAD1){
                opts_length -= RPL_CTRL_MSG_OPT_PAD1_LEN;
                continue;
            }
            
            cur_opt_length = msg_buffer[cur_index++];
            
            /* Validate Data is present. PADN can only have length 0*/
            if ((!cur_opt_length && opt_type != RPL_CTRL_MSG_OPT_PADN) ||
                ((opts_length - RPL_CTRL_MSG_OPTIONS_FIXED_SIZE) <
                cur_opt_length)){
                return FAILURE;
            }
            
            switch (opt_type){
                case RPL_CTRL_MSG_OPT_PADN:
                    opts_length -= cur_opt_length;
                    break;
                case RPL_CTRL_MSG_OPT_SIO:
                    if (rpl_parse_solicited_info_option_data(msg_buffer,
                           cur_index, cur_opt_length, &dis_msg) != SUCCESS){
                        return FAILURE;
                    }

                    opts_length -= cur_opt_length;
                    cur_index += cur_opt_length;
                    break;
                default:
                    /* Option Type value is not recognized by the receiver, the receiver
                                      MUST silently ignore the unrecognized option */
                    opts_length -= cur_opt_length;
                    cur_index += cur_opt_length;
            }
        } 
    }

    retval = rpl_handle_dis(rpl_context, rcvd_msg_ctx, &dis_msg);
    return retval;
}

int rpl_dio_input(rpl_protocol_context rpl_context,
                    rpl_icmpv6_context_t *rcvd_msg_ctx)
{
    uint8_t    *msg_buffer = (rcvd_msg_ctx->icmpv6_msg_buff + 
                                RPL_MSG_ICMPV6_HEADER_SIZE);
    uint16_t   msg_length = rcvd_msg_ctx->length - RPL_MSG_ICMPV6_HEADER_SIZE;
    uint16_t   cur_index = 0;
    uint16_t   bytes_parsed = 0;
}

int rpl_dao_input(rpl_protocol_context rpl_context,
                     rpl_icmpv6_context_t *rcvd_msg_ctx)
{
    uint8_t    *msg_buffer = (rcvd_msg_ctx->icmpv6_msg_buff + 
                                RPL_MSG_ICMPV6_HEADER_SIZE);
    uint16_t   msg_length = rcvd_msg_ctx->length - RPL_MSG_ICMPV6_HEADER_SIZE;
    uint16_t   cur_index = 0;
    uint16_t   bytes_parsed = 0;
}

int rpl_dao_ack_input(rpl_protocol_context rpl_context,
                            rpl_icmpv6_context_t *rcvd_msg_ctx)
{
    uint8_t    *msg_buffer = (rcvd_msg_ctx->icmpv6_msg_buff + 
                                RPL_MSG_ICMPV6_HEADER_SIZE);
    uint16_t   msg_length = rcvd_msg_ctx->length - RPL_MSG_ICMPV6_HEADER_SIZE;
    uint16_t   cur_index = 0;
    uint16_t   bytes_parsed = 0;
}

int rpl_dco_input(rpl_protocol_context rpl_context,
                    rpl_icmpv6_context_t *rcvd_msg_ctx)
{
    uint8_t    *msg_buffer = (rcvd_msg_ctx->icmpv6_msg_buff + 
                                RPL_MSG_ICMPV6_HEADER_SIZE);
    uint16_t   msg_length = rcvd_msg_ctx->length - RPL_MSG_ICMPV6_HEADER_SIZE;
    uint16_t   cur_index = 0;
    uint16_t   bytes_parsed = 0;
}

int rpl_dco_ack_input(rpl_protocol_context rpl_context,
                            rpl_icmpv6_context_t *rcvd_msg_ctx)
{
    uint8_t    *msg_buffer = (rcvd_msg_ctx->icmpv6_msg_buff + 
                                RPL_MSG_ICMPV6_HEADER_SIZE);
    uint16_t   msg_length = rcvd_msg_ctx->length - RPL_MSG_ICMPV6_HEADER_SIZE;
    uint16_t   cur_index = 0;
    uint16_t   bytes_parsed = 0;
}


int rpl_send_dio(rpl_node_t *rplnode, rpl_instance_t *instance,
                rpl_ipv6_address_t *destination){
}

