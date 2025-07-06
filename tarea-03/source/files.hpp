#pragma once

#include <fstream>
#include <string>
#include <vector>

/// Parses a directory and returns a directory with the filenames of all files
/// within
std::vector<std::string> parseDir(const std::string& dir);

/// Opens a CSV file and returns an input file stream
std::ifstream openCSV(const std::string& filename);

/// Reads a CSV file and converts its data into an adjacency matrix
/// Also stores the city names in an array
void csvToMatrix(std::ifstream& file, std::vector<std::vector<int>>& matrix,
                 std::vector<std::string>& cities, int defaultValue = -1);
