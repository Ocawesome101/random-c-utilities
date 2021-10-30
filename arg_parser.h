// macro-based argument parsing
// yecch

#ifndef ARGPARSE_H
#define ARGPARSE_H

#define ARGPARSE_FUNCTION parse_arguments
#define ARGPARSE_STRUCT opts

#define ARGPARSE_SETUP(chunk) int ARGPARSE_FUNCTION (int argc, const char** argv) { \
  int i = 1; \
  for (i = 1; i < argc; i++) { \
    const char* arg = argv[i]; \
    if (arg[0] == '-') { \
      chunk \
    } else { \
      return i; \
    } \
  } \
  return i; \
}

#define ARGPARSE_CHECK(CH) if (arg[1] == (#CH)[0]) { ARGPARSE_STRUCT.CH = 1; }

#endif //ARGPARSE_H
