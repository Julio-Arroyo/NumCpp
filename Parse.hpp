#ifndef NUMCPP_PARSE_HPP
#define NUMCPP_PARSE_HPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>  // std::shared_ptr
#include <string>
#include <vector>

namespace NumCpp {
  std::shared_ptr<std::vector<std::vector<double>>>
  readCSV(const std::string& fname, const bool skip_first_col=true);

  std::shared_ptr<std::vector<std::vector<double>>>
  readCSV(const std::string& fname, const bool skip_first_col) {
    std::shared_ptr<std::vector<std::vector<double>>> data = std::make_shared<std::vector<std::vector<double>>>();

    // Open the CSV file for reading
    std::ifstream file(fname);
    if (!file.is_open()) {
      std::cerr << "Error: Unable to open file " << fname << std::endl;
      return nullptr;
    }

    std::string line;
    // Read each line from the file
    while (std::getline(file, line)) {
      std::vector<double> row;
      std::stringstream ss(line);
      std::string cell;
      bool skip = true; // Flag to indicate whether to skip the first column

      // Split the line into cells using comma as the delimiter
      while (std::getline(ss, cell, ',')) {
        // Skip the first column if specified and not already skipped
        if (skip_first_col && skip) {
          skip = false;
          continue;
        }

        try {
          double value = std::stod(cell);
          row.push_back(value);
        } catch (const std::invalid_argument& e) {
          std::cerr << "Error: Invalid data found in file " << fname << std::endl;
          return nullptr;
        }
      }

      // Add the row to the data vector
      data->push_back(row);
    }

    // Close the file
    file.close();

    return data;
  }
}

#endif

