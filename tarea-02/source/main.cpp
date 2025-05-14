#include <iostream>

void printMenu() {
  std::cout << "Choose a data structure to test:" << std::endl;
  std::cout << "\t1. Singly Linked List" << std::endl;
  std::cout << "\t2. Binary Search Tree" << std::endl;
  std::cout << "\t3. Red and Black Tree" << std::endl;
  std::cout << "\t4. Chained Hash Table" << std::endl;
  std::cout << "\nPress '0' to exit" << std::endl;
}

void printExit() {
  std::cout << "Cleaning everything up and closing the program..."
    << std::endl;
  std::cout << "Goodbye!" << std::endl;
}

int main() {
  std::cout << "Welcome!" << std::endl;
  int choice = -1;
  while (choice != 0) {
    printMenu();
    if (!(std::cin >> choice)) {
      std::cin.clear();
      char c;
      while ((c = std::cin.get()) != '\n' && c != EOF);
      std::cout << "Invalid input. Please enter a number." << std::endl;
      choice = -1;
      continue;
    }
    char c;
    while ((c = std::cin.get()) != '\n' && c != EOF);
    switch (choice) {
      case 1:
        // TODO:
        std::cout << "SLL" << std::endl;
        break;
      case 2:
        // TODO:
        std::cout << "BST" << std::endl;
        break;
      case 3:
        // TODO:
        std::cout << "RBT" << std::endl;
        break;
      case 4:
        // TODO:
        std::cout << "CHT" << std::endl;
        break;
      case 0:
        printExit();
        break;
      default:
        std::cout << "Please make sure to choose a valid option (0 to 4)"
          << std::endl;
        break;
    }
  }
}
