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

#include "../../include/basic_functions/successor.h"

// S: ℕ → ℕ
// S(x) = x + 1
unsigned Successor::evaluate(const std::vector<unsigned>& arguments) const {
  if (arguments.size() != 1) throw std::invalid_argument("Successor expects 1 argument");
  if (arguments[0] == std::numeric_limits<unsigned>::max()) {
    throw std::overflow_error("Error: the result does not fit in a 64-bit unsigned number");
  }
  return arguments[0] + 1;
}
