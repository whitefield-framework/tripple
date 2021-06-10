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
 * @brief       RPL Parent list management
 *
 * @}
 */

#include "rpl_topology.h"
#include "rpl_memory_mgmt.h"

RPL_CREATE_MEMORY_MANAGER(rpl_dag_parent_t,
				RPL_MAXIMUM_RPL_PARENT, parent_memory_manager);


rpl_dag_parent_t * rpl_add_new_parent()
{
	rpl_dag_parent_t *parent;
	parent  = rpl_memmgr_memalloc(parent_memory_manager,
							sizeof(rpl_dag_parent_t));
	if (NULL == parent){
		return NULL;
	}

	return parent;
}




