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
 * @brief       RPL Instance and DODAG related functions
 *
 * @}
 */

#include "rpl_topology.h"

rpl_node_t g_rpl_node;

#if RPL_USE_STATIC_ALLOCATION
rpl_instance_t g_rpl_instance_pool[RPL_MAXIMUM_RPL_INSTNACE];
#endif

rpl_instance_t * rpl_alloc_new_instnace(){
    rpl_instance_t *new_instance = NULL;

#if RPL_USE_STATIC_ALLOCATION
    int i = 0;

    for (; i < RPL_MAXIMUM_RPL_INSTNACE; i++){
        if (!g_rpl_instance_pool[i].is_used){
            memset(&(g_rpl_instance_pool[i]), 0, sizeof(rpl_instance_t));
            new_instance = &(g_rpl_instance_pool[i]);
            new_instance->is_used = RPL_TRUE;
            break;
        }
    }
#else
    /* Use Dynamic Memory Allocation */
#endif

    return new_instance;
}

rpl_instance_t *rpl_find_instnace(rpl_node_t *rpl_node, uint8_t instance_id){
    rpl_instance_t *cur_instnace = rpl_node->rpl_instance_list;

    while(cur_instnace){
        if (cur_instnace->rpl_instance_id == instance_id){
            break;
        }

        cur_instnace = cur_instnace->next;
    }

    return cur_instnace;
}

rpl_protocol_context rpl_init(rpl_node_configurations_t *config){
    memset(&g_rpl_node, 0 , sizeof(rpl_node_t));
    g_rpl_node.config.stNodeConfig = *config;
    return (rpl_protocol_context)(&g_rpl_node);
}

int rpl_add_root_instance(rpl_protocol_context rpl_ctx,
                    rpl_instance_info_t *instnace_info){
    rpl_node_t *node = (rpl_node_t *)rpl_ctx;
    rpl_instance_t *cur_instance = NULL;
    rpl_dodag_t *cur_dodag = NULL;
    bool_t poision_route = RPL_FALSE;
    
    if (NULL == rpl_ctx || NULL == instnace_info ||
        instnace_info->join_as_root == RPL_FALSE){
        return FAILURE;
    }

    /* 
            A node at most will be part of one DODAG in one instnace.
            It can be root of the DODAG or a normal node in that instnace.
      */

    cur_instance = rpl_find_instnace(node, instnace_info->instance_id);
    if (cur_instance != NULL){
        /* Check if we have already joined a do dag in this instance and its 
                a root in that DODAG */
        if (cur_instance->dodag.node_role == RPL_NODE_TYPE_BR){
            return RPL_ERR_INSTANCE_ROOT_EXISTS;
        }

        /* 
                Node will act as BR in this current DODAG. It need the poision 
                the routes for which this is the forwarding node
            */
        cur_dodag = &(cur_instance->dodag);
        poision_route = RPL_TRUE;
    }
    else{
        cur_instance = rpl_alloc_new_instnace();
        if (NULL == cur_instance){
            return FAILURE;
        }

        cur_instance->rpl_instance_id = instnace_info->instance_id;
        cur_instance->next = node->rpl_instance_list;
        node->rpl_instance_list = cur_instance;

        cur_dodag = &(cur_instance->dodag);
    }

    /* Copy the information to DODAG */
    memcpy(cur_dodag->dodag_id.ip6addr.addr8, 
                instnace_info->dodag_id.ip6addr.addr8,
                sizeof(instnace_info->dodag_id.ip6addr));
    cur_dodag->dodag_prefix.prefix_length = instnace_info->prefix_length;
    memcpy(cur_dodag->dodag_prefix.dodag_prefix.ip6addr.addr8, 
                instnace_info->prefix.ip6addr.addr8,
                sizeof(instnace_info->dodag_id.ip6addr));
    cur_dodag->node_role = RPL_NODE_TYPE_BR;
    cur_dodag->is_grounded = instnace_info->isGrounded;

    /* RPL_TODO: Handle route poisioning */
    if (poision_route){
    }

    return SUCCESS;
}


int rpl_start(rpl_protocol_context rpl_ctx){
    /* Here we will start the timers based on the node type */
}


