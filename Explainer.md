# Let's imagine: functional language

Might need to convert recursion to loops, though it might be possible to run
with it as is as a baseline.

Weakest point of purely functional approach in Wasm currently is that it
requires lots of intermediate allocations, since variables can only be assigned
once. It would require writing a GC if language needs it. Lazy evaluation would
probably have its own fun aspects, though I haven't thought about it much yet.

One optimization would be returning non-scalar results via a hidden pointer
argument, basically writing them to final destination. Another thing I can
think of would be defining memory region semantics for recursive functions, for
example requiring the return of every step of the recursion fit inside the
return of its predecessor (I am not sure if that is really necessary, since not
doing this may mean you will never converge).

Purely funcitonal approach would hit the memory management bump described
above, though at least it is relatively clear how to do it.

The dataflow approach could avoid the memory management hole, at least to a
point, for example by focusing on relationship of data areas before and after
function invocations. I think this would have to have a syntax within the
language, but I am not sure what that would be - should it be something usable
for other purposes (say "instance of" some special typeclass), or a completely
separate syntax for this problem (for example how CUDA uses a separate syntax
to describe layout).

## Data region layout, pointer affinity

I think that the mechanism to describe layout needs to outline relationship
between memory areas for arguments and return values. This can also include
writing result over the arguments after allocating the intermediate area in the
function, to enable memory clean up on every call. Scalar values (even the ones
corresponding to a record) will have special meaning since they can be returned
on the stack and don't have to be accounted for - it should be possible to use
that to swap a few elements, for example.

Ideas:

```
foo :: int(:) -> int(:)
foo - N -> N-1
foo extends state (M->N) where M = N - 1
```

Or encode space allocation in accessor syntax:

```
foo (state (int[30] x)) {
  y = substate (x, 0, 15)
  z = substate (x, 15, 15)
  ... do something with y and z
}
```

Also, maybe look for inspritaiton in fortran "interface" syntax.

This is by the way pointer provenance or pointer affinity in action.

## Syntax

```
int foo(int x, float y) = ...

(if (cond) then (stmt) else (stmt))

```

## Practical shortcuts

No linking - maybe just compile one source file to one module.

ASCII instead of UTF-8 for now.

