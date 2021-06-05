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
 * @brief       Timers
 *
 * @}
 */

#ifndef _RPL_PAPI_TIMERS_H_
#define _RPL_PAPI_TIMERS_H_

#ifdef __cplusplus
 extern "C" {
#endif

typedef void* rpl_timer_t;
typedef enum _RPL_TIMER_TYPE
{
    RPL_TIMER_TYPE_PERIODIC,
    RPL_TIMER_TYPE_ONCE	
}RPL_TIMER_TYPE;

/************************************************************
	Timer Related Interfaces. Each platform need to implement their own
	interface.
*************************************************************/

/* Timer APIs to be used by the RPL Protocol*/
/* Create the Timer */
rpl_timer_t rpl_timer_create_timer_object(void,);

/*Free the timer object*/
void rpl_timer_free_timer_object(rpl_timer_t);

/*Start 


#ifdef __cplusplus
 }
#endif

#endif /*_RPL_PAPI_TIMERS_H_*/

