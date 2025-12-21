# CPP Module 06 — Exercise 02: Real Type

## Goal
Practice **RTTI (Runtime Type Identification)** by “unmasking” a hidden derived class
(`A`, `B`, or `C`) behind a `Base*`.

## Why `dynamic_cast` works (polymorphism requirement)
`dynamic_cast` is the cast that can ask: “what are you really at runtime?”

To make that possible, the base class must be **polymorphic** (i.e., have at least one virtual function).
In this exercise that’s usually done by adding:

- `virtual ~Base()` (virtual destructor)

This forces the compiler to generate the RTTI/vtable metadata that `dynamic_cast` relies on.

## Pointer cast vs reference cast
`dynamic_cast` reports failure differently depending on what you cast to:

1. **Pointers** (`dynamic_cast<T*>(p)`):
   - returns `NULL` on failure
   - use `if/else` checks

2. **References** (`dynamic_cast<T&>(obj)`):
   - cannot be null
   - throws `std::bad_cast` on failure
   - use `try/catch`

## Implementation notes
- **No `<typeinfo>`**: if your subject forbids it, catching `std::exception` is enough (it will catch `std::bad_cast`).
- **Random seed**: call `srand(time(0))` **once** in `main`, not inside `generate()`, otherwise multiple calls can produce the same “random” result.