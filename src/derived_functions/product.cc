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

#include "../../include/derived_functions/product.h"

unsigned Product::evaluate(const std::vector<unsigned>&) const {
  return 0;
}

// product(x, 0) = Z(x);  product(x, y+1) = sum(P1(x, y, r), P3(x, y, r))
const PrimitiveRecursiveFunction* make_product() {
  const PrimitiveRecursiveFunction* base = new Zero();
  const PrimitiveRecursiveFunction* step = new Composition(
    make_sum(),
    std::vector<const PrimitiveRecursiveFunction*>{new Projection(1),
    new Projection(3)}
  );
  return new Recursion(base, step);
}
