/** \file parser.c
 *
 * Implementation of functionality in parser.h
 *
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "parser.h"
#include "token.h"

struct parser_ {
  error_handler_t error_handler;
  FILE * input_stream;
};

bool parser_is_next_token(parser_t * parser, token_kind_t kind);

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

/** Check if the next token matches given type
 *
 * \param parser parser object to use
 * \param kind token type
 * \return true if there a match, false otherwise
 */
bool parser_is_next_token(parser_t * parser, token_kind_t kind) {
  return false; // TODO
}

