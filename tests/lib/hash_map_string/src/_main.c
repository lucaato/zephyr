/*
 * Copyright (c) 2022 Meta
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stdlib.h>

#include <zephyr/ztest.h>
#include <zephyr/sys/hash_map.h>

#include "_main.h"
#include "zephyr/sys/printk.h"
#include "zephyr/sys/util.h"

static uint32_t hash_string(const void *uint64_ptr_key, size_t len);
static bool eq_string(uint64_t key_left, uint64_t key_right);

/* only valid pointers to char array must be stored in this map, anything else will break */
SYS_HASHMAP_DEFAULT_DEFINE_ADVANCED(map, hash_string, eq_string, SYS_HASHMAP_DEFAULT_ALLOCATOR,
				    SYS_HASHMAP_CONFIG(SIZE_MAX, CUSTOM_LOAD_FACTOR));

static uint32_t hash_string(const void *uint64_ptr_key, size_t len)
{
	__ASSERT(len == sizeof(uint64_t),
		 "Received an invalid length for the hasmap key, expected only uint64_t");

	uint64_t key_pointer = {0};

	memcpy(&key_pointer, uint64_ptr_key, sizeof(uint64_t));

	const char *key_string = UINT_TO_POINTER(key_pointer);
	size_t key_string_len = strlen(key_string);

	return sys_hash32(key_string, key_string_len);
}

static bool eq_string(uint64_t key_left, uint64_t key_right)
{
	const char *key_left_string = UINT_TO_POINTER(key_left);
	const char *key_right_string = UINT_TO_POINTER(key_right);

	return strcmp(key_left_string, key_right_string) == 0;
}
