# MenuLib

A simple C++ menu library created as part of an Object-Oriented Programming project.

## About the project

The library provides functionality to create a simple multi-page menu with toggles, sliders and menu options which execute user-defined functions when selected.

## Docs

Docs are available to build locally using doxygen or deployed online at 

https://mikor01.github.io/MenuLib/index.html

## Prerequisites

- C++17 compatible compiler
- Git
- CMake (version >= 3.10)
- doxygen (optional, needed to generate documentation)

## Installation and usage example

Clone the repository:
```bash
git clone https://github.com/Mikor01/MenuLib.git
cd MenuLib
```
(Optional) Build the docs:
```bash
doxygen ./Doxyfile
```
Create build folder and initialize:
```bash
mkdir build
cd build
cmake ..
```
Build the library and run provided example app (inside the build directory):
```bash
cmake --build . 
cd src
./MenuApp
```
