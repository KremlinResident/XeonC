#include "filemanager.h"
#include <errno.h>
#include <fcntl.h>

// impl function, dest should not alias with pathname,
// returns 0 on success, -1 on error and errno occurences
// relies on POSIX errno
static int impl_read_file(
  const char* pathname,
  char*       dest,
  size_t      sz,
  const char *FILE,
  int         LINE
) {
  // declarations
  int fd = open(pathname, O_RDONLY | O_CREAT);
  int return_val = 0

}
