#include "pathfinder.hpp"
#include <iostream>
#include <iomanip>

Pathfinder::Pathfinder(std::vector<std::string>& cities,
                       std::vector<std::vector<int>>& distances)
  : cities(cities), distances(distances), cityNameMaxLength(0) {
  this->parents.resize(distances.size(), std::vector<int>(distances.size()));
  this->populateParents();
  // find the maximum length for city names
  for (const std::string& name : this->cities) {
    if (name.length() > this->cityNameMaxLength)
      this->cityNameMaxLength = name.length();
  }
}

Pathfinder::~Pathfinder() {
}

void Pathfinder::populateParents() {
  int n = this->distances.size();
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      // if there isn't a connection, or it's a diagonal
      if (this->distances[i][j] == -1 || i == j) this->parents[i][j] = -1;
      // if there's a connection
      else this->parents[i][j] = i;
    }
  }
}

void Pathfinder::floydWarshall() {
  int n = this->distances.size();
  // Floyd-Warhsall
  for (int k = 0; k < n; ++k) {       // intermediate
    for (int i = 0; i < n; ++i) {     // source
      for (int j = 0; j < n; ++j) {   // destination
        // check if the path through k is shorter
        if (this->distances[i][k] != -1 && this->distances[k][j] != -1) {
          int newDistance = this->distances[i][k] + this->distances[k][j];
          // if the path through the intermediate node is better
          if (this->distances[i][j] == -1 ||
            newDistance < this->distances[i][j]) {
            this->distances[i][j] = newDistance;
            this->parents[i][j] = this->parents[k][j];
          }
        }
      }
    }
  }
}

void Pathfinder::dijkstra() {  // TODO:
}

void Pathfinder::printDistances() {
  int n = this->distances.size();
  int fieldWidth = this->cityNameMaxLength + 4;
  std::cout << "Distance Matrix (" << n << "x" << n << "):" << std::endl;
  // top header
  std::cout << std::setw(fieldWidth) << "";  // empty top left
  for (const auto& name : this->cities) {
    std::cout << std::setw(fieldWidth) << name;
  }
  std::cout << std::endl;
  // rows
  for (int i = 0; i < n; ++i) {
    std::cout << std::setw(fieldWidth) << cities[i];  // row label
    for (int j = 0; j < n; ++j) {
      if (this->distances[i][j] == -1)
        std::cout << std::setw(fieldWidth) << "[∞]";
      else
        std::cout << std::setw(fieldWidth)
          << ('[' + std::to_string(this->distances[i][j]) + ']');
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

void Pathfinder::printParents() {
  int n = this->distances.size();
  int fieldWidth = this->cityNameMaxLength + 4;
  std::cout << "Parent Matrix (" << n << "x" << n << "):" << std::endl;
  // top header
  std::cout << std::setw(fieldWidth) << "";  // empty top left
  for (const auto& name : this->cities) {
    std::cout << std::setw(fieldWidth) << name;
  }
  std::cout << std::endl;
  // rows
  for (int i = 0; i < n; ++i) {
    std::cout << std::setw(fieldWidth) << cities[i];  // row label
    for (int j = 0; j < n; ++j) {
      if (this->parents[i][j] == -1)
        std::cout << std::setw(fieldWidth) << "[-]";
      else
        std::cout << std::setw(fieldWidth)
          << ('[' + std::to_string(this->parents[i][j]) + ']');
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}
