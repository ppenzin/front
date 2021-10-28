/** \file lexer.c
 * 
 * Implementation of functionality in lexer.h
 *
 */

#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "dstr.h"
#include "lexer.h"
#include "token.h"

struct lexer_ {
  // We treat current token as state, since there is no externally visible way
  // to get between the states
  token_kind_t state;
  // Current token string
  dstr_t * token;
  // Error callback
  error_handler_t error_handler;
  // Input stream/file to tokenize
  FILE * input;
};

/** Report error
 *
 * \param lexer object
 * \param str string to report
 */
void lexer_error(lexer_t * lexer, const char * str);

/** Scan for a string
 *
 * \param target string to scan for
 * \param input FILE pointer to read from
 * \param dst string pointer to write the characters to, gets heap allocated
 * \return true entire target was read, false otherwise
 *
 * dst needs to be freed after the call
 */
bool scan_for(const char * target, FILE * input, char ** dst);

lexer_t * lex(FILE * input, error_handler_t error_handler) {
  lexer_t * l = malloc(sizeof(lexer_t));

  if (l) l->token = new_dstr();

  if (l && l->token) {
    l->error_handler = error_handler;
    l->input = input;
    l->state = unknown;
  } else
    error_handler("Internal error: failed to allocate lexer object");

  return l;
}

void lexer_free(lexer_t * lexer) {
  free_dstr(lexer->token);
  free(lexer);
}

bool lex_token(lexer_t * lexer) {
  lexer->state = unknown;
  dstr_cpy(lexer->token, "");

  while (lexer->state != eof && lexer->state != invalid) {
    int c = getc(lexer->input);
    char * str; // Scratch string to read text into
    if (lexer->state == unknown) {
      /*** Token start **/
      if (feof(lexer->input)) { // Initial attempt to read brings EOF
        lexer->state = eof;
      } else switch (c) {
        case '(':
          lexer->state = tk_lparen;
          dstr_addc(lexer->token, c);
          break;
        case ')':
          lexer->state = tk_rparen;
          dstr_addc(lexer->token, c);
          break;
        case ',':
          lexer->state = tk_comma;
          dstr_addc(lexer->token, c);
          break;
        case ':': // FIXME removed from the examples
          lexer->state = tk_colon;
          dstr_addc(lexer->token, c);
          break;
        case '=':
          lexer->state = tk_eq;
          dstr_addc(lexer->token, c);
          break;
        case '-':
            c = getc(lexer->input);
            if (c == '>') {
                dstr_adds(lexer->token, "->");
                lexer->state = tk_rarrow;
            } else {
                char error[30]; // Make sure full error string fits here
                char ch[3];
                strcpy(error, "Unrecognized sequence: '");
                ch[0] = '-';
                ch[1] = c;
                ch[2] = '\0';
                strcat(error, ch);
                strcat(error, "'");
                lexer_error(lexer, error); // TODO better way to compose error
                ungetc(c, lexer->input);
                ungetc('-', lexer->input);
                lexer->token = invalid;
            }
            break;
        case 'i':
          dstr_addc(lexer->token, c);
          if (scan_for("nt", lexer->input, &str))
            lexer->state = kw_int;
          else
            lexer->state = tk_identifier;
          dstr_adds(lexer->token, str);
          free(str);
          break;
        case 'u':
          dstr_addc(lexer->token, c);
          if (scan_for("ndefined", lexer->input, &str))
            lexer->state = kw_undefined;
          else
            lexer->state = tk_identifier;
          dstr_adds(lexer->token, str);
          free(str);
          break;
        default:
          if (isalpha(c)) {
            dstr_addc(lexer->token, c);
            lexer->state = tk_identifier;
          } else if (isspace(c)) {
            // Consume space characters
            // TODO if this is valid for all statements
          } else {
            lexer->state = invalid;
            char error[30]; // Make sure full error string fits here
            char ch[2];
            strcpy(error, "Unrecognized character: '");
            ch[0] = c;
            ch[1] = '\0';
            strcat(error, ch);
            strcat(error, "'");
            lexer_error(lexer, error); // TODO better way to compose error
          }
          break;
      }
    } else {
      /*** Token end **/
      if (feof(lexer->input)) {
        break; // Catching an EOF means end of the token
      }
      switch (c) {
        case '(':
        case ')':
        case ',':
        case ':':
        case '=':
          ungetc(c, lexer->input); // Done, latest character back to stream
          return true;
        default:
          if (isspace(c)) {
            return true;
          } else if (isalpha(c) || isdigit(c)) {
            // Turn finished keywords to ID, terminate punctuators
            // TODO need 'is punctuator', 'is keyword', etc
	    if (token_is_punctuator(lexer->state)) {
                ungetc(c, lexer->input); // Done, latest character back to stream
                return true;
	    }
	    if (token_is_keyword(lexer->state)) {
	        lexer->state = tk_identifier; // int123 and the like
	        dstr_addc(lexer->token, c);
	    } else if (lexer->state == tk_identifier) {
	        lexer->state = tk_identifier; // int123 and the like
	        dstr_addc(lexer->token, c);
	    } // TODO anything else?
          }
          break;
      }
    }
  }
  assert(lexer->state != unknown);
  return (lexer->state != invalid);
}

token_kind_t get_token(lexer_t * lexer) {
  return lexer->state;
}

const char * get_token_string(lexer_t * lexer) {
  return dstr_cstr(lexer->token);
}

void lexer_error(lexer_t * lexer, const char * str) {
  assert(lexer);
  lexer->error_handler(str);
}

bool scan_for(const char * target, FILE * input, char ** dst) {
  size_t length = strlen(target);
  *dst = malloc(length + 1); // Enough space for entire pattern
  if (!dst) return false;

  // Copy matching characters
  for (int i = 0; i < length; ++i) {
    int c = getc(input);
    if (c == target[i]) {
      (*dst)[i] = c;
    } else { // Mismatch
      // Return character to the stream
      ungetc(c, input);
      // Terminate destination string
      (*dst)[i] = '\0';
      return false;
    }
  }
  (*dst)[length] = '\0';

  return true;
}

bool token_is_punctuator(token_kind_t kind) {
  switch (kind) {
#undef PUNCTUATOR
#define PUNCTUATOR(X, Y) case tk_ ## X:
#include "tokens.def"
#undef PUNCTUATOR
      return true;
    default:
      return false;
  }
}

bool token_is_keyword(token_kind_t kind) {
  switch (kind) {
#undef KEYWORD
#define KEYWORD(X, Y) case kw_ ## X:
#include "tokens.def"
#undef PUNCTUATOR
      return true;
    default:
      return false;
  }
}
