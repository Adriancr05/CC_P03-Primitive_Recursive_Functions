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

// product: ℕ × ℕ → ℕ
// product(x, 0) = g(x) = Z(x)
// product(x, y + 1) = h(x, y, product(x, y)) = sum(P^3_1(x, y, product(x, y)), P^3_3(x, y, product(x, y)))
unsigned Product::evaluate(const std::vector<unsigned>& arguments) const {
  const PrimitiveRecursiveFunction* base = new Zero();
  const PrimitiveRecursiveFunction* step = new Composition(
    new Sum(),
    std::vector<const PrimitiveRecursiveFunction*>{
      new Projection(1),
      new Projection(3)
    }
  );
  const PrimitiveRecursiveFunction* product = new Recursion(base, step);
  return (*product)(arguments);
}
