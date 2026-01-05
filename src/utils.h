#ifndef MYUTILS_H
#define MYUTILS_H

#include "pico/bootrom.h"
#include "pico/stdio.h"
#include <errno.h>
#include <pico/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CLAMP(value, lower, upper)                                             \
  ((value) < (lower) ? (lower) : ((value) > (upper) ? (upper) : (value)))
#define CYCLE(value, len)                                                      \
  ((value) < (0) ? (len - 1) : ((value) > (len - 1) ? (0) : (value)))
#define DA_APPEND(arr, i)                                                      \
  do {                                                                         \
    if ((arr)->count >= (arr)->capacity) {                                     \
      if ((arr)->capacity == 0)                                                \
        (arr)->capacity = 256;                                                 \
      else                                                                     \
        (arr)->capacity *= 2;                                                  \
      (arr)->items =                                                           \
          realloc((arr)->items, (arr)->capacity * sizeof((arr)->items[0]));    \
    }                                                                          \
    (arr)->items[(arr)->count++] = (i);                                        \
  } while (0)
#define DA_REMOVE(arr, id)                                                     \
  do {                                                                         \
    for (int i = 0; i < (arr)->count; i++) {                                   \
      if ((arr)->items[i].id == id) {                                          \
        memmove((arr)->items + i, (arr)->items + i + 1,                        \
                ((arr)->count - i - 1) * sizeof((arr)->items[0]));             \
        (arr)->count--;                                                        \
        break;                                                                 \
      }                                                                        \
    }                                                                          \
  } while (0)
#define DA_CLEAR(arr)                                                          \
  do {                                                                         \
    free((arr)->items);                                                        \
    (arr)->items = NULL;                                                       \
    (arr)->count = 0;                                                          \
    (arr)->capacity = 0;                                                       \
  } while (0)
#define ARRAY_HAS(elem, arr, size)                                             \
  ({                                                                           \
    int _found = 0;                                                            \
    for (int _i = 0; _i < (size); _i++) {                                      \
      if ((arr)[_i] == elem) {                                                 \
        _found = 1;                                                            \
        break;                                                                 \
      }                                                                        \
    }                                                                          \
    _found;                                                                    \
  })
#define PRINT_ARRAY(arr, size)                                                 \
  ({                                                                           \
    for (int _i = 0; _i < (size); _i++) { printf("%d ", (arr)[_i]); }          \
    printf("\n");                                                              \
  })

static inline uint32_t time_ms_boot(void) { return us_to_ms(time_us_64()); }

static inline void input_callback(void *param) {
  int *char_ptr = (int *)param;
  int c = getchar_timeout_us(0);
  if (c != PICO_ERROR_TIMEOUT) *char_ptr = c;
}

static inline void handle_input(int *last_char) {
  if (*last_char == 'r') rom_reset_usb_boot_extra(-1, 0, false);
}

static inline int string_startswith(const char *str, const char *prefix) {
  while (*prefix && *prefix == *str) {
    prefix++;
    str++;
  }
  if (*prefix) return 0;
  return 1;
}

static inline int string_endswith(const char *str, const char *suffix) {
  size_t str_len = strlen(str);
  size_t suffix_len = strlen(suffix);

  if (suffix_len > str_len) return 0;
  return strcmp(str + str_len - suffix_len, suffix) == 0;
}

static inline unsigned long parse_uint(const char *str) {
  char *endptr;
  unsigned long val = strtoul(str, &endptr, 10);
  if (endptr == str || *endptr != '\0' || errno == ERANGE) return 0;
  return val;
}

unsigned int uint_hash(const uint32_t *key) { return (unsigned int)*key; }

int uint_hash_cmp(const uint32_t *a, const uint32_t *b) {
  return *a == *b ? 0 : 1;
}

#endif
