#include "files.hpp"
#include <filesystem>
#include <iostream>
#include <sstream>
#include <tuple>
#include <unordered_map>

std::vector<std::string> parseDir(const std::string& dir) {
  // create array of filenames
  std::vector<std::string> filenames;
  try {
    // for every file in the directory
    for (const auto& file : std::filesystem::directory_iterator(dir)) {
      // if the file is a regular file
      if (file.is_regular_file()) {
        // insert its filename in the array
        filenames.push_back(file.path().filename().string());
      }
    }
  } catch (const std::filesystem::filesystem_error& e) {
    std::cerr << "Error reading directory: " << e.what() << std::endl;
  }
  return filenames;
}

std::ifstream openCSV(const std::string& filename) {
  // open the file
  std::ifstream file(filename);
  // check if the file was opened correctly
  if (!file.is_open()) {
    throw std::runtime_error("Could not open CSV file: " + filename);
  }
  return file;
}

void csvToMatrix(std::ifstream& file, std::vector<std::vector<int>>& matrix,
                 int defaultValue) {
  std::string line;
  // skip header
  if (!std::getline(file, line)) {
    throw std::runtime_error("CSV is empty or has no header");
  }
  int maxID = -1;
  std::vector<std::tuple<int, int, int>> edges;  // source_id, target_id, weight
  // read a line from the file
  while (std::getline(file, line)) {
    std::stringstream ss(line);
    std::string sourceIDstr, sourceName, targetIDstr, targetName, weightStr;
    // if it fails to parse any entry in the line, continue
    if (!std::getline(ss, sourceIDstr, ',')) continue;
    if (!std::getline(ss, sourceName, ',')) continue;
    if (!std::getline(ss, targetIDstr, ',')) continue;
    if (!std::getline(ss, targetName, ',')) continue;
    if (!std::getline(ss, weightStr, ',')) continue;
    // extract needed data
    int sourceID = std::stoi(sourceIDstr);
    int targetID = std::stoi(targetIDstr);
    int weight = std::stoi(weightStr);
    // find biggest ID to size matrix
    maxID = std::max(std::max(maxID, sourceID), targetID);
    // store the edges
    edges.emplace_back(sourceID, targetID, weight);
  }
  // sets matrix size based on the number of cities
  int n = maxID + 1;
  // creates an nxn matrix populated with the default value
  matrix.assign(n, std::vector<int>(n, defaultValue));
  // set diagonal to 0 (no distance from city A to city A)
  for (int i = 0; i < n; ++i) {
    matrix[i][i] = 0;
  }
  // set distances from weights gathered from file
  for (const auto& [u, v, w] : edges) {
    matrix[u][v] = w;
  }
}
