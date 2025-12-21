# CPP Module 06 — Exercise 01: Serializer

## Goal
Demonstrate **pointer serialization**:

- turn a “live” address (`Data*`) into an integer (`uintptr_t`)
- then convert it back into the original pointer type

## Core idea: `reinterpret_cast` (bit re-labeling)
This exercise revolves around `reinterpret_cast`, the “powerful but sharp” cast:

- **Zero conversion cost**: no real transformation of bits (unlike `static_cast`).
- **Label analogy**: the bits stay the same, you just change the type label (`Data*` ↔ `uintptr_t`).
- **GPS analogy**: a pointer is a location; `uintptr_t` is that location written as a number.

## `uintptr_t` vs `void*`
- **`void*`**: “an address, but unknown object type”.
- **`uintptr_t`**: a real integer type guaranteed to hold a pointer value (platform-sized).
- **Typical uses**: packet formats, hashing, memory-mapped I/O (hardware addresses).

## Implementation checks
- **Identity check**: `&data == deserialized_data` proves round-trip correctness.
- **Hex check**: printing with `std::hex` makes it obvious the integer value matches the address bits.