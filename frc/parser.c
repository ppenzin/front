/** \file parser.c
 *
 * Implementation of functionality in parser.h
 *
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "lexer.h"
#include "parser.h"
#include "token.h"

struct parser_ {
  error_handler_t error_handler;
  lexer_t * lexer;
  FILE * input_stream;
};

bool parser_is_next_token(parser_t * parser, token_kind_t kind);

parser_t * parser_init(FILE * input, error_handler_t error_handler) {
  parser_t * p = malloc(sizeof(parser_t));

  if (p) {
    p->error_handler = error_handler;
    p->input_stream = input;
    p->lexer = lex(input, error_handler);
  } else
    error_handler("Internal error: failed to allocate parser object");

  return p;
}

void parser_free(parser_t * parser) {
  free(parser);
}

bool parse_top_level_declarations(parser_t * parser) {
  while(lex_token(parser->lexer)) {
    token_kind_t tok = get_token(parser->lexer);
    if (tok == invalid || tok == eof) break;
    // A cheat way to dump tokens (FIXME remove)
    parser->error_handler(get_token_string(parser->lexer));
    parser->error_handler("=======");
  }
  return true;
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

