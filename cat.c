// cat

#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arg_parser.h"

#define BUFFER_SIZE 4096

struct ARGPARSE_STRUCT {
  int h
} ARGPARSE_STRUCT;

ARGPARSE_SETUP(
  ARGPARSE_CHECK(h)
)

int main(int argc, const char** argv) {
  int offset = ARGPARSE_FUNCTION(argc, argv);

  if (opts.h == 1) {
    printf(
      "usage: %s [file [...]]\n"
      "Concatenate 'file'(s) to standard output.\n"
      "\nCopyright (c) 2021 Ocawesome101 under the GPLv3.\n", argv[0]
    );
    exit(0);
  }

  if (offset == argc) {
    argv[offset] = "-";
  }

  for (int i = offset; i < argc; i++) {
    if (strcmp(argv[i], "-") == 0) {
      int c;
      while ((c = getchar()) != 0) {
        putchar(c);
      }
    } else {
      FILE* fd = fopen(argv[i], "r");
      if (fd == NULL) {
        err(1, "%s", argv[i]);
      }
      char buffer[BUFFER_SIZE];
      int read;
      while ((read = fread(&buffer, BUFFER_SIZE, 1, fd)) != 0) {
        printf("%s", buffer);
      }
      fclose(fd);
    }
  }
  exit(0);
}
