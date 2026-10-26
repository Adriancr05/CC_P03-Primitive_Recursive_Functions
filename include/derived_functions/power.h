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

#ifndef POWER_H
#define POWER_H

#include "../operations.h"
#include "../basic_functions.h"
#include "../primitive_recursive_function.h"

// Basic function: Z(x) = 0
class Power : public PrimitiveRecursiveFunction {
 private:
  unsigned evaluate(const std::vector<unsigned>& arguments) const override;
};

#endif  // POWER_H
