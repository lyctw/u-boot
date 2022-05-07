/* 
 * Copyright (c) 2022, Canaan Bright Sight Co., Ltd
 * Copyright (C) 2004 CodeSourcery, LLC
 *
 * Permission to use, copy, modify, and distribute this file
 * for any purpose is hereby granted without fee, provided that
 * the above copyright notice and this notice appears in all
 * copies.
 *
 * This file is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */
#include <sys/types.h>

#define USE_LIBC_INITFINI		1

#if USE_LIBC_INITFINI

/*
 * The _init() and _fini() will be called respectively when use __libc_init_array()
 * and __libc_fnit_array() in libc.a to perform constructor and destructor handling.
 * The dummy versions of these functions should be provided.
 */
void _init(void)
{
}

void _fini(void)
{
}

#else

/* These magic symbols are provided by the linker.  */
extern void (*__preinit_array_start []) (void) __attribute__((weak));
extern void (*__preinit_array_end []) (void) __attribute__((weak));
extern void (*__init_array_start []) (void) __attribute__((weak));
extern void (*__init_array_end []) (void) __attribute__((weak));

/*
 * The __libc_init_array()/__libc_fnit_array() function is used to do global
 * constructor/destructor and can NOT be compilied to generate the code coverage
 * data. We have the function attribute to be 'no_profile_instrument_function'
 * to prevent been instrumented for coverage analysis when GCOV=1 is applied.
 */
/* Iterate over all the init routines.  */
void __libc_init_array (void) __attribute__((no_profile_instrument_function));
void __libc_init_array (void)
{
	size_t count;
	size_t i;

	count = __preinit_array_end - __preinit_array_start;
	for (i = 0; i < count; i++)
		__preinit_array_start[i] ();

	count = __init_array_end - __init_array_start;
	for (i = 0; i < count; i++)
		__init_array_start[i] ();
}

extern void (*__fini_array_start []) (void) __attribute__((weak));
extern void (*__fini_array_end []) (void) __attribute__((weak));

/* Run all the cleanup routines.  */
void __libc_fini_array (void) __attribute__((no_profile_instrument_function));
void __libc_fini_array (void)
{
	size_t count;
	size_t i;

	count = __fini_array_end - __fini_array_start;
	for (i = count; i > 0; i--)
		__fini_array_start[i-1] ();
}

#endif
