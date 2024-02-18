// utilities.h
#ifndef UTILITIES_H
#define UTILITIES_H

#include <vector>
#include <string>
#include "typed_array.h"  // Include the TypedArray definition

#include <map>

std::map<std::string, int> occurrence_map(const std::string& path);

TypedArray<TypedArray<double>> read_matrix_csv(const std::string& path);

void write_matrix_csv(const TypedArray<TypedArray<double>>& matrix, const std::string& path);

void sort_by_magnitude(std::vector<double>& vec);

#endif // UTILITIES_H
