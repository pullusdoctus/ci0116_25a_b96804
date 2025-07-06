#include "pathfinder.hpp"

Pathfinder::Pathfinder(std::vector<std::string>& cities,
                       std::vector<std::vector<int>>& distances)
  : cities(cities), distances(distances) {
  this->parents.resize(distances.size(), std::vector<int>(distances.size()));
  this->populateParents();
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
