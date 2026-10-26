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

// power: ℕ × ℕ → ℕ
// power(x, 0) = S(Z(x))
// power(x, y+1) = h(x, y, power(x, y)) = product(P^3_1(x, y, power(x, y)), P^3_3(x, y, power(x, y)))
unsigned Power::evaluate(const std::vector<unsigned>& arguments) const {
  const PrimitiveRecursiveFunction* base = new Composition(
    new Successor(),
    std::vector<const PrimitiveRecursiveFunction*>{new Zero()}
  );
  const PrimitiveRecursiveFunction* step = new Composition(
    new Product(),
    std::vector<const PrimitiveRecursiveFunction*>{
      new Projection(1),
      new Projection(3)
    }
  );
  const PrimitiveRecursiveFunction* power =  new Recursion(base, step);
  return (*power)(arguments);
}
