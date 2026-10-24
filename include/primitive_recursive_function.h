/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Degree in Computer Engineering
 * Computational Complexity
 * Assignment 3 - Primitive Recursive Functions
 *
 * @author Adrián Castro Rodríguez
 * @since Oct 30 2026
 */

#ifndef PRIMITIVE_RECURSIVE_FUNCTION_H
#define PRIMITIVE_RECURSIVE_FUNCTION_H

#include <vector>
#include <limits>
#include <stdexcept>

// Base class of every (basic or derived) primitive recursive function.
class PrimitiveRecursiveFunction {
 public:
  virtual ~PrimitiveRecursiveFunction() = default;

  // Evaluates the function and counts the call.
  unsigned operator()(const std::vector<unsigned>& arguments) const;

  static unsigned long long calls() { return calls_; }
  static void reset_calls() { calls_ = 0; }

 protected:
  virtual unsigned evaluate(const std::vector<unsigned>& arguments) const = 0;
  static void add_calls(unsigned long long amount) { calls_ += amount; }

 private:
  static inline unsigned long long calls_ = 0;
};

// Basic function: Z(x1..xn) = 0
class Zero : public PrimitiveRecursiveFunction {
 protected:
  unsigned evaluate(const std::vector<unsigned>& arguments) const override;
};

// Basic function: S(x) = x + 1
class Successor : public PrimitiveRecursiveFunction {
 protected:
  unsigned evaluate(const std::vector<unsigned>& arguments) const override;
};

// Basic function: P_i(x1..xn) = xi (index is 1-based)
class Projection : public PrimitiveRecursiveFunction {
 public:
  explicit Projection(size_t index) : index_(index) {}
 protected:
  unsigned evaluate(const std::vector<unsigned>& arguments) const override;
 private:
  size_t index_;
};

// Combination + composition: f(g1(x), ..., gm(x)).
// Takes ownership of 'outer' and of every function in 'inner'.
class Composition : public PrimitiveRecursiveFunction {
 public:
  Composition(const PrimitiveRecursiveFunction* outer, std::vector<const PrimitiveRecursiveFunction*> inner)
      : outer_(outer), inner_(std::move(inner)) {}
  ~Composition() override;
  Composition(const Composition&) = delete;
  Composition& operator=(const Composition&) = delete;
 protected:
  unsigned evaluate(const std::vector<unsigned>& arguments) const override;
 private:
  const PrimitiveRecursiveFunction* outer_;
  std::vector<const PrimitiveRecursiveFunction*> inner_;
};

// Primitive recursion on the last argument:
//   f(x, 0)   = base(x)
//   f(x, y+1) = step(x, y, f(x, y))
// Takes ownership of 'base' and 'step'.
class Recursion : public PrimitiveRecursiveFunction {
 public:
  Recursion(const PrimitiveRecursiveFunction* base, const PrimitiveRecursiveFunction* step) : base_(base), step_(step) {}
  ~Recursion() override;
  Recursion(const Recursion&) = delete;
  Recursion& operator=(const Recursion&) = delete;
 protected:
  unsigned evaluate(const std::vector<unsigned>& arguments) const override;
 private:
  const PrimitiveRecursiveFunction* base_;
  const PrimitiveRecursiveFunction* step_;
};

// Derived functions built only from the pieces above.
// The caller owns the returned pointer and must delete it.
const PrimitiveRecursiveFunction* MakeSum();      // sum(x, y)
const PrimitiveRecursiveFunction* MakeProduct();  // product(x, y)
const PrimitiveRecursiveFunction* MakePower();    // power(x, y) = x^y

#endif  // PRIMITIVE_RECURSIVE_FUNCTION_H
