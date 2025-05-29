#!/bin/bash

# Ordner anlegen
mkdir -p cpp/algorithms
mkdir -p cpp/data_structures
mkdir -p cpp/system
mkdir -p python/scripts
mkdir -p c/system
mkdir -p opencl
mkdir -p headers
mkdir -p misc

# C++ Algorithmen
mv merge_sort*.cpp selection_sort.cpp heron.cpp rational.cpp eratosthenes.cpp is_prime.cpp count_lines_in_file.cpp 12-1.cpp cpp/algorithms/ 2>/dev/null

# C++ Datenstrukturen
mv binary_search_tree.cpp hash_table.cpp graph.cpp stack.cpp DLL.cpp double_linked_list.hpp resizable_array.hpp heap.hpp PQ.hpp cpp/data_structures/ 2>/dev/null

# C++ Systemnahe Dinge
mv memory_allocator.c search_string_parallel.cpp terminal.c cpp/system/ 2>/dev/null

# Python-Skripte
mv DigitalClock.py Calculator.py OneTimePad.py FileOrginaizer.py RockPapierScissors.py web_scrapper.py ZahlenKoverter.py from_python_toC_assembly.py python/scripts/ 2>/dev/null

# C Dateien
mv for_parallel_omp.c hello_parallel.c converter.c c/system/ 2>/dev/null

# OpenCL
mv openCL_*.cpp ocl_3_in_2_ou.cpp opencl/ 2>/dev/null

# Header-Dateien
mv myFunction.h *.hpp headers/ 2>/dev/null

# Einzelne Sonstige
mv OTP.cpp Student.cpp momen.cpp misc/ 2>/dev/null

