#pragma once

typedef unsigned char u8;
typedef signed char s8;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned int u32;
typedef signed int s32;

typedef unsigned long u64;
typedef signed long s64;

typedef float f32;
typedef double f64;

#ifdef DEBUG
	#include <stdio.h>

	#define LOG(fmt, ...) do { \
		printf((fmt), ##__VA_ARGS__); \
	} while (false)
#else
	#define LOG(fmt, ...) // Nothing
#endif
