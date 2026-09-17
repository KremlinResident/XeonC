#include "utils.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

static char *xeoncimpl_read_file(const char *path, size_t *out_size,
                                 const char *FILE_NAME, int LINE) {
  char *str = NULL;
  FILE *fd = fopen(path, "rb");
  if (!fd)
    goto cleanup;
  // seek returns 0 on success, !=0 on error
  if (fseek(fd, 0, SEEK_END)) {
    XeonC_errno = XEONC_FSEEK_FAILURE;
    goto cleanup;
  }
  off_t tmp_len = ftello(fd);
  if ((size_t)tmp_len >= SIZE_MAX - 1) {
    XeonC_errno = XEONC_SIZETYPE_REACHED_SIZEMAX;
    goto cleanup;
  }
  *out_size = (size_t)tmp_len;
  rewind(fd);

  str = malloc(*out_size + 1); // '\0'
  if (!str) {
    XeonC_errno = XEONC_ALLOCATION_FAILURE;
    goto cleanup;
  }
  if (!fread(str, *out_size, 1, fd)) {
    XeonC_errno = XEONC_READ_FILE_FAILURE;
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
  fprintf(stderr,
          "failed to call function, file:%s, ln:%i\n, please check XeonC_errno",
          FILE_NAME, LINE);
  return str;
}

static int xeoncimpl_write_file(const char *path, const char *data, size_t size,
                                const char *FILE, int LINE) {}
