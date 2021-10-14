/** \file parser.h
 *
 * Source parser functionality
 *
 */
#ifndef PARSER_H
#define PARSER_H

#include "error.h"

/** Forward-declared parser object */
typedef struct parser_ parser_t;

/** Allocate and init parser
 *
 * \param input (file) stream to read
 * \param error_handler function to handle errors
 * \return parser object or NULL if allocation fails
 *
 * Attempt to report alloaction errors using error handler
 */
parser_t * parser_init(FILE * input, error_handler_t error_handler);

/** Free parser entity
 *
 * \param parser entity to destroy
 */
void parser_free(parser_t * parser);

/** Parse top level declarations
 *
 * \param parser the parser to use
 * \return true on success, false otherwise
 *
 * This function uses error handling callback to report errors
 */
bool parse_top_level_declarations(parser_t * parser);

// TODO various entities to parse

#endif // ifndef PARSER_H
