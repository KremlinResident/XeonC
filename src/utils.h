#pragma once
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

/* typedefs */

typedef unsigned char byte;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int32_t i32;
typedef int64_t i64;
typedef float f32;
typedef double f64;

/* custom XeonC errno values */

enum XeonC_errno_vals {
  XEONC_CLEAR = 0,
  XEONC_FILE_OPEN_FAILURE,
  XEONC_FSEEK_FAILURE,
  XEONC_READ_FILE_FAILURE,
  XEONC_WRITE_FILE_FAILURE,
  XEONC_ALLOCATION_FAILURE,
  XEONC_SIZETYPE_REACHED_SIZEMAX
};

extern enum XeonC_errno_vals XeonC_errno;

// read_file reads the entire contents of a file into a newly allocated buffer.
// includes null terminator. returns NULL on error. out_size is set to the size
// of the buffer (not including null terminator).
// this utility function is macro'd, use read_file for proper debug handling of
// FILE_NAME and LINE
static char *xeoncimpl_read_file(const char *path, size_t *out_size,
                                 const char *FILE_NAME, int LINE);
#define read_file(path, out_size)                                              \
  xeoncimpl_read_file((path), (out_size), __FILE__, __LINE__)
// write_file writes the contents of a buffer to a file. returns NULL on error.
// returns 0 on success. returns -1 on failure
// this utility function is macro'd, use write_file for proper debug handling of
// FILE_NAME and LINE
static int xeoncimpl_write_file(const char *path, const char *data, size_t size,
                                const char *FILE_NAME, int LINE);
#define write_file(path, data, size)                                           \
  xeoncimpl_write_file((path), (data), (size), __FILE__, __LINE__)
