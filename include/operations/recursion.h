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

// Primitive recursion operator: builds f from base and step functions
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
  unsigned evaluate(const std::vector<unsigned>&) const override;
};

#endif  // RECURSION_H
