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

/** Token is a punctuator
 *
 * \param kind token kind
 * \return true if token is a punctuator, false otherwise
 */
bool token_is_punctuator(token_kind_t kind);

/** Token is a keyword
 *
 * \param kind token kind
 * \return true if token is a keyword, false otherwise
 */
bool token_is_keyword(token_kind_t kind);

#endif // ifndef TOKEN_H
