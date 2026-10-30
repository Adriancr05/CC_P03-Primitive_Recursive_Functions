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
  unsigned long long operator()(const std::vector<unsigned long long>&) const;
  static unsigned long long calls() { return calls_; }
  static void reset_calls() { calls_ = 0; }
 protected:
  static void add_calls(unsigned long long amount) { calls_ += amount; }
 private:
  static inline unsigned long long calls_ = 0;
  virtual bool counts_as_call() const { return true; }
  virtual unsigned long long evaluate(const std::vector<unsigned long long>&) const = 0;
};

#endif  // PRIMITIVE_RECURSIVE_FUNCTION_H
