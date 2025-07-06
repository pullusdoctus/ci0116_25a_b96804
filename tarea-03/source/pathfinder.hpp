#pragma once

#include <string>
#include <vector>

class Pathfinder {
 private:
  /// Array containing city names
  std::vector<std::string> cities;
  /// Matrix containing the distances from one node to another
  std::vector<std::vector<int>> distances;
  /// Matrix containing parent nodes
  std::vector<std::vector<int>> parents;
  /// The length of the longest city name
  long unsigned int cityNameMaxLength = 0;

  /// Populates the parents matrix based on data found in the distances matrix
  void populateParents();

 public:
  /// Constructor
  Pathfinder(std::vector<std::string>& cities,
             std::vector<std::vector<int>>& distances);
  /// Destructor
  ~Pathfinder();

  /// Runs the Floyd-Warshall algorithm against the distances and parents matrices
  void floydWarshall();
  /// TODO: Runs the Dijkstra algorithm for a specific node
  /// NOTE: was not needed; is not implemented
  void dijkstra();

  /// Finds the best city to assign as a distribution hub
  int bestHub();
  /// Find the closest city to send help to another, target city
  int bestCityToHelp(int target);
  /// Finds the pair of cities which are the furthest from each other
  std::vector<int> mostDistantPair(int& origin, int& destiny, int& time);
  /// Finds the pair of cities which are the closest from each other
  std::vector<int> closestPair(int& origin, int& destiny, int& time);
  /// Reconstructs a path from an origin city to a destiny city
  std::vector<int> reconstructPath(int origin, int destiny);
  /// Finds the closest city from the origin city
  int findClosest(int origin);

  /// Prints the distances matrix labeled with the city names
  void printDistances();
  /// Prints the parents matrix labeled with the city names
  void printParents();
  /// Finds and prints the Hub City's name
  void printHub();
  /// Finds and prints the pair of cities which are the furthest from each other
  void printMostDistantPair();
  /// Finds and prints the pair of cities which are the closest from each other
  void printClosestPair();
  /// Prints all cities in order of their average travel distance to other cities
  void printByAverage();
  /// Prints a path from an origin city to a destiny city
  void printPath(const std::vector<int>& path);
  /// Prompts the user to select a city, then finds and displays the closest city to send help from
  void promptFindHelpToCity();
  /// Prints the list of loaded cities
  void printCities();

  // Getters
  std::vector<std::string>& getCities() { return this->cities; }
  std::vector<std::vector<int>>& getDistances() { return this->distances; }
  std::vector<std::vector<int>>& getParents() { return this->parents; }
};
