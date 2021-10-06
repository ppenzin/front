/** \file parser.c
 *
 * Implementation of functionality in parser.h
 *
 */

#include <stdlib.h>
#include <stdio.h>

#include "parser.h"

struct parser_ {
  error_handler_t error_handler;
  FILE * input_stream;
};

parser_t * parser_init(FILE * input, error_handler_t error_handler) {
  parser_t * p = malloc(sizeof(parser_t));

  if (p) {
    p->error_handler = error_handler;
    p->input_stream = input;
  } else
    error_handler("Internal error: failed to allocate parser object");

  return p;
}

void parser_free(parser_t * parser) {
  free(parser);
}

