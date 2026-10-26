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

#include "../../include/basic_functions/projection.h"

unsigned Projection::evaluate(const std::vector<unsigned>& arguments) const {
  if (index_ == 0 || index_ > arguments.size()) {
    throw std::invalid_argument("Projection index out of range");
  }
  return arguments[index_ - 1];
}
