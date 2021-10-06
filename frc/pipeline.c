#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "pipeline.h"

struct pipeline_ {
  error_handler_t error_handler;
};

pipeline_t * pipeline_init(error_handler_t error_handler) {
  pipeline_t * p = malloc(sizeof(pipeline_t));

  if (!p) error_handler("Internal error: failed to allocate pipeline object");

  return p;
}

void pipeline_free(pipeline_t * pipeline) {
  free(pipeline);
}

bool pipeline_process_input(pipeline_t * pipeline, FILE * input) {
  assert(pipeline);

  // TODO
  return true;
}

bool pipeline_emit(pipeline_t * pipeline, FILE * output) {
  assert(pipeline);

  // TODO
  return true;
}
