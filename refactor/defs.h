/*
 * (C) Copyright 2001 Diomidis Spinellis.
 *
 * Standard definitions read when starting up
 *
 * To create this file look at /usr/lib/gcc-lib/ * / * /specs
 * This file should have read-only permissions
 *
 * $Id: defs.h,v 1.14 2006/02/10 12:13:50 dds Exp $
 */

#define __DATE__ ""
#define __TIME__ ""
#define __FILE__ ""
#define __LINE__ 0
#define __PRETTY_FUNCTION__ ""

//#define __cplusplus
#define __STDC__ 1
#define __ELF__
#define unix
#define i386
#define __i386
#define __i386__
#define __tune_i386__
#define linux
#define __linux
#define __linux__
#define __unix
#define __GNUC__ 2
#define __GNUC_MINOR__ 96
#define __WCHAR_TYPE__ short unsigned int

#ifdef __cplusplus
#define __GNUG__ 3
#define __EXCEPTIONS
#endif

#define __extension__
#define __attribute__(x)
#define __const const
#define __restrict
#define __builtin_va_list void *
#define __builtin_stdarg_start
#define __builtin_va_end
#define __builtin_va_arg(_ap, _type) (*(_type *)(_ap))
#define __inline__ inline
#define __inline inline
#define __volatile__
