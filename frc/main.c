#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libgen.h>

/** Print basic tool usage
 * \param out output stream/file
 * \param tool_name current file name of the tool
 */
void print_usage(FILE * out, const char * tool_name) {
  printf("Usage: %s <input> [-o output]\n", tool_name);
}

int
main (int argc, char ** argv) {
  const char * input = NULL;
  const char * output = NULL;
  unsigned i;

  /* tool name */
  const char * name = basename(argv[0]);

  /* parse command line arguments */
  for (i = 1; i < argc; ++i) {
    if (!strcmp("-o", argv[i])) {
      if (i == argc - 1) {
        fprintf(stderr, "'-o' requires a filename argument\n");
        print_usage(stderr, name);
        exit(8);
      } else if (output) {
        fprintf(stderr, "Only one output argument ('-o') is allowed\n");
        print_usage(stderr, name);
        exit(8);
      } else {
        output = argv[++i];
      }
    }
    if (input) {
      fprintf(stderr, "Only one input argument is allowed\n");
      print_usage(stderr, name);
      exit(8);
    } else {
      input = argv[++i];
    }
  }

  if (!input) {
    if (output) {
      fprintf(stderr, "Required input file name\n");
      print_usage(stderr, name);
      exit(8);
    } else {
      print_usage(stdin, name);
      exit(8);
    }
  }
  
  if (!output) output = "a.wasm";

  return 0;
}
