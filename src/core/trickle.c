
#include "rpl.h"
#include <trickle.h>

static void rpl_handle_trickle_timeout(void *data)
{
    trickle_timer_t *trickle_timer = (trickle_timer_t *)data;

    /* If the Count is < redundancy constant or supression is disabled 
           need to perform the task */
    if (trickle_timer->bNeedTsend){
        if (trickle_timer->redundancy_constant == 0 || 
            trickle_timer->counter < trickle_timer->redundancy_constant){
            trickle_timer->handler(trickle_timer->data);
        }
    }
    else{
        /* Move to Next Interval if we have not yet reached Imax */
        if (trickle_timer->cur_interval < (trickle_timer->interval_min +
            trickle_timer->interval_doubling)){
            trickle_timer->cur_interval++;
        }

        rpl_start_new_trickle_interval(trickle_timer);
    }

    return;
}



int rpl_start_new_trickle_interval(trickle_timer_t *trickle_timer){
    uint32_t interval;
    uint32_t duration;

    /* This duration is in milliseconds */
    interval = 1U << trickle_timer->cur_interval;

    /*When an interval begins, Trickle resets c to 0 and sets t to a random point in the
          interval, taken from the range [I/2, I)*/
    duration = interval/2;
    trickle_timer->remain_delay_interval = interval - duration;
    trickle_timer->counter = 0;

    /* Schedule the Time */

    return SUCCESS;
    
}


void rpl_reset_trickle_timer(trickle_timer_t *trickle_timer){
    /* If Current Interval 'I' is equal to Imin when Trickle hears an"inconsistent" transmission,
           Trickle does nothing.*/
    if (trickle_timer->cur_interval > trickle_timer->interval_min){
        trickle_timer->cur_interval = trickle_timer->interval_min;
        trickle_timer->counter = 0;
        rpl_start_new_trickle_interval(trickle_timer);
    }

    return;
}


