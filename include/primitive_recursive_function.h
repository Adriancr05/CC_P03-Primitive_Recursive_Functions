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

#include <memory>
#include <vector>

using Natural = unsigned long long;
using Arguments = std::vector<Natural>;

// Base class of every (basic or derived) primitive recursive function.
class PrimitiveRecursiveFunction {
 public:
  virtual ~PrimitiveRecursiveFunction() = default;

  // Evaluates the function and counts the call.
  Natural operator()(const Arguments& arguments) const;

  static unsigned long long calls() { return calls_; }
  static void ResetCalls() { calls_ = 0; }

 protected:
  virtual Natural Evaluate(const Arguments& arguments) const = 0;
  static void AddCalls(unsigned long long amount) { calls_ += amount; }

 private:
  static inline unsigned long long calls_ = 0;
};

using FunctionPtr = std::shared_ptr<const PrimitiveRecursiveFunction>;

// Basic function: Z(x1..xn) = 0
class Zero : public PrimitiveRecursiveFunction {
 protected:
  Natural Evaluate(const Arguments& arguments) const override;
};

// Basic function: S(x) = x + 1
class Successor : public PrimitiveRecursiveFunction {
 protected:
  Natural Evaluate(const Arguments& arguments) const override;
};

// Basic function: P_i(x1..xn) = xi (index is 1-based)
class Projection : public PrimitiveRecursiveFunction {
 public:
  explicit Projection(size_t index) : index_(index) {}
 protected:
  Natural Evaluate(const Arguments& arguments) const override;
 private:
  size_t index_;
};

// Combination + composition: f(g1(x), ..., gm(x))
class Composition : public PrimitiveRecursiveFunction {
 public:
  Composition(FunctionPtr outer, std::vector<FunctionPtr> inner)
      : outer_(std::move(outer)), inner_(std::move(inner)) {}
 protected:
  Natural Evaluate(const Arguments& arguments) const override;
 private:
  FunctionPtr outer_;
  std::vector<FunctionPtr> inner_;
};

// Primitive recursion on the last argument:
//   f(x, 0)   = base(x)
//   f(x, y+1) = step(x, y, f(x, y))
class Recursion : public PrimitiveRecursiveFunction {
 public:
  Recursion(FunctionPtr base, FunctionPtr step)
      : base_(std::move(base)), step_(std::move(step)) {}
 protected:
  Natural Evaluate(const Arguments& arguments) const override;
 private:
  FunctionPtr base_;
  FunctionPtr step_;
};

// Derived functions built only from the pieces above.
FunctionPtr MakeSum();      // sum(x, y)
FunctionPtr MakeProduct();  // product(x, y)
FunctionPtr MakePower();    // potencia(x, y) = x^y

#endif  // PRIMITIVE_RECURSIVE_FUNCTION_H
