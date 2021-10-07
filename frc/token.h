/** \file token.h
 *
 * Token definitions
 */

typedef enum {
#define TOK(X) X,
#include "tokens.def"
#undef TOK
  NUM_TOKENS
} token_kind_t;

