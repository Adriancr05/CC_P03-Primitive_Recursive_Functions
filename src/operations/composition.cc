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

#include "../../include/operations/composition.h"

// Destructor: frees the outer function and all inner functions
Composition::~Composition() {
  delete outer_;
  for (const PrimitiveRecursiveFunction* function : inner_) delete function;
}

// Combination + composition: f(g_1(x), ..., g_n(x)).
unsigned long long Composition::evaluate(const std::vector<unsigned long long>& arguments) const {
  std::vector<unsigned long long> values;
  values.reserve(inner_.size());
  for (const PrimitiveRecursiveFunction* function : inner_) values.push_back((*function)(arguments));
  return (*outer_)(values);
}
