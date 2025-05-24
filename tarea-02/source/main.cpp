#include <ctime>
#include <iostream>
#include <random>

#include <BinarySearchTree.hpp>
#include <SinglyLinkedList.hpp>
#include <Timer.hpp>

void printMenu() {
  std::cout << "\nChoose a data structure to test:" << std::endl;
  std::cout << "\t1. Singly Linked List" << std::endl;
  std::cout << "\t2. Binary Search Tree" << std::endl;
  std::cout << "\t3. Red and Black Tree" << std::endl;
  std::cout << "\t4. Chained Hash Table" << std::endl;
  std::cout << "\nPress '0' to exit" << std::endl;
}

int genRandomInt(int min, int max) {
  static std::mt19937 generator(static_cast<unsigned int>(std::time(nullptr)));
  std::uniform_int_distribution<int> distribution(min, max - 1);
  return distribution(generator);
}

void singlyLinkedList() {
  std::cout << "=== Singly Linked List Tests ===" << std::endl;

  SLList<int>* randomInsertionList = new SLList<int>();
  std::cout << "-- Random Insertion --" << std::endl;
  Timer timer;
  std::cout << "Inserting a million nodes..." << std::endl;
  timer.start();
  for (long long counter = 1000000; counter > 0; --counter) {
    int value = genRandomInt(0, 3000000);
    randomInsertionList->insert(value);
  }
  timer.stop();
  timer.reportDuration();
  std::cout << "Searching for ten thousand random nodes..." << std::endl;
  timer.start();
  for (long long counter = 10000; counter > 0; --counter) {
    int value = genRandomInt(0, 3000000);
    randomInsertionList->search(value);
  }
  timer.stop();
  timer.reportDuration();
  std::cout << "Deleting ten thousand random nodes..." << std::endl;
  timer.start();
  for (long long counter = 10000; counter > 0; --counter) {
    int value = genRandomInt(0, 3000000);
    randomInsertionList->remove(value);
  }
  timer.stop();
  timer.reportDuration();
  delete randomInsertionList;

  SLList<int>* orderedInsertionList = new SLList<int>();
  std::cout << "\n-- Ordered Insertion --" << std::endl;
  std::cout << "Inserting a million nodes, in order..." << std::endl;
  timer.start();
  for (long long counter = 1000000; counter > 0; --counter) {
    int value = 1000000 - counter;
    orderedInsertionList->insert(value);
  }
  timer.stop();
  timer.reportDuration();
  std::cout << "Searching for ten thousand random nodes..." << std::endl;
  timer.start();
  for (long long counter = 10000; counter > 0; --counter) {
    int value = genRandomInt(0, 3000000);
    orderedInsertionList->search(value);
  }
  timer.stop();
  timer.reportDuration();
  std::cout << "Deleting ten thousand random nodes..." << std::endl;
  timer.start();
  for (long long counter = 10000; counter > 0; --counter) {
    int value = genRandomInt(0, 3000000);
    orderedInsertionList->remove(value);
  }
  timer.stop();
  timer.reportDuration();
  delete orderedInsertionList;
}

void binarySearchTree() {
  std::cout << "=== Binary Search Tree Tests ===" << std::endl;

  BSTree<int>* randomInsertionBSTree = new BSTree<int>();
  std::cout << "-- Random Insertion --" << std::endl;
  Timer timer;
  std::cout << "Inserting a million nodes..." << std::endl;
  timer.start();
  for (long long counter = 1000000; counter > 0; --counter) {
    int value = genRandomInt(0, 3000000);
    randomInsertionBSTree->insert(value);
  }
  timer.stop();
  timer.reportDuration();
  std::cout << "Searching for ten thousand random nodes..." << std::endl;
  timer.start();
  for (long long counter = 10000; counter > 0; --counter) {
    int value = genRandomInt(0, 3000000);
    randomInsertionBSTree->search(randomInsertionBSTree->getRoot(), value);
  }
  timer.stop();
  timer.reportDuration();
  std::cout << "Deleting ten thousand random nodes..." << std::endl;
  timer.start();
  for (long long counter = 10000; counter > 0; --counter) {
    int value = genRandomInt(0, 3000000);
    randomInsertionBSTree->remove(value);
  }
  timer.stop();
  timer.reportDuration();
  delete randomInsertionBSTree;

  BSTree<int>* orderedInsertionBSTree = new BSTree<int>();
  std::cout << "\n-- Ordered Insertion --" << std::endl;
  std::cout << "Inserting a million nodes, in order..." << std::endl;
  timer.start();
  orderedInsertionBSTree->fastinsert(1000000);
  timer.stop();
  timer.reportDuration();
  std::cout << "Searching for ten thousand random nodes..." << std::endl;
  timer.start();
  for (long long counter = 10000; counter > 0; --counter) {
    int value = genRandomInt(0, 3000000);
    orderedInsertionBSTree->search(orderedInsertionBSTree->getRoot(), value);
  }
  timer.stop();
  timer.reportDuration();
  std::cout << "Deleting ten thousand random nodes..." << std::endl;
  timer.start();
  for (long long counter = 10000; counter > 0; --counter) {
    int value = genRandomInt(0, 3000000);
    orderedInsertionBSTree->remove(value);
  }
  timer.stop();
  timer.reportDuration();
  delete orderedInsertionBSTree;
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
        singlyLinkedList();
        break;
      case 2:
        binarySearchTree();
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
        std::cout << "\nGoodbye!" << std::endl;
        break;
      default:
        std::cout << "Please make sure to choose a valid option (0 to 4)"
          << std::endl;
        break;
    }
  }
}
