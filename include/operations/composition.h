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

#ifndef COMPOSITION_H
#define COMPOSITION_H

#include "../primitive_recursive_function.h"

// Combination + composition: f(g_1(x), ..., g_n(x)).
class Composition : public PrimitiveRecursiveFunction {
 public:
  Composition(const PrimitiveRecursiveFunction* outer, std::vector<const
    PrimitiveRecursiveFunction*> inner) : outer_(outer), inner_(std::move(inner)) {}
  ~Composition() override;
  Composition(const Composition&) = delete;
  Composition& operator=(const Composition&) = delete;
 private:
  const PrimitiveRecursiveFunction* outer_;
  std::vector<const PrimitiveRecursiveFunction*> inner_;
  bool counts_as_call() const override { return false; }
  unsigned evaluate(const std::vector<unsigned>&) const override;
};

#endif  // COMPOSITION_H
