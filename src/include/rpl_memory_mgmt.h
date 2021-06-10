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
 * @brief       Memory Related Interfaces
 *
 * @}
 */

#ifndef _RPL_MEMORY_MGMT_H_
#define _RPL_MEMORY_MGMT_H_

#include "rpl_papi.h"
#include "rpl_topology.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MEMORY_TYPE_STATIC_FLAG 0x80
#define MEMORY_TYPE_DYNAMIC_FLAG 0x40

typedef void rpl_memory_region;

typedef struct _rpl_memory_manager{
#if RPL_USE_STATIC_ALLOCATION
	int count;
	uint8_t *allocation_array;
#endif
	uint32_t entry_size;

	/* For malloc based allocation this will be NULL for platform based
	    memory managers this can be point to the memory manager*/
	rpl_memory_region *memory;
	uint8_t flags;
}rpl_memory_manager;

/* Each Platform MUST implement their own Mmeory Menager if they 
    don't want to use the static based allocation */
uint32_t rpl_initialize_memory_manager(rpl_memory_manager *,
			uint32_t item_size);

#if RPL_USE_STATIC_ALLOCATION 
#define RPL_CREATE_MEMORY_MANAGER(type, count, name)                     \
	static type _##name##_mem[count];                                    \
	static char _##name##_track_alloc[count] = {0};                      \
	static rpl_memory_manager name##_manager = {count,                   \
	                    _##name##_track_alloc, sizeof(type),             \
	                    _##name##_mem, MEMORY_TYPE_STATIC_FLAG};         \
	static rpl_memory_manager *name = &(name##_manager)
#else
#define RPL_CREATE_MEMORY_MANAGER(type, count, name)                     \
	static rpl_memory_manager *name = NULL
#endif

void *rpl_memmgr_memalloc(rpl_memory_manager *, uint32_t);
void rpl_memmgr_memfree(rpl_memory_manager *, void *);

#define RPL_MEMORY_INIT

#ifdef __cplusplus
}
#endif

#endif /*_RPL_MEMORY_MGMT_H_*/

