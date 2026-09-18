#pragma once
#include <stddef.h>
#include <errno.h>
#include <fcntl.h>

/*  this will use POSIX implementations.
 *  defined in man pages section 2.
 *  must include read to file, write to file.
 *  subject to DESIGN.md.
 *
 * */

// impl function, dest should not alias with pathname,
// returns 0 on success, -1 on error and errno occurences
// relies on POSIX errno
static int impl_read_file(
  const char* pathname,
  char*       dest,
  size_t      sz,
  const char* FILE,
  int         LINE
);
// wrapper of impl_read_file(const char* restrict pathname, const char* restrict dest, size_t sz, const char* FILE, int LINE)
// used for runtime debugging to print the file and line in the cleanup: of the impl
#define read_file(pathname, dest, sz) \
  impl_read_file((pathname), (dest), (sz), __FILE__, __LINE__)
