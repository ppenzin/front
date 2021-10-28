# Functional language for WebAssembly

Going with a functional language takes avoidance of relooper to a whole new
level.

Might need to convert recursion to loops, though it might be possible to run
with it as is as a baseline.

Weakest point of purely functional approach in Wasm is memory allocation (it
has no automatic memory management).

## Handling mutable memory

Objects not fitting in 'locals' would need to be returned by memory and
pointers can be, and should be (if we care about performance) updated. An
inspiration can be taken from Haskell's State monad - a type where every value
represents a state of changed pointer. If such type cannot be directly copied,
then it would be fit to update mutable memory without too much extra overhead.

## Syntax

Some ideas:

```
foo(x: int , y: float): int  = ...

```

```
int foo(int x, float y) = ...
bool foo(double z, (double->double) f) = ...
bool foo(double z, double f(double)) = ... // Cumbersome, agrument name missing
```

```
(if (cond) then (stmt) else (stmt))

```

## Practical shortcuts

No linking - maybe just compile one source file to one module.

ASCII instead of UTF-8 for now.

## Kitchen sink

Lazy evaluation would probably have its own fun aspects, though maybe an
experiment for a different time.

