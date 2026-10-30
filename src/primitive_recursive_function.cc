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

#include "../include/primitive_recursive_function.h"

// Evaluates the function and counts the call.
unsigned long long PrimitiveRecursiveFunction::operator()(const std::vector<unsigned long long>& arguments) const {
  if (counts_as_call()) calls_++;
  return evaluate(arguments);
}
