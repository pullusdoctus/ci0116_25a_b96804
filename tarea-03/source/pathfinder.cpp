#include "pathfinder.hpp"
#include <algorithm>
#include <climits>
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

int Pathfinder::bestHub() {
  int n = this->distances.size();
  int best = -1;
  int min = INT_MAX;
  // for every city
  for (int i = 0; i < n; ++i) {
    // find the total distance to every other city
    int total = 0;
    for (int j = 0; j < n; ++j) {
      if (i != j && this->distances[i][j] != -1)
        total += this->distances[i][j];
    }
    // if the total distance is less than the minimum distance found
    if (total < min) {
      // this city is the new best hub
      min = total;
      best = i;
    }
  }
  return best;
}

int Pathfinder::bestCityToHelp(int target) {
  int n = this->distances.size();
  int best = -1;
  int min = INT_MAX;
  // for every city with a path to the target
  for (int i = 0; i < n; ++i) {
    // if the origin city has a path to the target, and that path is the
    // shortest path found so far
    if (i != target && this->distances[i][target] != -1
        && this->distances[i][target] < min) {
      // this city is the new, best city to send help to the target
      min = this->distances[i][target];
      best = i;
    }
  }
  return best;
}

std::vector<int> Pathfinder::mostDistantPair(int& origin, int& destiny,
                                             int& time) {
  int n = this->distances.size();
  int max = -1;
  // from every origin city
  for (int i = 0; i < n; ++i) {
    // to every destiny city
    for (int j = 0; j < n; ++j) {
      // find the greatest distance and compare it with the overall max
      if (i != j && this->distances[i][j] > max) {
        max = this->distances[i][j];
        origin = i;
        destiny = j;
      }
    }
  }
  // store the time that it takes to go from origin to destiny
  time = max;
  // return an array of indices with the path from origin to destiny
  return this->reconstructPath(origin, destiny);
}

std::vector<int> Pathfinder::closestPair(int& origin, int& destiny, int& time) {
  int n = this->distances.size();
  int min = INT_MAX;
  // from every origin city
  for (int i = 0; i < n; ++i) {
    // to every destiny city
    for (int j = 0; j < n; ++j) {
      // find the shortest overall distance
      if (i != j && this->distances[i][j] != -1
        && this->distances[i][j] < min) {
        min = this->distances[i][j];
        origin = i;
        destiny = j;
      }
    }
  }
  // store the time that it takes to go from origin to destiny
  time = min;
  // return an array of indices with the path from origin to destiny
  return this->reconstructPath(origin, destiny);
}

std::vector<int> Pathfinder::reconstructPath(int origin, int destiny) {
  // no path exists
  if (this->parents[origin][destiny] == -1) return {};
  std::vector<int> path;
  int current = destiny;
  // go from destiny to origin through the parents matrix
  while (current != origin) {
    // if the path is broken somewhere
    if (current == -1) return {};
    path.push_back(current);
    current = this->parents[origin][current];
  }
  path.push_back(origin);  // add the origin city
  // invert the path: destiny->origin ==> origin->destiny
  std::reverse(path.begin(), path.end());
  return path;
}

void Pathfinder::printData() {
  this->printDistances();
  this->printParents();

  int hub = this->bestHub();
  std::cout << "\nThe best city to use as a hub is " << this->cities[hub]
    << std::endl;

  int origin = -1, destiny = -1, time = 0;
  std::vector<int> distantPairPath
    = this->mostDistantPair(origin, destiny, time);
  std::cout << "\nThe two cities with the greatest distance between them are "
    << this->cities[origin] << " and " << this->cities[destiny]
    << ", with a time of " << time << std::endl;
  std::cout << "To go from " << this->cities[origin] << " to "
    << this->cities[destiny] << ", you must follow this path:" << std::endl;
  this->printPath(distantPairPath);

  origin = -1;
  destiny = -1;
  time = 0;
  std::vector<int> closestPairPath
    = this->closestPair(origin, destiny, time);
  std::cout << "\nThe two cities with the shortest distance between them are "
    << this->cities[origin] << " and " << this->cities[destiny]
    << ", with a time of " << time << std::endl;
  std::cout << "To go from " << this->cities[origin] << " to "
    << this->cities[destiny] << ", you must follow this path:" << std::endl;
  this->printPath(closestPairPath);

  this->printByAverage();
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

void Pathfinder::printByAverage() {
  int n = this->distances.size();
  std::vector<std::pair<std::string, double>> averages;
  // for every city
  for (int i = 0; i < n; ++i) {
    // find the sum of all distances from this city
    int total = 0, count = 0;
    for (int j = 0; j < n; ++j) {
      if (i != j && this->distances[i][j] != -1) {
        total += this->distances[i][j];
        ++count;
      }
    }
    // get the average for this city
    double avg = (count > 0) ? static_cast<double>(total) / count : 0.0;
    averages.emplace_back(this->cities[i], avg);
  }
  // sort the averages
  std::sort(averages.begin(), averages.end(), [](auto& a, auto& b)
            { return a.second < b.second; });
  // print the results
  std::cout << "\nCities ordered by average travel time:" << std::endl;
  for (const auto& [name, avg] : averages) {
    std::cout << name << ": " << avg << std::endl;
  }
}

void Pathfinder::printPath(const std::vector<int>& path) {
  for (size_t i = 0; i < path.size(); ++i) {
    std::cout << this->cities[path[i]];
    if (i < path.size() - 1) std:: cout << " -> ";
  }
  std::cout << std::endl;
}
