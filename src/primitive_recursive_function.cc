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

unsigned PrimitiveRecursiveFunction::operator()(const std::vector<unsigned>& arguments) const {
  calls_++;
  return Evaluate(arguments);
}

unsigned Zero::Evaluate(const std::vector<unsigned>&) const {
  return 0;
}

unsigned Successor::Evaluate(const std::vector<unsigned>& arguments) const {
  if (arguments.size() != 1) throw std::invalid_argument("Successor expects 1 argument");
  if (arguments[0] == std::numeric_limits<unsigned>::max()) {
    throw std::overflow_error("Error: the result does not fit in a 64-bit unsigned number");
  }
  return arguments[0] + 1;
}

unsigned Projection::Evaluate(const std::vector<unsigned>& arguments) const {
  if (index_ == 0 || index_ > arguments.size()) {
    throw std::invalid_argument("Projection index out of range");
  }
  return arguments[index_ - 1];
}

Composition::~Composition() {
  delete outer_;
  for (const PrimitiveRecursiveFunction* function : inner_) delete function;
}

unsigned Composition::Evaluate(const std::vector<unsigned>& arguments) const {
  std::vector<unsigned> values;
  values.reserve(inner_.size());
  for (const PrimitiveRecursiveFunction* function : inner_) values.push_back((*function)(arguments));
  return (*outer_)(values);
}

Recursion::~Recursion() {
  delete base_;
  delete step_;
}

// Evaluated iteratively to avoid stack overflow with large exponents. Each unfolded
// step f(x, k+1) is still counted as a call, so the count matches the recursive definition.
unsigned Recursion::Evaluate(const std::vector<unsigned>& arguments) const {
  if (arguments.empty()) throw std::invalid_argument("Recursion expects at least 1 argument");
  std::vector<unsigned> params(arguments.begin(), arguments.end() - 1);
  const unsigned y = arguments.back();
  unsigned accumulator = (*base_)(params);
  for (unsigned k = 0; k < y; ++k) {
    AddCalls(1);
    std::vector<unsigned> step_arguments = params;
    step_arguments.push_back(k);
    step_arguments.push_back(accumulator);
    accumulator = (*step_)(step_arguments);
  }
  return accumulator;
}

// sum(x, 0) = P1(x);  sum(x, y+1) = S(P3(x, y, sum(x, y)))
const PrimitiveRecursiveFunction* MakeSum() {
  const PrimitiveRecursiveFunction* base = new Projection(1);
  const PrimitiveRecursiveFunction* step = new Composition(
    new Successor(),
    std::vector<const PrimitiveRecursiveFunction*>{new Projection(3)}
  );
  return new Recursion(base, step);
}

// product(x, 0) = Z(x);  product(x, y+1) = sum(P1(x, y, r), P3(x, y, r))
const PrimitiveRecursiveFunction* MakeProduct() {
  const PrimitiveRecursiveFunction* base = new Zero();
  const PrimitiveRecursiveFunction* step = new Composition(
    MakeSum(),
    std::vector<const PrimitiveRecursiveFunction*>{new Projection(1),
    new Projection(3)}
  );
  return new Recursion(base, step);
}

// power(x, 0) = S(Z(x));  power(x, y+1) = product(P1(x, y, r), P3(x, y, r))
const PrimitiveRecursiveFunction* MakePower() {
  const PrimitiveRecursiveFunction* base = new Composition(
    new Successor(),
    std::vector<const PrimitiveRecursiveFunction*>{new Zero()}
  );
  const PrimitiveRecursiveFunction* step = new Composition(
    MakeProduct(),
    std::vector<const PrimitiveRecursiveFunction*>{new Projection(1),
    new Projection(3)}
  );
  return new Recursion(base, step);
}
