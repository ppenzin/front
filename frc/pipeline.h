/** \file pipleine.h
 * 
 * Define high-level pipeline handling interactions
 *
 */

/** Callback to report an error */
typedef void (*error_handler_t)(const char * error_string);

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
 * Errors are reported via provided callback
 */
bool pipeline_process_input(pipeline_t * pipeline, FILE * input);

/** Emit bytecode to a file
 *
 * \param pipeline pointer to pipeline object
 * \param output file pointer for the output
 * \return true if success, false otherwise
 *
 * Errors are reported via provided callback
 */
bool pipeline_emit(pipeline_t * pipeline, FILE * output);

