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

typedef enum _RPL_TIMER_TYPE
{
    RPL_TIMER_TYPE_PERIODIC,
    RPL_TIMER_TYPE_ONCE	
}RPL_TIMER_TYPE;

typedef void* rpl_timer_t;

/************************************************************
	Timer Related Interfaces. Each platform need to implement their own
	interface.
*************************************************************/

/* Callback for timeout */

typedef void (*fpRplTimerTimeoutHandler)(void *user_data);
/* Timer APIs to be used by the RPL Protocol*/
/* Create the Timer */
rpl_timer_t rpl_timer_create_timer_object(RPL_TIMER_TYPE, 
				fpRplTimerTimeoutHandler, void *);

/*Free the timer object*/
void rpl_timer_free_timer_object(rpl_timer_t);

/* Starts the timer */
uint8_t rpl_timer_start_timer(rpl_timer_t);

/* Stop the timer */
uint8_t rpl_timer_stop_timer(rpl_timer_t);

/* Get current status of the timer */
uint8_t rpl_timer_get_status(rpl_timer_t);

#ifdef __cplusplus
 }
#endif

#endif /*_RPL_PAPI_TIMERS_H_*/

