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
 * @brief       Tripple Network topology components
 *
 * @}
 */

#ifndef _RPL_TOPOLOGY_H_
#define _RPL_TOPOLOGY_H_

#include "rpl_types.h"
#include "rpl_objective_function.h"

#define RPL_MAX_NUM_THROUGHPUT 5
#define RPL_MAX_LQL_VALUES 8

typedef enum rpl_node_type{
    RPL_NODE_TYPE_LEAF,
    RPL_NODE_TYPE_LR,
    RPL_NODE_TYPE_BR,
    RPL_NODE_TYPE_NONE
}rpl_node_type;

/* Node Metric or/and constraint Objects*/
typedef enum rpl_mc_types{
    RPL_MC_TYPE_NSA = 1,                /* Won't be supported */
    RPL_MC_TYPE_ENERGY ,                /* Will support this */
    RPL_MC_TYPE_HOP_COUNT,              /* Will Support this */
    RPL_MC_TYPE_THROUGHPUT,             /* Will support this */
    RPL_MC_TYPE_LATENCY,                /* WIll Support This */
    RPL_MC_TYPE_LINK_RELIABILITY_LQL,   /* Will Support This */
    RPL_MC_TYPE_NONE
}rpl_mc_types;

/* RPL Prefix Information */
typedef struct _rpl_dodag_prefix{
    uint32_t           valid_lifetime;
    uint32_t           preferred_lifetime;
    rpl_ipv6_prefix    dodag_prefix;
    uint8_t            prefix_length;
    
#define RPL_DODAG_PREFIX_USE_FOR_ONLINK_DETERMINATION  0x80
#define RPL_DODAG_PREFIX_USE_FOR_SLAC                  0x40
#define RPL_DODAG_PREFIX_CONTAINS_COMPLETE_ADDRESS     0x20
    uint8_t            prefix_flags;
    uint8_t            reserved[2];
}rpl_dodag_prefix_t;


/* RPL Metrics 
    Routing Constraints are used to Prune the links and node that
    don't satisfy the constraint.

    A routing Metric is a quantitative value that is used to evaluate the 
    path cost.

    The best path is the path that satisfies all supplied constraints (if any)
    and that has the lowest cost with respect to some specified metrics.

    We will support both constraint and metric.
    link and node characteristics can be used as constraints and/or metrics
*/

typedef struct _rpl_metric_constraint_common{
    uint8_t        routing_mc_type;              /* It Can be Metric or constrainnts */

#define RPL_DAG_MC_RESERVED_FLAGS                0xF800 /* Reserved */
#define RPL_DAG_MC_METRIC_RECORDING_INFO         0x0400 /* P */
#define RPL_DAG_MC_USE_AS_CONSTRAINT             0x0200 /* C */
#define RPL_DAG_MC_CONSTRAINT_IS_OPTIONAL        0x0100 /* O */
#define RPL_DAG_MC_RECORD_AGGREGATE              0x0080 /* R */
#define RPL_DAG_MC_TYPE_AGGREGATED_M             0x0070 /* A */
#define RPL_DAG_MC_PRECEDENCE                    0x000F /* A */

    uint16_t       flags;                        /* P, C , O, R, A, Perc */
}rpl_metric_constraint_common_t;

/* Node Metrics */
typedef struct _rpl_node_energy_object{
    rpl_metric_constraint_common_t stcmnInfo;
#define NE_OBJECT_INCLUSION_VS_EXCLUSION    0x08
#define NE_OBJECT_NODE_TYPE_MP_BP_ES        0x06
#define NE_OBJECT_EP_RE                     0x01 /*Estimated Percentage Of 
                                                                                Remaining Energy*/
    uint8_t flags;
    uint8_t estimated_energy;
}rpl_node_energy_object_t;


typedef struct _rpl_hop_count_object{
    rpl_metric_constraint_common_t stcmnInfo;
    uint8_t hop_count;
}rpl_hop_count_object_t;


/* Link Metrics */
typedef struct _rpl_throughput_object{
    rpl_metric_constraint_common_t stcmnInfo;
    uint32_t throughput;
}rpl_throughput_object;

/* Link Metrics */
typedef struct _rpl_latency_object{
    rpl_metric_constraint_common_t stcmnInfo;
    uint32_t latency;               /* Can be a constraint or Metrics */
}rpl_latency_object;

