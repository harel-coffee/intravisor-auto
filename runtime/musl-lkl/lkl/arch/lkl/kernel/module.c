/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  Copyright (C) 2017 Zihao Yu
 */
extern int lkl_printf(const char *format, ...);

int apply_relocate_add(void *sechdrs, const char *strtab,
		       unsigned int symindex, unsigned int relsec,
		       struct module *me)
{
	lkl_printf("NOT IMPLEMENTED %s\n", __func__);
	return 0;
}
