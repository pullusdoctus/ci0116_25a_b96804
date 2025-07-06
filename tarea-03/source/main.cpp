#include "pathfinder.hpp"
#include "files.hpp"
#include <iostream>

#define INPUT_DIR "input"

void printMatrix(const std::vector<std::vector<int>>& matrix);

int main() {
  std::cout << "=== List of CSV files in input directory ===" << std::endl;
  std::vector<std::string> filenames = parseDir(INPUT_DIR);
  if (filenames.empty()) {
    std::cerr << "No files found in input directory";
    return 1;
  }
  for (const std::string& name : filenames) {
    std::cout << " - " << name << std::endl;
  }

  std::cout << "Enter filename to load (must be inside input directory): ";
  std::string filename;
  std::cin >> filename;

  std::ifstream csv;
  try {
    csv = openCSV(std::string(INPUT_DIR) + '/' + filename);
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  std::vector<std::vector<int>> matrix;
  csvToMatrix(csv, matrix);
  std::cout << "== Matrix data ==" << std::endl;
  printMatrix(matrix);

  Pathfinder pf = Pathfinder(filenames, matrix);
  std::cout << "\nAdjacency Matrix before Floyd-Warshall:" << std::endl;
  printMatrix(pf.getDistances());
  std::cout << "\nParents' Matrix before Floyd-Warshall:" << std::endl;
  printMatrix(pf.getParents());

  pf.floydWarshall();
  std::cout << "\nAdjacency Matrix after Floyd-Warshall:" << std::endl;
  printMatrix(pf.getDistances());
  std::cout << "\nParents' Matrix after Floyd-Warshall:" << std::endl;
  printMatrix(pf.getParents());

  return 0;
}

void printMatrix(const std::vector<std::vector<int>>& matrix) {
  int n = matrix.size();
  std::cout << "Matrix (" << n << "x" << n << "):" << std::endl;
  for (const auto& row : matrix) {
    for (int value : row) {
      std::cout << "[ ";
      if (value == -1) std::cout << "∞";
      else std::cout << value;
      std::cout << " ]\t";
    }
    std::cout << std::endl;
  }
}
