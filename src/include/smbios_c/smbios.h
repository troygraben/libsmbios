// vim:expandtab:autoindent:tabstop=4:shiftwidth=4:filetype=c:
/*
 * Copyright (C) 2005 Dell Inc.
 *  by Michael Brown <Michael_E_Brown@dell.com>
 * Licensed under the Open Software License version 2.1 
 * 
 * Alternatively, you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published 
 * by the Free Software Foundation; either version 2 of the License, 
 * or (at your option) any later version.

 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 */


#ifndef SMBIOS_H
#define SMBIOS_H

// include smbios_c/compat.h first
#include "smbios_c/compat.h"
#include "smbios_c/types.h"

EXTERN_C_BEGIN;

#define SMBIOS_DEFAULTS       0x0000
#define SMBIOS_GET_SINGLETON  0x0001
#define SMBIOS_GET_NEW        0x0002
#define SMBIOS_UNIT_TEST_MODE 0x0004

struct smbios_table;
struct smbios_struct;

// construct
struct smbios_table *smbios_factory(int flags, ...);

// destruct
void smbios_free(struct smbios_table *);

// format error string
size_t memory_fmt_err(struct memory *, char *buf, size_t len);

// for looping/searching
struct smbios_struct *smbios_get_next_struct(struct smbios_struct *cur);
struct smbios_struct *smbios_get_next_struct_bytype(struct smbios_struct *cur, u8 type);
struct smbios_struct *smbios_get_next_struct_byhandle(struct smbios_struct *cur, u16 handle);

// visitor pattern
typedef void (smbios_walk_fn)(struct smbios_struct *);
void smbios_walk(smbios_walk_fn);

u8 smbios_struct_get_type(struct smbios_struct *);
u8 smbios_struct_get_length(struct smbios_struct *);
u16 smbios_struct_get_handle(struct smbios_struct *);
int smbios_struct_get_data(struct smbios_struct *s, void *dest, u8 offset, size_t len);
const char *smbios_get_string(struct smbios_struct *s, u8 offset);

EXTERN_C_END;

#endif  /* SMBIOS_H */