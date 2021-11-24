add_library(common OBJECT
  dstr.c
  main.c
  pipeline.c
)

# Front compiler
add_executable(frc
  $<TARGET_OBJECTS:common>
  lexer.c
  parser.c
)

if (ENABLE_TESTING)
  # Test interpreter utility
  add_executable(frti
    $<TARGET_OBJECTS:common>
    lexer.c
    parser.c
  )
  target_compile_definitions(frti PUBLIC TESTING)
endif (ENABLE_TESTING)
