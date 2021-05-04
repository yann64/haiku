/*
 * Copyright 2019 Haiku, Inc. All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _FEATURES_H
#define _FEATURES_H


#if defined(_BSD_SOURCE) \
	|| (!defined(__STRICT_ANSI__) && !defined(_POSIX_C_SOURCE))
	#undef _DEFAULT_SOURCE
	#define _DEFAULT_SOURCE
#endif

#if defined(_GNU_SOURCE)
       #undef _ISOC11_SOURCE
       #define _ISOC11_SOURCE
       #undef _DEFAULT_SOURCE
       #define _DEFAULT_SOURCE
#endif

#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
	#undef _ISOC11_SOURCE
	#define _ISOC11_SOURCE
#endif

#if defined(__cplusplus) && __cplusplus >= 201703L
       #undef _ISOC11_SOURCE
       #define _ISOC11_SOURCE
#endif

#endif // _FEATURES_H
