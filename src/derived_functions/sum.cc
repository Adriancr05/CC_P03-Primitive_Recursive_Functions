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

unsigned Sum::evaluate(const std::vector<unsigned>&) const {
  return 0;
}

// sum(x, 0) = P1(x);  sum(x, y+1) = S(P3(x, y, sum(x, y)))
const PrimitiveRecursiveFunction* make_sum() {
  const PrimitiveRecursiveFunction* base = new Projection(1);
  const PrimitiveRecursiveFunction* step = new Composition(
    new Successor(),
    std::vector<const PrimitiveRecursiveFunction*>{new Projection(3)}
  );
  return new Recursion(base, step);
}
