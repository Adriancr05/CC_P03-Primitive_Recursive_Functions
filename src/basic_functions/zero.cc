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

#include "../../include/basic_functions/zero.h"

// Z: ℕ → ℕ
// Z(x) = 0
unsigned long long Zero::evaluate(const std::vector<unsigned long long>&) const {
  return 0;
}
