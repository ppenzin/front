/** \file lexer.h
 * 
 * Lexer (tokenizer) functionality
 *
 */

#include "error.h"
#include "token.h"

typedef struct lexer_ lexer_t;

/** Allocate and initialize lexer
 *
 * \param input file to tokenize
 * \param error_handler error handler callback
 * \return lexer object or NULL if allocation fails
 *
 * Attempt to report alloaction errors using error handler
 */
lexer_t * lex(FILE * input, error_handler_t error_handler);

/** Free lexer entity
 *
 * \param lexer entity to destroy
 */
void lexer_free(lexer_t * lexer);

/** Lex a token
 *
 * \param lexer object to use
 * \return true on success, false - otherwise
 */
bool lex_token(lexer_t * lexer);

/** Get current token's kind
 *
 * \param lexer object to use
 * \return token ID of the current token
 */
token_kind_t get_token(lexer_t * lexer);
