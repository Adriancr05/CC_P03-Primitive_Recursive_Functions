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

#ifndef TOOLS_H
#define TOOLS_H

#include <string>
#include <limits>
#include <iostream>
#include <stdexcept>

#include "../include/derived_functions/power.h"

// Stores command-line arguments including file paths.
struct args {
  unsigned long long x = 0;
  unsigned long long y = 0;
  bool show_help = false;
};

void show_help();
void execute_power(const args&);
args parse_args(int, char*[]);

#endif  // TOOLS_H
