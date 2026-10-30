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

// Displays the program usage instructions and available parameters.
void show_help() {
  std::cout << "./power -x <n> -y <n>" << std::endl;
}

// Parses a non-negative integer, rejecting signs, trailing garbage and values above max.
unsigned long long parse_unsigned(const std::string& value) {
  if (value[0] == '-') {
    throw std::invalid_argument("Error: negative values are not allowed");
  }
  size_t pos = 0;
  unsigned long long temp = 0;
  try {
    temp = std::stoull(value, &pos);
  } catch (const std::invalid_argument&) {
    throw std::invalid_argument("Error: '" + value + "' is not a number");
  } catch (const std::out_of_range&) {
    throw std::out_of_range("Error: the value '" + value + "' is too large");
  }
  if (pos != value.size()) {
    throw std::invalid_argument("Error: leftover characters in '" + value + "'");
  }
  return temp;
}

// Parses command-line arguments and returns an args structure with the options.
args parse_args(int argc, char* argv[]) {
  args options;
  if (argc == 2) {
    std::string option = std::string(argv[1]);
    if (option == "--help" || option == "-h") {
      options.show_help = true;
      return options;
    }
  }
  if (argc != 5) {
    throw std::invalid_argument("Incorrect number of parameters. Use --help for more information.");
  }
  for (int i = 1; i < argc; i++) {
    std::string option = argv[i];
    if (i + 1 >= argc) throw std::invalid_argument("Missing value for " + option);
    std::string value = argv[++i];
    if (option == "-x") options.x = parse_unsigned(value);
    else if (option == "-y") options.y = parse_unsigned(value);
    else throw std::invalid_argument("Unknown parameter: " + option);
  }
  return options;
}

// Builds the power function, evaluates it and prints the result and the number of calls.
void execute_power(const args& options) {
  Power power;
  PrimitiveRecursiveFunction::reset_calls();
  unsigned long long result = power({options.x, options.y});
  std::cout << "Result: " << result << std::endl;
  std::cout << "Function calls: " << PrimitiveRecursiveFunction::calls() << std::endl;
}
