// ls

#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <errno.h>
#include <dirent.h>
#include <sys/types.h>
#include "arg_parser.h"
#include "ls_colors.h"

struct ARGPARSE_STRUCT {
  int a, h, c;
} ARGPARSE_STRUCT;

ARGPARSE_SETUP(
  ARGPARSE_CHECK(a)
  ARGPARSE_CHECK(c)
  ARGPARSE_CHECK(h)
)

int list_dir(const char* path) {
  DIR* dstream = opendir(path);
  if (dstream == NULL) {
    err(errno, path);
  }
  struct dirent* dir_ent;
  while (1) {
    if ((dir_ent = readdir(dstream)) == NULL) {
      break;
    } else {
      if ((dir_ent->d_name[0] != '.') || (opts.a == 1)) {
        int color;
        if (opts.c == 1) {
          int type = dir_ent->d_type;
          if (type == DT_BLK) {
            color = FTYPE_BLK;
          } else if (type == DT_CHR) {
            color = FTYPE_CHR;
          } else if (type ==  DT_DIR) {
            color = FTYPE_DIR;
          } else if (type == DT_FIFO) {
            color = FTYPE_FIFO;
          } else if (type == DT_LNK) {
            color = FTYPE_LNK;
          } else if (type == DT_SOCK) {
            color = FTYPE_SOCK;
          } else if (type == DT_UNKNOWN) {
            color = FTYPE_UNKNOWN;
          } else {
            color = 37;
          }
        } else {
          color = 37;
        }
        printf("\x1B[%dm%s\x1B[37m\n", color, dir_ent->d_name);
      }
    }
  }
  closedir(dstream);
  return 0;
}

int main(int argc, const char** argv) {
  int offset = ARGPARSE_FUNCTION(argc, argv);

  if (opts.h == 1) {
    printf(
        "usage: %s [opts] [dir [...]]\n"
        "Lists all files in each provided 'dir'.\n"
        "Accepted options are:\n"
        "  -a: show filenames beginning with a '.'\n"
        "  -c: colorize output\n"
        "  -h: print this help\n\n"
        "Copyright (c) 2021 Ocawesome101 under the GPLv3.\n", argv[0]);
    exit(0);
  }
  
  if (offset == argc) {
    list_dir(getenv("PWD"));
    exit(0);
  }

  for (int i = offset; i < argc; i++) {
    if (argc - offset > 1) {
      printf("%s:\n", argv[i]);
    }
    list_dir(argv[i]);
  }
}
