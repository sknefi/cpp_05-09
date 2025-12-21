# CPP Module 06 - Exercise 00: Scalar Converter

### 🎯 Project Overview
Creating a static utility class to convert string literals into the four fundamental scalar types of C++.

### 🔬 Theory: What is a Scalar?
We discussed that a **Scalar** is a physical quantity that is fully described by its magnitude (a single number).
* **Scalar:** 1D (e.g., `42`). Just a magnitude.
* **Vector:** 2D (e.g., `[x, y]`). Magnitude + Direction.
* **Matrix:** 3D (A grid/array of values).
* **Tensor:** 4D+ (Complex multi-dimensional arrays used in AI and General Relativity).

In this project, we focused on **Scalar types**: `char`, `int`, `float`, and `double`.



### 🛡️ The Power of `static_cast`
Unlike the old C-style cast `(int)v`, `static_cast` is the "Safe/Logical" cast. 
* It actually **executes CPU instructions** to transform bit patterns. 
* Converting `int` to `float` requires moving the sign bit and calculating an exponent/mantissa.

### 🛠️ "Flashback" Implementation Details
* **Precision & Bits:** We discussed that a `float` (32-bit) only has ~7 digits of precision because its **Mantissa** is only 23 bits wide. A `double` (64-bit) has ~15-17 digits because its Mantissa is 52 bits wide.
* **The `end_ptr` Logic:** We used `strtod` because it gives us a pointer to where the parsing stopped. If `literal.c_str() == end_ptr`, it means the input was purely non-numeric garbage.
* **The `.0` Requirement:** We used `std::fixed` and `std::setprecision(1)` to ensure floating-point values are visually distinct from integers, even if they are whole numbers (e.g., `42.0f`).
* **Overflow Guards:** We used `std::numeric_limits` to prevent "Undefined Behavior" that occurs when trying to shove a massive double into a small integer container.