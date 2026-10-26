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

#include "../../include/derived_functions/sum.h"

// sum: ℕ × ℕ → ℕ
// sum(x, 0) = g(x) = P^1_1(x)
// sum(x, y + 1) = h(x, y, sum(x, y)) = S(P^3_3(x, y, sum(x, y)))
unsigned Sum::evaluate(const std::vector<unsigned>& arguments) const {
  const PrimitiveRecursiveFunction* base = new Projection(1);
  const PrimitiveRecursiveFunction* step = new Composition(
    new Successor(),
    std::vector<const PrimitiveRecursiveFunction*>{new Projection(3)}
  );
  const PrimitiveRecursiveFunction* sum = new Recursion(base, step);
  return (*sum)(arguments);
}
