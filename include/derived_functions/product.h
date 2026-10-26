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

#ifndef PRODUCT_H
#define PRODUCT_H

#include "sum.h"

// Product function: product(x, y) = x * y
class Product : public PrimitiveRecursiveFunction {
 private:
  unsigned evaluate(const std::vector<unsigned>&) const override;
};

#endif  // PRODUCT_H
