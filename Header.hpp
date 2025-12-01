/*
File Name: Header.hpp
Created: 11/19/2025
Purpose: Include this Header for Libraries
*/

#pragma once // Prevent redefinition and CRT

#include <SFML/Graphics.hpp>

#include <string> // Strings, length/size, ==, etc.

#include <iostream> // In/Output Stream Library (cin/cout/cerr)
#include <fstream> // ifstream/ofstream or Input/Output file operations
#include <sstream> // Enables treating strings as in/out files reading and writing strings

#include <stack> // Allows insertion and removal from one end of a stack
#include <ctime> // Time Library, allows for taking system time (rand gen uses)
#include <vector> // Dynamic array that resizes self when elements added/removed
#include <cstdlib> // Key library for rand, memory, string conversion, process control, etc.
#include <cassert> // Assert, used for error handling. Evals if expression is false, prints.
#include <cmath> // Trig, Power, Expo, Rounding, etc.

extern sf::Clock globalClock; // global clock

using std::cout;
using std::cin;
using std::endl;
using std::ostream;
using std::ifstream;
using std::fstream;
using std::ofstream;
