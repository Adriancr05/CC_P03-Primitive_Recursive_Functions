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

#ifndef PRIMITIVE_RECURSIVE_FUNCTION_H
#define PRIMITIVE_RECURSIVE_FUNCTION_H

#include <vector>

// Base class of every primitive recursive function.
class PrimitiveRecursiveFunction {
 public:
  virtual ~PrimitiveRecursiveFunction() = default;
  unsigned operator()(const std::vector<unsigned>&) const;
  static unsigned long long calls() { return calls_; }
  static void reset_calls() { calls_ = 0; }
 protected:
  static void add_calls(unsigned long long amount) { calls_ += amount; }
 private:
  static inline unsigned long long calls_ = 0;
  virtual unsigned evaluate(const std::vector<unsigned>&) const = 0;
};

#endif  // PRIMITIVE_RECURSIVE_FUNCTION_H
