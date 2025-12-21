# CPP Module 06 - Exercise 02: Real Type

### 🎯 The Mission
To master **Runtime Type Identification (RTTI)** by "unmasking" a hidden child class (`A`, `B`, or `C`) hidden behind a generic `Base` pointer.

### 🔬 The Deep Theory: VTables and ID Cards
We learned that `dynamic_cast` is the only cast that "asks" the object what it is at runtime.
* **The VTable (Virtual Table):** For `dynamic_cast` to work, the class must be **polymorphic**. We added a `virtual ~Base()` destructor, which forces the compiler to create a VTable.
* **The ID Check:** Think of the VTable as an internal "ID Card." `dynamic_cast` looks at this card to see if the object's blueprint matches the class we are trying to cast into.



### 🛡️ Pointers vs. References
We handled the two different ways `dynamic_cast` reports failure:
1. **Pointers:** Returns `NULL` if the cast fails. We used `if/else` checks.
2. **References:** References **cannot** be NULL. If the cast fails, C++ throws a `std::bad_cast` exception. We used `try/catch` blocks to handle this safely.



### 🛠️ "Flashback" Implementation Notes
* **Bypassing `<typeinfo>`:** The subject forbids the header where `std::bad_cast` lives. We successfully bypassed this by catching the parent `std::exception`.
* **The Randomness Seed:** We remembered to call `srand(time(0))` **only once** in `main`. If called inside `generate()`, the rapid-fire calls would result in the same "random" class every time due to the clock resolution.