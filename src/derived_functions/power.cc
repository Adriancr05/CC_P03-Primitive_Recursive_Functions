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

#include "../../include/derived_functions/power.h"

unsigned Power::evaluate(const std::vector<unsigned>&) const {
  return 0;
}

// power(x, 0) = S(Z(x));  power(x, y+1) = product(P1(x, y, r), P3(x, y, r))
const PrimitiveRecursiveFunction* make_power() {
  const PrimitiveRecursiveFunction* base = new Composition(
    new Successor(),
    std::vector<const PrimitiveRecursiveFunction*>{new Zero()}
  );
  const PrimitiveRecursiveFunction* step = new Composition(
    make_product(),
    std::vector<const PrimitiveRecursiveFunction*>{new Projection(1),
    new Projection(3)}
  );
  return new Recursion(base, step);
}
