/**
 * @file
 * Tripple Configurations
 */

/*
 * Copyright (C) 2020 Authors of Tripple
 *
 * This file is subject to the terms and conditions. See the file LICENSE in
 * the top level directory for more details.
 */

/**
 * @ingroup     Include
 * @{
 *
 * @file
 * @brief       RPL Configurations
 *
 * @}
 */

#ifdef __cplusplus
extern "C" {
#endif

#define RPL_SUPPORTED_FOR_LWIP 0x01
#define RPL_SUPPORTED_FOR_UIP  0x02
#define RPL_SUPPORTED_FOR_RIOT 0x03

/* Platform Related Configurations */
#ifdef RPL_WITH_LWIP
#define RPL_PLATFORM     RPL_SUPPORTED_FOR_LWIP
#define TIMER_INCLUDE    "lwip_patimer.h"
#endif

#ifdef RPL_WITH_UIP
#define RPL_PLATFORM     RPL_SUPPORTED_FOR_UIP
#endif

#ifdef RPL_WITH_RIOT
#define RPL_PLATFORM     RPL_SUPPORTED_FOR_RIOT
#endif

/* RPL Protocol Constants as per RFC 6550*/

#define DEFAULT_DIO_INTERVAL_MIN           3
#define DEFAULT_DIO_INTERVAL_DOUBLINGS     20
#define DEFAULT_DIO_REDUNDANCY_CONSTANT    10

#ifndef _RPL_CONFIGURATIONS_H_
#define _RPL_CONFIGURATIONS_H_

#ifndef RPL_CONF_USE_STATIC_ALLOCATION
#define RPL_USE_STATIC_ALLOCATION      1
#else
#define RPL_USE_STATIC_ALLOCATION           RPL_CONF_USE_STATIC_ALLOCATION
#endif

#if RPL_USE_STATIC_ALLOCATION

#ifndef RPL_CONF_MAXIMUM_RPL_INSTNACE        
#define RPL_MAXIMUM_RPL_INSTNACE            2
#else
#define RPL_MAXIMUM_RPL_INSTNACE            RPL_CONF_MAXIMUM_RPL_INSTNACE
#endif

#endif

/* Trickle Related Configurations */
#ifndef RPL_CONF_DIO_INTERVAL_MIN
#define RPL_DIO_INTERVAL_MIN                DEFAULT_DIO_INTERVAL_MIN
#else
#define RPL_DIO_INTERVAL_MIN                RPL_CONF_DIO_INTERVAL_MIN
#endif

#ifndef RPL_CONF_DIO_INTERVAL_DOUBLINGS
#define RPL_DIO_INTERVAL_DOUBLINGS          DEFAULT_DIO_INTERVAL_DOUBLINGS
#else
#define RPL_DIO_INTERVAL_DOUBLINGS          RPL_CONF_DIO_INTERVAL_DOUBLINGS
#endif

#ifndef RPL_CONF_DIO_REDUNDANCY_CONSTANT
#define RPL_DIO_REDUNDANCY_CONSTANT         DEFAULT_DIO_REDUNDANCY_CONSTANT
#else
#define RPL_DIO_REDUNDANCY_CONSTANT         RPL_CONF_DIO_REDUNDANCY_CONSTANT
#endif

/* Configuration common accross all the RPL instnaces a node
    will be part of */
typedef struct _rpl_node_configurations{
    
}rpl_node_configurations_t;

/* In a given instnace a node can be part of only one DODAG
    so it can have both instnace and DODAG specific configuration */
typedef struct _rpl_instance_configuration{
    
}rpl_instance_configuration_t;


typedef struct _rpl_configurations{
	rpl_node_configurations_t stNodeConfig;
	rpl_instance_configuration_t instance_config;
}rpl_configurations_t;

#ifdef __cplusplus
}
#endif

#endif  /*_RPL_CONFIGURATIONS_H_*/
 