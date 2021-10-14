/** \file pipeline.c
 *
 * Implementation for pipeline.h
 *
 */
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "parser.h"
#include "pipeline.h"

struct pipeline_ {
  error_handler_t error_handler;
};

pipeline_t * pipeline_init(error_handler_t error_handler) {
  pipeline_t * p = malloc(sizeof(pipeline_t));

  if (p)
    p->error_handler = error_handler;
  else
    error_handler("Internal error: failed to allocate pipeline object");

  return p;
}

void pipeline_free(pipeline_t * pipeline) {
  free(pipeline);
}

bool pipeline_process_input(pipeline_t * pipeline, FILE * input) {
  assert(pipeline);
  assert(input && "Pipeline input");

  parser_t * parser = parser_init(input, pipeline->error_handler);

  bool success = parse_top_level_declarations(parser);

  parser_free(parser);

  return success;
}

bool pipeline_emit(pipeline_t * pipeline, FILE * output) {
  assert(pipeline);
  assert(output && "Pipeline output");

  // TODO
  return true;
}
