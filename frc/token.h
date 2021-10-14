/** \file token.h
 *
 * Token definitions
 */
#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
#define TOK(X) X,
#include "tokens.def"
#undef TOK
  NUM_TOKENS
} token_kind_t;

#endif // ifndef TOKEN_H
