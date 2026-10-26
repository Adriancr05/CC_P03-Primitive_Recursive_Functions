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

#ifndef RECURSION_H
#define RECURSION_H

#include "../primitive_recursive_function.h"

// Primitive recursion on the last argument:
//   f(x, 0)   = base(x)
//   f(x, y+1) = step(x, y, f(x, y))
// Takes ownership of 'base' and 'step'.
class Recursion : public PrimitiveRecursiveFunction {
 public:
  Recursion(const PrimitiveRecursiveFunction* base, const
    PrimitiveRecursiveFunction* step) : base_(base), step_(step) {}
  ~Recursion() override;
  Recursion(const Recursion&) = delete;
  Recursion& operator=(const Recursion&) = delete;
 private:
  const PrimitiveRecursiveFunction* base_;
  const PrimitiveRecursiveFunction* step_;
  unsigned evaluate(const std::vector<unsigned>& arguments) const override;
};

#endif  // RECURSION_H
