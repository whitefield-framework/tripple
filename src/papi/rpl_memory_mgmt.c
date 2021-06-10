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

#include "rpl_memory_mgmt.h"

static void *rpl_static_memmgr_memalloc(rpl_memory_manager *mem_mgr)
{
#if RPL_USE_STATIC_ALLOCATION
	int i = 0;

	for (; i < mem_mgr->count ; i++){
		if (mem_mgr->allocation_array[i] == 0){
			/* Increase the count to indicate memory is in use */
			mem_mgr->allocation_array[i] = 1;
			return (void *)((char *)mem_mgr->memory + (i * mem_mgr->entry_size));
		}
	}
#endif

	return NULL;

}

static void rpl_static_memmgr_memfree(rpl_memory_manager *mem_mgr,
												void *memory)
{
#if RPL_USE_STATIC_ALLOCATION
	int index = 0;

	/* Find the index of the memory that will be freed.*/
	index = ((char *)memory - (char *)mem_mgr->memory)/mem_mgr->entry_size;
	if (mem_mgr->allocation_array[index] > 0){
		mem_mgr->allocation_array[index] = 0;
	}
#endif

	return;
}

void *rpl_memmgr_memalloc(rpl_memory_manager *mem_mgr,uint32_t size)
{
	if (NULL == mem_mgr){
		return NULL;
	}

	/* For Static Memory just return the next free index */
	if (mem_mgr->flags & MEMORY_TYPE_STATIC_FLAG){
		return rpl_static_memmgr_memalloc(mem_mgr);
	}
	else{
		return NULL;
	}
}
void rpl_memmgr_memfree(rpl_memory_manager *mem_mgr, void *mem)
{
	if (NULL == mem_mgr || mem == NULL){
		return;
	}
	
	/* For Static Memory just return the next free index */
	if (mem_mgr->flags & MEMORY_TYPE_STATIC_FLAG){
		return rpl_static_memmgr_memfree(mem_mgr, mem);
	}
	else{
		return;
	}
}

