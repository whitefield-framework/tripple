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
 * @brief       Trickle algorithm
 *
 * @}
 */

#ifndef _TRICKLE_H_
#define _TRICKLE_H_

#include <rpl_types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*pfTrickleTimerTimeoutHandler)(void *);

typedef struct _trickle_timer{
    /* In the RPL the Trickle Interval MIN is specified in the term of 
           base 2 log(minumum_interval_size in ms) */
    uint8_t     interval_min;
    uint8_t     interval_doubling;
    uint8_t     redundancy_constant;
    
    uint8_t     cur_interval;
    uint8_t     counter;
    bool_t      bNeedTsend;
    uint32_t    remain_delay_interval;
    pfTrickleTimerTimeoutHandler handler;
    void        *data;
    
}trickle_timer_t;

void rpl_reset_trickle_timer(trickle_timer_t *trickle_timer);
int  rpl_start_new_trickle_interval(trickle_timer_t *trickle_timer);


#ifdef __cplusplus
}
#endif

#endif /* _TRICKLE_H_ */

