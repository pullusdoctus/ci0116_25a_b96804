#include "pathfinder.hpp"
#include "files.hpp"
#include <iostream>
#include <vector>

#define INPUT_DIR "input"

void prompt(Pathfinder& pf);
void printOptions();

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
    std::cout << "Loading, please wait..." << std::endl;
    csv = openCSV(std::string(INPUT_DIR) + '/' + filename);
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  std::vector<std::vector<int>> matrix;
  std::vector<std::string> cities;
  csvToMatrix(csv, matrix, cities);

  Pathfinder pf = Pathfinder(cities, matrix);
  pf.floydWarshall();

  prompt(pf);

  return 0;
}

void prompt(Pathfinder& pf) {
  std::cout << "== Requests ==" << std::endl;
  std::cout << "Choose an option:" << std::endl;
  while (true) {
    printOptions();
    int choice = 0;
    std::cin >> choice;
    switch (choice) {
      case 0:
        return;
      case 1:
        pf.printHub();
        break;
      case 2:
        pf.promptFindHelpToCity();
        break;
      case 3:
        pf.printMostDistantPair();
        break;
      case 4:
        pf.printClosestPair();
        break;
      case 5:
        pf.printByAverage();
        break;
      default:
        std::cerr << "Invalid option. Make sure your input is an integer"
          " between 0 and 5, inclusive" << std::endl;
        break;
    }
  }
}

void printOptions() {
  std::cout << "0. Exit" << std::endl;
  std::cout << "1. Find Hub City" << std::endl;
  std::cout << "2. Find Helper City" << std::endl;
  std::cout << "3. Find Most Distant Pair" << std::endl;
  std::cout << "4. Find Closest Pair" << std::endl;
  std::cout << "5. List Cities by Average Distance" << std::endl;
}
