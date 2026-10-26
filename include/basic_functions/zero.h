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

#ifndef ZERO_H
#define ZERO_H

#include "../primitive_recursive_function.h"

// Zero function: Z(x) = 0
class Zero : public PrimitiveRecursiveFunction {
 private:
  unsigned evaluate(const std::vector<unsigned>&) const override;
};

#endif  // ZERO_H
