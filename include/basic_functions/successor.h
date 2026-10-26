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

#ifndef SUCCESSOR_H
#define SUCCESSOR_H

#include <limits>
#include <stdexcept>

#include "../primitive_recursive_function.h"

// Basic function: S(x) = x + 1
class Successor : public PrimitiveRecursiveFunction {
 private:
  unsigned evaluate(const std::vector<unsigned>& arguments) const override;
};

#endif  // SUCCESSOR_H
