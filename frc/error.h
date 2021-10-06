/** \file error.h
 *
 * Provide types for error callbacks
 *
 */
#ifndef ERROR_H
#define ERROR_H

/** Callback to report an error */
typedef void (*error_handler_t)(const char * error_string);

#endif // ifndef ERROR_H
