/** \file dstr.c
 *
 * Implementation of the dynamic string
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "dstr.h"

// Allocation increment
const size_t increment = 256;

struct dstr_ {
  /// Current allocated size
  size_t allocated_size;
  /// C-string contatining the data
  char * data;
};

dstr_t * new_dstr(void) {
  // Allocate the object
  dstr_t * s = malloc(sizeof(dstr_t));
  if (!s) return NULL;
  // Allocate 'increment' sized string in it
  s->data = malloc(increment);
  if (!s->data) {
    free(s);
    return NULL;
  }
  s->allocated_size = increment;
  // Null-terminate to initialize as an empty string
  s->data[0] = '\0';
  return s;
}

void free_dstr(dstr_t * dstr) {
  free(dstr->data);
  free(dstr);
}

dstr_t * dstr_cpy(dstr_t * to, const char * from) {
  // Space needed to store source string
  size_t size = strlen(from) + 1;

  // Reallocate if needed
  if (size > to->allocated_size) {
    size_t new_size = (size / increment + 1) * increment;
    char * new_data = realloc(to->data, new_size);
    if (!new_data) return NULL; // Failed to reallocate
    to->data = new_data;
    to->allocated_size = new_size;
  }

  // Copy string
  strcpy(to->data, from);

  return to;
}

dstr_t * dstr_addc(dstr_t * to, int c) {
  // String length of the existing portion
  size_t length = strlen(to->data);

  // We expect to add two characters (char + null)
  if (length + 2 > to->allocated_size) {
    size_t new_size = to->allocated_size + increment;
    char * new_data = realloc(to->data, new_size);
    if (!new_data) return NULL; // Failed to reallocate
    to->allocated_size = new_size;
    to->data = new_data;
  }

  // Write
  to->data[length] = c;
  to->data[length + 1] = '\0';

  return to;
}

dstr_t * dstr_adds(dstr_t * to, const char * s) {
  // Expected string length of the final string
  size_t expected_length = strlen(to->data) + strlen(s);

  // Not enough space
  if (expected_length + 1 > to->allocated_size) {
    size_t new_size = ((expected_length + 1) / increment + 1) * increment;
    char * new_data = realloc(to->data, new_size);
    if (!new_data) return NULL; // Failed to reallocate
    to->data = new_data;
    to->allocated_size = new_size;
  }

  // Append the string
  strcat(to->data, s);

  return to;
}

const char * dstr_cstr(dstr_t * d) {
  return d->data;
}
