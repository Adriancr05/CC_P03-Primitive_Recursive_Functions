# Universidad de La Laguna
# Escuela Superior de Ingeniería y Tecnología
# Degree in Computer Engineering
# Computational Complexity
# Assignment 2 - Turing Machine
#
# @author Adrián Castro Rodríguez
# @since Oct 30 2026
# @desc Makefile

TARGET = power

IDIR = include
LDIR = lib
SDIR = src
BDIR = build

CXX = g++
CXXFLAGS = -I$(IDIR) -I$(LDIR) -std=c++20 -Wall -g # -fsanitize=address

SOURCES = $(shell find $(SDIR) -name "*.cc")

OBJ = $(patsubst $(SDIR)/%.cc, $(BDIR)/%.o, $(SOURCES))

all: $(TARGET)

$(BDIR)/%.o: $(SDIR)/%.cc
	@mkdir -p $(dir $@)
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY: clean
clean:
	rm -rf $(BDIR) $(TARGET)