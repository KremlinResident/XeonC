#pragma once
#include <stddef.h>

struct Buffer {
  char *data;
  size_t size;
  size_t capacity;
};
