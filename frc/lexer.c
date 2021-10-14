/** \file lexer.c
 * 
 * Implementation of functionality in lexer.h
 *
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "lexer.h"
#include "token.h"

struct lexer_ {
  error_handler_t error_handler;
  token_kind_t current_token;
  FILE * input_stream;
};

/** Report error
 *
 * \param lexer object
 * \param str string to report
 */
void lexer_error(lexer_t * lexer, const char * str);

lexer_t * lex(FILE * input, error_handler_t error_handler) {
  lexer_t * l = malloc(sizeof(lexer_t));

  if (l) {
    l->error_handler = error_handler;
    l->input_stream = input;
    l->current_token = unknown;
  } else
    error_handler("Internal error: failed to allocate lexer object");

  return l;
}

void lexer_free(lexer_t * lexer) {
  free(lexer);
}

bool lex_token(lexer_t * lexer) {
  lexer_error(lexer, "Unimplemnted");
  return false;
}

token_kind_t get_token(lexer_t * lexer) {
  return lexer->current_token;
}

void lexer_error(lexer_t * lexer, const char * str) {
  assert(lexer);
  lexer->error_handler(str);
}

