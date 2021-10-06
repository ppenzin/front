/** \file pipleine.h
 * 
 * Define high-level pipeline handling interactions
 *
 */
#ifndef PIPELINE_H
#define PIPELINE_H

#include "error.h"

/** Anonymous pipeline type */
typedef struct pipeline_ pipeline_t;

/** Initialize pipeline
 *
 * \param error_handler error reporting function
 * \return new pipeline object or NULL if allocation fails
 *
 * Funtion calls provided error handler to report allocation failures
 */
pipeline_t * pipeline_init(error_handler_t error_handler);

/** Deallocate pipeline object and associated state
 *
 * \param pipeline pointer to a pipeline object
 */
void pipeline_free(pipeline_t * pipeline);

/** Process a file input
 *
 * \param pipeline pointer to pipeline object
 * \param input file pointer for the input
 * \return true if success, false otherwise
 *
 * Errors are reported via provided callback, but it asserts on input being
 * non-null.
 */
bool pipeline_process_input(pipeline_t * pipeline, FILE * input);

/** Emit bytecode to a file
 *
 * \param pipeline pointer to pipeline object
 * \param output file pointer for the output
 * \return true if success, false otherwise
 *
 * Errors are reported via provided callback, but it asserts on output being
 * non-null.
 */
bool pipeline_emit(pipeline_t * pipeline, FILE * output);

#endif // ifndef PIPELINE_H
