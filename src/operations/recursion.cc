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

#include "../../include/operations/recursion.h"

// Destructor: frees the base and step functions
Recursion::~Recursion() {
  delete base_;
  delete step_;
}

// Primitive recursion:
//   f(x, 0) = g(x)
//   f(x, y + 1) = h(x, y, f(x, y))
unsigned long long Recursion::evaluate(const std::vector<unsigned long long>& arguments) const {
  if (arguments.empty()) throw std::invalid_argument("Recursion expects at least 1 argument");
  std::vector<unsigned long long> params(arguments.begin(), arguments.end() - 1);
  const unsigned long long y = arguments.back();
  unsigned long long accumulator = (*base_)(params);
  for (unsigned long long i = 0; i < y; ++i) {
    std::vector<unsigned long long> step_arguments = params;
    step_arguments.push_back(i);
    step_arguments.push_back(accumulator);
    accumulator = (*step_)(step_arguments);
  }
  return accumulator;
}
