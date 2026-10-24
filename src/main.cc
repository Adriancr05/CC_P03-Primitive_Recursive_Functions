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

#include "../include/tools.h"

int main(int argc, char* argv[]) {
  try {
    args options = parse_args(argc, argv);
    if (options.show_help) { show_help(); return 0; }
    execute_power(options);
    return 0;
  } catch (const std::exception& exception) {
    std::cerr << exception.what() << std::endl;
    return 1;
  }
}
