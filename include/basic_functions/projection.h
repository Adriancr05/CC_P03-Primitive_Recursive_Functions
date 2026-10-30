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

#ifndef PROJECTION_H
#define PROJECTION_H

#include <stdexcept>

#include "../primitive_recursive_function.h"

// Projection function: P^n_i(x_1..x_n) = x_i
class Projection : public PrimitiveRecursiveFunction {
 public:
  explicit Projection(size_t index) : index_(index) {}
 private:
  size_t index_;
  unsigned long long evaluate(const std::vector<unsigned long long>&) const override;
};

#endif  // PROJECTION_H
