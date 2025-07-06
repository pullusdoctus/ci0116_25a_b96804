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
  void dijkstra();

  /// Prints the distances matrix labeled with the city names
  void printDistances();
  /// Prints the parents matrix labeled with the city names
  void printParents();

  // Getters
  std::vector<std::string>& getCities() { return this->cities; }
  std::vector<std::vector<int>>& getDistances() { return this->distances; }
  std::vector<std::vector<int>>& getParents() { return this->parents; }
};
