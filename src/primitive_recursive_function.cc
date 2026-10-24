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

#include <limits>
#include <stdexcept>

Natural PrimitiveRecursiveFunction::operator()(const Arguments& arguments) const {
  ++calls_;
  return Evaluate(arguments);
}

Natural Zero::Evaluate(const Arguments&) const {
  return 0;
}

Natural Successor::Evaluate(const Arguments& arguments) const {
  if (arguments.size() != 1) throw std::invalid_argument("Successor expects 1 argument");
  if (arguments[0] == std::numeric_limits<Natural>::max()) {
    throw std::overflow_error("Error: the result does not fit in a 64-bit natural number");
  }
  return arguments[0] + 1;
}

Natural Projection::Evaluate(const Arguments& arguments) const {
  if (index_ == 0 || index_ > arguments.size()) {
    throw std::invalid_argument("Projection index out of range");
  }
  return arguments[index_ - 1];
}

Natural Composition::Evaluate(const Arguments& arguments) const {
  Arguments values;
  values.reserve(inner_.size());
  for (const FunctionPtr& function : inner_) values.push_back((*function)(arguments));
  return (*outer_)(values);
}

// Evaluated iteratively to avoid stack overflow with large exponents. Each unfolded
// step f(x, k+1) is still counted as a call, so the count matches the recursive definition.
Natural Recursion::Evaluate(const Arguments& arguments) const {
  if (arguments.empty()) throw std::invalid_argument("Recursion expects at least 1 argument");
  Arguments params(arguments.begin(), arguments.end() - 1);
  const Natural y = arguments.back();
  Natural accumulator = (*base_)(params);
  for (Natural k = 0; k < y; ++k) {
    AddCalls(1);
    Arguments step_arguments = params;
    step_arguments.push_back(k);
    step_arguments.push_back(accumulator);
    accumulator = (*step_)(step_arguments);
  }
  return accumulator;
}

// sum(x, 0) = P1(x);  sum(x, y+1) = S(P3(x, y, sum(x, y)))
FunctionPtr MakeSum() {
  auto successor = std::make_shared<Successor>();
  auto base = std::make_shared<Projection>(1);
  auto step = std::make_shared<Composition>(
      successor, std::vector<FunctionPtr>{std::make_shared<Projection>(3)});
  return std::make_shared<Recursion>(base, step);
}

// product(x, 0) = Z(x);  product(x, y+1) = sum(P1(x, y, r), P3(x, y, r))
FunctionPtr MakeProduct() {
  auto base = std::make_shared<Zero>();
  auto step = std::make_shared<Composition>(
      MakeSum(), std::vector<FunctionPtr>{std::make_shared<Projection>(1),
                                          std::make_shared<Projection>(3)});
  return std::make_shared<Recursion>(base, step);
}

// potencia(x, 0) = S(Z(x));  potencia(x, y+1) = product(P1(x, y, r), P3(x, y, r))
FunctionPtr MakePower() {
  auto base = std::make_shared<Composition>(
      std::make_shared<Successor>(),
      std::vector<FunctionPtr>{std::make_shared<Zero>()});
  auto step = std::make_shared<Composition>(
      MakeProduct(), std::vector<FunctionPtr>{std::make_shared<Projection>(1),
                                              std::make_shared<Projection>(3)});
  return std::make_shared<Recursion>(base, step);
}
