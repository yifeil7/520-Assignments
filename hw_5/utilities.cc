// utilities.cc
#include "utilities.h"
#include <algorithm> // For std::sort
#include <cmath>     // For std::abs
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept> // For std::runtime_error
#include <cctype>


void sort_by_magnitude(std::vector<double>& vec) {
    std::sort(vec.begin(), vec.end(), [](double x, double y) {
        return std::abs(x) < std::abs(y);
    });
}

TypedArray<TypedArray<double>> read_matrix_csv(const std::string& path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    TypedArray<TypedArray<double>> matrix;
    std::string line;
    size_t rowNum = 0;
    size_t expectedColumns = 0;

    while (getline(file, line)) {
        std::istringstream lineStream(line);
        std::string cell;
        TypedArray<double> row;
        size_t columnNum = 0;

        while (getline(lineStream, cell, ',')) {
            // Trim spaces and tabs from the cell
            cell.erase(0, cell.find_first_not_of(" \t"));
            cell.erase(cell.find_last_not_of(" \t") + 1);
            
            // Convert cell to double and add to the current row
            try {
                double value = std::stod(cell);
                row.set(columnNum, value);
                columnNum++;
            } catch (const std::invalid_argument& e) {
                throw std::runtime_error("Invalid number format");
            }
        }

        if (rowNum == 0) {
            expectedColumns = columnNum;
        } else if (columnNum != expectedColumns) {
            throw std::runtime_error("Inconsistent number of columns");
        }

        matrix.set(rowNum, row);
        rowNum++;
    }

    if (file.bad()) {
        throw std::runtime_error("Error while reading file");
    }

    return matrix;
}

void write_matrix_csv(const TypedArray<TypedArray<double>>& matrix, const std::string& path) {
    std::ofstream file(path);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file for writing");
    }

    for (int i = 0; i < matrix.size(); ++i) {
        for (int j = 0; j < matrix.safe_get(i).size(); ++j) {
            file << matrix.safe_get(i).safe_get(j);
            if (j < matrix.safe_get(i).size() - 1) {
                file << ",";
            }
        }
        file << "\n";
    }
}


std::map<std::string, int> occurrence_map(const std::string& path) {
    std::map<std::string, int> wordCount;
    std::ifstream file(path);
    std::string word;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << path << std::endl;
        return wordCount;
    }

    while (file >> word) {
        std::string processedWord;
        bool isValidWord = true;

        // Remove special characters from the start and end of the word
        size_t start = 0, end = word.length() - 1;
        while(start <= end && !(std::isalnum(word[start]) || word[start] == '\'')) ++start;
        while(end >= start && !(std::isalnum(word[end]) || word[end] == '\'')) --end;

        // Process only the valid part of the word
        for (size_t i = start; i <= end; ++i) {
            char c = word[i];
            if (std::isalnum(c) || c == '\'') {
                processedWord += std::tolower(c);
            } else {
                // If the word contains any invalid character, mark it as invalid and break the loop
                isValidWord = false;
                break;
            }
        }

        // Only add the word to the map if it's valid
        if (isValidWord && !processedWord.empty()) {
            wordCount[processedWord]++;
        }
    }

    file.close();
    return wordCount;
}