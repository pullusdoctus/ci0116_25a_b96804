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

std::vector<int> Pathfinder::bestHubs() {
  int n = this->distances.size();
  int min = INT_MAX;
  std::vector<int> bestHubs;
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
      bestHubs.clear();
      bestHubs.push_back(i);
    } else if (total == min) {
      // add this other city as a candidate if its total equals the
      // minimum distance found
      bestHubs.push_back(i);
    }
  }
  return bestHubs;
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

std::vector<int> Pathfinder::findClosest(int origin) {
  int min = INT_MAX, n = this->distances.size();
  std::vector<int> closest;
  // for every adjacent city
  for (int i = 0; i < n; ++i) {
    // skip the origin city and invalid connections
    if (i != origin && this->distances[origin][i] > -i) {
      int distance = this->distances[origin][i];
      // find the one that's closest to the origin city
      if (distance < min) {
        min = distance;
        closest.clear();
        closest.push_back(i);
      } else if (distance == min) {
        // if another candidate is found
        closest.push_back(i);
      }
    }
  }
  return closest;
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

void Pathfinder::printHub() {
  std::vector<int> hubs = this->bestHubs();
  if (hubs.empty()) {
    std::cout << "\nNo valid hubs found." << std::endl;
    return;
  }
  if (hubs.size() == 1) {
    std::cout << "\nThe best city to use as a hub is " << this->cities[hubs[0]]
      << std::endl;
    int n = hubs.size();
    int total = 0;
    for (int i = 0; i < n; ++i) {
      if (i != hubs[0] && this->distances[hubs[0]][i] != -1)
        total += this->distances[hubs[0]][i];
    }
    std::cout << "\nThe total distance from this city is " << total
      << std::endl;
  } else {
    std::cout << "\nThe best cities to use as hubs are:" << std::endl;
    int n = hubs.size();
    for (int i = 0; i < n; ++i) {
      std::cout << " " << this->cities[hubs[i]] << std::endl;
      int total = 0;
      for (int j = 0; j < n; ++j) {
        if (i != j && this->distances[i][j] != -1)
          total += this->distances[i][j];
      }
      std::cout << "The total distance from this city is " << total
        << std::endl;
    }
  }
}

void Pathfinder::printMostDistantPair() {
  int origin = -1, destiny = -1, time = 0;
  std::vector<int> distantPairPath
    = this->mostDistantPair(origin, destiny, time);
  std::cout << "\nThe two cities with the greatest distance between them are "
    << this->cities[origin] << " and " << this->cities[destiny]
    << ", with a time of " << time << std::endl;
  std::cout << "To go from " << this->cities[origin] << " to "
    << this->cities[destiny] << ", you must follow this path:" << std::endl;
  this->printPath(distantPairPath);
}

void Pathfinder::printClosestPair() {
  int origin = -1, destiny = -1, time = 0;
  std::vector<int> closestPairPath
    = this->closestPair(origin, destiny, time);
  std::cout << "\nThe two cities with the shortest distance between them are "
    << this->cities[origin] << " and " << this->cities[destiny]
    << ", with a time of " << time << std::endl;
  std::cout << "To go from " << this->cities[origin] << " to "
    << this->cities[destiny] << ", you must follow this path:" << std::endl;
  this->printPath(closestPairPath);
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

void Pathfinder::promptFindHelpToCity() {
  std::cout << "\n== Find Helper City ==" << std::endl;
  std::cout << "Choose a city (by number) that you wish to find"
    " the closest city to it, in order to send help:" << std::endl;
  while (true) {
    std::cout << "0. Exit" << std::endl;
    this->printCities();
    long unsigned int choice = 0;
    std::cin >> choice;
    if (choice > this->cities.size()) {
      std::cout << "\nInvalid choice. Please make sure you entered a valid number"
        << std::endl;
      std::cout << "Press Enter to continue..." << std::endl;
      std::cin.ignore();
      std::cin.get();
    }
    else if (choice == 0) return;
    else {
      std::vector<int> closest = this->findClosest(--choice);
      if (closest.empty()) {
        std::cout << "\nNo helper city found from " << this->cities[choice]
          << std::endl;
      } else if (closest.size() == 1) {
        std::cout << "\nThe closest city to " << this->cities[choice]
          << " is " << this->cities[closest[0]] << std::endl;
      } else {
        std::cout << "\nThe closest cities to " << this->cities[choice]
          << " are: " << std::endl;
        int n = closest.size();
        for (int i = 0; i < n; ++i) {
          std::cout << " " << this->cities[closest[i]] << std::endl;
        }
      }
      std::cout << "Press Enter to continue..." << std::endl;
      std::cin.ignore();
      std::cin.get();
    }
  }
}

void Pathfinder::printCities() {
  int n = this->cities.size();
  for (int i = 0; i < n; ++i) {
    std::cout << i + 1 << ". " << this->cities[i] << std::endl;
  }
}
