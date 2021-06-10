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
 * @brief       RPL objective function interfaces.
 *
 * @}
 */

#ifndef _RPL_OBJECTIVE_FUNCTION_
#define _RPL_OBJECTIVE_FUNCTION_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _rpl_objective_function{
    uint16_t (*pf_of_compute_path_cost)(void *rpl_parent);
    uint16_t (*pf_of_compute_rank) (void *rpl_parent);
    void * (*pf_of_select_preferred_parent)(void *parent_list);
    void * (*pf_of_select_n_preferred_parent)(void *parent_list);
}rpl_objective_function_cb;

#ifdef __cplusplus
}
#endif

#endif /*_RPL_OBJECTIVE_FUNCTION_*/

