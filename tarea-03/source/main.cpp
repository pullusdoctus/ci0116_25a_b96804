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
  std::vector<std::string> cities;
  csvToMatrix(csv, matrix, cities);

  Pathfinder pf = Pathfinder(cities, matrix);
  std::cout << "\nBefore Floyd-Warshall:" << std::endl;
  pf.printDistances();
  pf.printParents();

  pf.floydWarshall();
  std::cout << "\nAfter Floyd-Warshall:" << std::endl;
  pf.printDistances();
  pf.printParents();

  return 0;
}
