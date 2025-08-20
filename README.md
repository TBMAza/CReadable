# CReadable

**CReadable** is a lightweight C library that makes it easier for C programmers to write and parse large numeric literals in source code.

Instead of writing unreadable long numbers like:

```c
int x = 1000000000;
```

you can now write:

```c
int x = rint(1_000_000_000);   // more readable
```

CReadable automatically parses strings with separators (`_`, `,`, or spaces) into integers or floating-point values, performing type safety checks and reporting errors on invalid input.

---

## Features

* Readable numeric literals for all standard C types:

  * `char`, `signed char`, `unsigned char`
  * `short`, `unsigned short`
  * `int`, `unsigned int`
  * `long`, `unsigned long`
  * `long long`, `unsigned long long`
  * `float`, `double`, `long double`
* Allows separators in numbers:

  * Underscore (`_`): `1_234_567`
  * Comma (`,`) : `1,234,567`
  * Space (` `) : `12 345`
* Handles negative numbers
* Detects and reports overflow/underflow
* Reports type mismatches (e.g., assigning float to int, or int to float)
* Gracefully defaults to zero on error
* Boundary values supported (e.g., `INT_MAX`, `LLONG_MIN`, `ULLONG_MAX`)

---

## Installation

Simply add **`creadable.h`** and **`creadable.c`** to your project and include the header:

```c
#include "creadable.h"
```

Compile them together with your project:

```bash
gcc main.c creadable.c -o main
```

---

## Usage

```c
#include <stdio.h>
#include "creadable.h"

int main(void) {
    int a = rint(1_234_567);             // 1234567
    unsigned long b = rulong(18,446,744,073,709,551,615);
    float pi = rfloat(3.14159);
    double e = rdouble(2.71828);

    printf("%d\n", a);
    printf("%lu\n", b);
    printf("%f\n", pi);
    printf("%f\n", e);

    return 0;
}
```

### Example Output

```
1234567
18446744073709551615
3.141590
2.718280
```

---

## Known Limitations

CReadable is experimental, and some edge cases are **not yet supported**:

1. **Scientific notation not supported**

   ```c
   float f = rfloat(3.402823e+38); // ❌ FAILS
   ```

   Currently, `e` or `E` is treated as an invalid character.

2. **Float/Int strictness is intentional**
   For readability, CReadable enforces explicit decimal points for floating-point literals:

   ```c
   float x = rfloat(1234);   // ❌ invalid: missing decimal point
   float y = rfloat(1234.0); // ✅ valid
   int z = rint(12.34);      // ❌ invalid: float assigned to int
   ```

   This is by design to encourage clearer numeric literals.

3. **Performance**

   * Each call involves parsing and allocating memory internally (freed automatically).
   * Not intended for tight loops or performance-critical code.

---

## Test Results

Out of **41 tests**, **39 passed** and **2 failed** (due to scientific notation not being supported yet).

```
==== SUMMARY ====
Total: 41 | Passed: 39 | Failed: 2
```

---

## Roadmap

* [ ] Add support for scientific notation (`e`, `E`)
* [ ] Optimize parsing to avoid unnecessary allocations
* [ ] Add CI tests and package release on GitHub

---

## License

MIT License – feel free to use, modify, and distribute.