typedef struct _rpl_lql_object{
    rpl_metric_constraint_common_t stcmnInfo;
    /* Valid values for lql are from 0 to 7. 
           0 - LQL is unknown
           1- Highest LQL.
           for each encountered LQL value, only the number of matching links is 
           reported. */
    uint8_t values[RPL_MAX_LQL_VALUES];
}rpl_lql_object_t;

/*The ETX object may be used as a constraint or a path metric.*/
typedef struct _rpl_etx_object{
    rpl_metric_constraint_common_t stcmnInfo;
    uint16_t etx;                  /* Can be a constraint or Metrics */
}rpl_etx_object;


typedef struct _rpl_link_metric{
  uint16_t     etx;             /* ETX using ETX_DIVISOR as fixed point divisor */
  int16_t      rssi;            /* RSSI (received signal strength) */
  uint16_t     per_hop_latency; /* Link latency */
}rpl_link_metric_t;
/* 
    Metric container can have multiple metrics ans constraints 
    We need to strore them in the order of their preference
*/
typedef struct _rpl_dag_metric_container{
    void *metrics_constraints[RPL_NODE_TYPE_NONE];
}rpl_dag_metric_container_t;


/* RPL Parent 
    An upstream node can be a parent for multiple DODAG belongs to multiple
    instnace.
    Note: Given an RPL Instance with multiple DODAG, A node can join 
             one DODAG in that instnace.
    Usecase: In home mesh network we can have two DODAG one for the 
                  Baterry operated appliances one for powerline operated 
                  appliances both optimizing different matrics.

    Common Information of a parent across multiple Instnace: 
    1- Parent Link Local Address
    2- Parent Link Layer address
    3- Parent Metric information (If all DODAG's of all instances uses 
                                             same Metric)
    Information Specific to DODAG
    1- Parent Rank
    2- Metric Information if each DODAG have its own metric (Etx, Energy, Hop 
                                                                                     Count)
    3- DODAG Specific Globar IP address
    4- DTSN (DAO Trigger Sequence Number)
    
 */

typedef struct _rpl_dag_neighbor{
    /* Neighbor Link Local Address */
    rpl_ipv6_address_t      link_local_address;
    rpl_link_metric_t       link_metric_info;
}rpl_dag_neighbor_t;

typedef struct _rpl_dag_parent{
    rpl_dag_neighbor_t             *nbr_info;
    rpl_rank_t                     rank;
    rpl_dag_metric_container_t     metric_info;
    uint8_t                        dtsn;
    uint8_t                        flags
}rpl_dag_parent_t;

typedef struct _rpl_dodag_configs{
    uint16_t     max_rank_incr;
    uint16_t     minhop_rank_incr;
    uint16_t     lifetime_uint;
    uint8_t      default_lifetime;
    uint8_t      dio_inter_doubling;
    uint8_t      dio_inter_min;
    uint8_t      dio_redundancy;
    uint8_t      flag_and_pcs;
    uint8_t      unused;
}rpl_dodag_configs_t;

/*
    RPL node can belong to one DODAG in a RPL Instance. So Its highly 
    possible a device can be part of multiple RPL instances.
*/
typedef struct _rpl_dodag{
    rpl_dodag_configs_t   dodag_config;
    rpl_ipv6_address_t    dodag_id;
    rpl_dodag_prefix_t    dodag_prefix;
    rpl_ipv6_address_t    target_address;
    rpl_node_type         node_role;
    rpl_rank_t            dodag_rank;
    uint8_t               dodag_version;
    rpl_dag_parent_t      *preferred_parent;
    rpl_dag_parent_t      *parent_list;
}rpl_dodag_t;


typedef struct _rpl_instnace{
    struct _rpl_instnace *next;
    /* DODAGs Associated with it */
    rpl_dodag_t *dodag;
    rpl_objective_function_cb *objfuns;
    uint8_t rpl_instance_id;
}rpl_instnace_t;


/* A node can be part of multiple Instnace . 
    An instnace can have multiple DODAG
    But a Node can be part of only one DODAG in an RPL instnace */
typedef struct _rpl_node{
    rpl_instnace_t *rpl_instance_list;
    power_type
}rpl_node_t;


#endif /*_RPL_TOPOLOGY_H_*/

