Implementation details
======================

First cut. Support only "stateful" and basic types, since more complex types require memory management. Export everything and import nothing. Every source file compiles (one at a time) to a single complete WebAssembly module.

For a more functional solution add semi-automatic memory management, while still compiling a source modeule to a Wasm module (rely on exporting for multiple-module use cases).

Multi-module compilation should either be fixed via `module-linking`, or by a static module linker (inner modules absorb into outer modules).

