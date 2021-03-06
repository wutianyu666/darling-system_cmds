/*
 * Copyright (c) 2016 Apple Inc.  All rights reserved.
 */

#include "vm.h"

#ifndef _VANILLA_H
#define _VANILLA_H

extern walk_region_cbfn_t vanilla_region_optimization;

extern int coredump(task_t, int);
extern int coredump_write(task_t, int, struct regionhead *, const uuid_t, mach_vm_offset_t, mach_vm_offset_t);
extern struct regionhead *coredump_prepare(task_t, uuid_t);

#endif /* _VANILLA_H */
