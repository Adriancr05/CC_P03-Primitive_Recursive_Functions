# Assignment 3 - Primitive Recursive Functions

**Subject:** Computational Complexity  
**University:** Universidad de La Laguna  
**Degree:** Grado en Ingeniería Informática  
**Course:** 2026/2027  
**Date:** 30th October 2026

## Description

This program computes the function

```
power: ℕ × ℕ → ℕ
(x, y) ↦ x^y
```

as a **primitive recursive function** over the natural numbers. Every function is built exclusively from:

- the **basic functions**: Zero, Successor and Projection;
- the **operations**: Composition (which includes combination) and Primitive Recursion;
- other primitive recursive functions previously defined with those same tools.

After evaluating the function, the program prints:

- the result of the operation;
- the total number of function calls performed.

## Mathematical definition

Each function is derived from the previous one:

| Function | Base case | Recursive step |
|----------|-----------|----------------|
| `sum(x, y)` | `sum(x, 0) = P¹₁(x)` | `sum(x, y+1) = S(P³₃(x, y, sum(x, y)))` |
| `product(x, y)` | `product(x, 0) = Z(x)` | `product(x, y+1) = sum(P³₁(x, y, product(x, y)), P³₃(x, y, product(x, y)))` |
| `power(x, y)` | `power(x, 0) = S(Z(x))` | `power(x, y+1) = product(P³₁(x, y, power(x, y)), P³₃(x, y, power(x, y)))` |

**Basic functions:**

- **Zero:** `Z(x) = 0`
- **Successor:** `S(x) = x + 1`
- **Projection:** `Pⁿᵢ(x₁, …, xₙ) = xᵢ`

**Operations:**

- **Composition:** `f(g₁(x), …, gₙ(x))`
- **Primitive recursion:** `f(x, 0) = g(x)` and `f(x, y+1) = h(x, y, f(x, y))`

Note that, by this definition, `power(x, 0) = 1` for every `x`, including `x = 0`.


## Project structure

```
.
├── docs
│   └── CC_2627_Practica3.pdf              # Assignment statement
├── include
│   ├── basic_functions
│   │   ├── projection.h                   # Projection P^n_i
│   │   ├── successor.h                    # Successor S
│   │   └── zero.h                         # Zero Z
│   ├── basic_functions.h                  # Includes all basic functions
│   ├── derived_functions
│   │   ├── power.h                        # power(x, y) = x^y
│   │   ├── product.h                      # product(x, y) = x * y
│   │   └── sum.h                          # sum(x, y) = x + y
│   ├── operations
│   │   ├── composition.h                  # Composition / combination
│   │   └── recursion.h                    # Primitive recursion
│   ├── operations.h                       # Includes all operations
│   ├── primitive_recursive_function.h     # Abstract base class
│   └── tools.h                            # Argument parsing and execution helpers
├── src
│   ├── basic_functions/                   # Implementation of the basic functions
│   ├── derived_functions/                 # Implementation of sum, product and power
│   ├── operations/                        # Implementation of composition and recursion
│   ├── main.cc                            # Entry point
│   ├── primitive_recursive_function.cc
│   └── tools.cc
├── makefile
└── readme.md
```

## Design

The project follows an object-oriented design.

- **`PrimitiveRecursiveFunction`** is the abstract base class of every function. It exposes `operator()`, which increments a static call counter and then delegates to the private pure virtual method `evaluate()`. This guarantees that **every** invocation is counted, regardless of the concrete type.
- **`Zero`**, **`Successor`** and **`Projection`** implement the basic functions.
- **`Composition`** stores an outer function and a vector of inner functions. It evaluates every inner function on the same arguments (combination) and feeds the results to the outer function (composition).
- **`Recursion`** stores a base function `g` and a step function `h`, and evaluates `f(x, y)` iteratively, applying `h` `y` times.
- **`Sum`**, **`Product`** and **`Power`** are derived functions. Each one builds its definition using only the basic functions, the two operations and, in the case of `Product` and `Power`, the function defined before it.

### Call counting

The counter is incremented:

- once every time any function is invoked through `operator()`, and
- once per iteration of the recursion operator (in `Recursion::evaluate`).

The counter is reset before every evaluation in `execute_power`.

## Requirements

- A C++20 compatible compiler (`g++` is used by default)
- `make`
- A Unix-like shell (Linux/macOS; the makefile uses `find` and `mkdir -p`)

## Compilation

From the root of the project:

```bash
make
```

This compiles every `.cc` file under `src/` into `build/` and links the executable `power` in the root directory.

To remove the compiled files:

```bash
make clean
```

## Usage

```bash
./power -x <n> -y <n>
```

| Option | Description |
|--------|-------------|
| `-x <n>` | Natural number used as the **base** of the power |
| `-y <n>` | Natural number used as the **exponent** of the power |
| `-h`, `--help` | Shows the usage message |

Both options are required, and they can be given in any order.

### Examples

```bash
./power -x 2 -y 10
```

```
Result: 1024
Function calls: 1401244
```

```bash
./power -y 3 -x 5      # 5^3 = 125
./power -x 7 -y 0      # 7^0 = 1
./power --help
```

## Error handling

The program prints a message to `stderr` and exits with code `1` in the following cases:

| Situation | Behaviour |
|-----------|-----------|
| Wrong number of parameters | `Incorrect number of parameters. Use --help for more information.` |
| Unknown option | `Unknown parameter: <option>` |
| Negative value | `Error: negative values are not allowed` |
| Non-numeric value | `Error: '<value>' is not a number` |
| Trailing characters (e.g. `12abc`) | `Error: leftover characters in '<value>'` |
| Value larger than `unsigned` | `Error: the value '<value>' is too large` |
| Result does not fit in an `unsigned` | `overflow_error` raised by the Successor function |

Since the natural numbers are represented with `unsigned`, results exceeding its maximum value (typically 2³² − 1) are reported as an overflow instead of being silently truncated.

## Notes

- The computation time grows quickly with the exponent, because `power` is built from `product`, which is built from `sum`, and all of them are evaluated by counting up one unit at a time (as the primitive recursive definition requires).
- This implementation favours fidelity to the formal definition over performance.
