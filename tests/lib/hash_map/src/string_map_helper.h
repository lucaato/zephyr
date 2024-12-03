/* custom equality test public utility functions */
#include "zephyr/sys/util.h"

static inline bool string_map_contains_key(const struct sys_hashmap *map, const char *key) {
	return string_map_get(map, key, NULL);
}

static inline bool string_map_remove(struct sys_hashmap *map, const char *key, uint64_t *value, char **old_key) {
	uint64_t uint_old_key = 0;
	bool res = 0;

	res = sys_hashmap_remove(map, POINTER_TO_UINT(key), value, &uint_old_key);

	if (old_key && uint_old_key) {
		/* NOLINTNEXTLINE(performance-no-int-to-ptr) */
		*old_key = UINT_TO_POINTER(uint_old_key);
	}

	return res;
}

static inline int string_map_insert(struct sys_hashmap *map, const char *key, uint64_t value, uint64_t *old_value,
		      char **old_key)
{
	uint64_t uint_old_key = 0;
	int res = 0;

	res = sys_hashmap_insert(map, POINTER_TO_UINT(key), POINTER_TO_UINT(value), old_value,
				 &uint_old_key);

	if (old_key && uint_old_key) {
		/* NOLINTNEXTLINE(performance-no-int-to-ptr) */
		*old_key = UINT_TO_POINTER(uint_old_key);
	}

	return res;
}

static inline bool string_map_get(const struct sys_hashmap *map, const char *key, uint64_t *value)
{
	return sys_hashmap_get(map, POINTER_TO_UINT(key), value);
}

static inline void string_map_free_callback(uint64_t key, uint64_t value, void *cookie)
{
	/* NOLINTNEXTLINE(performance-no-int-to-ptr) */
	char *key_string = UINT_TO_POINTER(key);

	free(key_string);
}

