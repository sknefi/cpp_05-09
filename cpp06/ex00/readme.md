# CPP Module 06 — Exercise 00: Scalar Converter

## Goal
Build a small **static utility** that converts a string literal into the four scalar types:
`char`, `int`, `float`, `double`.

## Concept refresher: “scalar”
A **scalar** is fully described by its magnitude (a single value).

- **Scalar**: 1D (e.g. `42`) → magnitude only
- **Vector**: 2D (e.g. `[x, y]`) → magnitude + direction
- **Matrix**: 3D (grid/array of values)
- **Tensor**: 4D+ (multi-dimensional structures; common in ML/physics)

## Casting note: `static_cast`
Compared to old C-style casts like `(int)v`, `static_cast` is the “safe / explicit” cast:

- It performs **real conversions** (may emit CPU instructions).
- Example: converting `int` → `float` requires building a float representation (sign/exponent/mantissa).

## Implementation notes (what matters in practice)
- **Precision limits**:
  - `float` (32-bit) ≈ ~7 digits of precision (23-bit mantissa)
  - `double` (64-bit) ≈ ~15–17 digits (52-bit mantissa)
- **Parsing with `strtod`**:
  - `end_ptr` tells you where parsing stopped.
  - If `literal.c_str() == end_ptr`, the input wasn’t numeric.
- **Consistent output formatting**:
  - `std::fixed` + `std::setprecision(1)` keeps `.0` visible (e.g. `42.0f`), so floats/doubles don’t “look like ints”.
- **Overflow guards**:
  - Use `std::numeric_limits` to avoid undefined behavior when converting huge values into smaller integer types.