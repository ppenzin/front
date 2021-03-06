#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#ifndef _WIN32 // FIXME this might need to live in a separate file
#include <libgen.h>
#endif

#include "pipeline.h"

/** Print basic tool usage
 * \param out output stream/file
 * \param tool_name current file name of the tool
 */
void print_usage(FILE * out, const char * tool_name) {
  fprintf(out, "Usage: %s <input> [-o output]\n", tool_name);
}

/** Extract command line tool name
 *
 * \param path possibly extended file path
 * \return minimal string that user needs to type to reference the tool
 *
 * FIXME this is needed solely due to platform differences, maybe it needs to
 * be in its own file
 */
char * exe_name(char * path) {
#ifndef _WIN32
  return basename(path);
#else
  char * name = malloc(strlen(path) + 1); // TODO deallocate
  _splitpath(path, NULL, NULL, name, NULL);
  return name;
#endif
}

/** Report an error
 * \param error string to print
 */
void report_error(const char * error) {
  fprintf(stderr, "Error: %s\n", error);
}

int
main (int argc, char ** argv) {
  const char * input = NULL;
  const char * output = NULL;
  unsigned i;

  /* tool name */
  const char * name = exe_name(argv[0]);

  /* parse command line arguments */
  for (i = 1; i < argc; ++i) {
    if (!strcmp("-o", argv[i])) {
      if (i == argc - 1) {
        fputs("'-o' requires a filename argument\n", stderr);
        print_usage(stderr, name);
        exit(8);
      } else if (output) {
        fputs("Only one output argument ('-o') is allowed\n", stderr);
        print_usage(stderr, name);
        exit(8);
      } else {
        output = argv[++i];
      }
    } else if (input) {
      fputs("Only one input argument is allowed\n", stderr);
      print_usage(stderr, name);
      exit(8);
    } else {
      input = argv[i];
    }
  }

  if (!input) {
    if (output) {
      fputs("Required input file name\n", stderr);
      print_usage(stderr, name);
      exit(8);
    } else {
      print_usage(stdout, name);
      exit(8);
    }
  }
  
  if (!output) output = "a.wasm";

  /* Open the input file */
  FILE * in_file = fopen(input, "rb");
  if (!in_file) {
    fprintf(stderr, "Could not open input file %s\n", input);
    exit(8);
  }

  /* Initialize pipeline */
  pipeline_t * pipeline = pipeline_init(report_error);

  /* Process input */
  bool have_errors = pipeline_process_input(pipeline, in_file);

  fclose(in_file);
 
  if (have_errors)
    exit(8);

  /* Open the output file */
  FILE * out_file = fopen(output, "wb");
  if (!out_file) {
    fprintf(stderr, "Could not open output file %s\n", output);
    exit(8);
  }

  /* Emit bytecode */
  have_errors = pipeline_emit(pipeline, out_file);

  fclose(out_file);

  if (have_errors)
    exit(8);

  return 0;
}
