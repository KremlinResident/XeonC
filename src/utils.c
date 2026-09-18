#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// read_file reads the entire contents of a file into a newly allocated buffer.
// includes null terminator. returns NULL on error. out_size is set to the size
// of the buffer (not including null terminator).
// this utility function is macro'd, use read_file for proper debug handling of
// FILE_NAME and LINE
// the read is atomic, it's all or nothing, fread(str, *out_size, 1, fd);
static char *xeoncimpl_read_file(const char *path, size_t *out_size,
                                 const char *FILE_NAME, int LINE) {
  enum XeonC_errno_vals discrete_errno = XEONC_CLEAR;
  char *str = NULL;
  FILE *fd = fopen(path, "rb");
  if (!fd) {
    perror("fopen");
    discrete_errno = XEONC_FILE_OPEN_FAILURE;
    goto cleanup;
  }
  // seek returns 0 on success, !=0 on error
  if (fseeko(fd, 0, SEEK_END)) {
    discrete_errno = XEONC_FSEEK_FAILURE;
    goto cleanup;
  }
  off_t tmp_len = ftello(fd);
  if ((size_t)tmp_len >= SIZE_MAX - 1) {
    discrete_errno = XEONC_SIZETYPE_REACHED_SIZEMAX;
    goto cleanup;
  }
  *out_size = (size_t)tmp_len;
  rewind(fd);

  str = malloc(*out_size + 1); // '\0'
  if (!str) {
    discrete_errno = XEONC_ALLOCATION_FAILURE;
    goto cleanup;
  }
  if (!fread(str, *out_size, 1, fd)) {
    discrete_errno = XEONC_READ_FILE_FAILURE;
    free(str);
    str = NULL;
    goto cleanup;
  }
  // NOTE: SCOPED SUPPRESSION OF FAULTY STATIC ANALYSIS
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunsafe-buffer-usage"
  str[*out_size] = '\0';
#pragma clang diagnostic pop
  goto cleanup;
cleanup:
  if (fd)
    fclose(fd);
  if (discrete_errno != XEONC_CLEAR)
    fprintf(
        stderr,
        "failed to call function, file:%s, ln:%i\n, please check XeonC_errno",
        FILE_NAME, LINE);
  XeonC_errno = discrete_errno;
  return str;
}

// write_file writes the contents of a buffer to a file. returns NULL on error.
// returns 0 on success. returns -1 on failure
// this utility function is macro'd, use write_file for proper debug handling of
// FILE_NAME and LINE
// the write is non-atomic, it's a looping write and may improperly write
// uses fwrite(str, sizeof(*str), size, fd);
static int xeoncimpl_write_file(const char *path, const char *data, size_t size,
                                const char *FILE_NAME, int LINE) {
  enum XeonC_errno_vals discrete_errno = XEONC_CLEAR;
  int return_n = 0;

cleanup:
  return return_n;
}
