#ifndef NUMCPP_SERIES_HPP
#define NUMCPP_SERIES_HPP

#include <algorithm>
#include <concepts>
#include <iostream>
#include <numeric>
#include <vector>

namespace NumCpp {

template<typename T>
concept Numeric = std::is_arithmetic_v<T>;

template<Numeric DataType, typename IndexType>
class Series {
private:
  struct Entry {
    IndexType index;
    DataType data;
  };

  std::vector<Entry> entries;

public:
  Series(const std::vector<DataType>& data, const std::vector<IndexType>&index) {
    if (data.size() != index.size()) {
      throw std::invalid_argument("ERROR Series(data, index): both arguments must be equal-sized.");
    }

    for (size_t i = 0; i < data.size(); i++) {
      entries.emplace_back(index[i], data[i]);
    }
  }

  Series(const std::vector<DataType>& data) {
    // Index is enumeration [0, n-1]
    std::vector<size_t> index(data.size());
    std::iota(index.begin(), index.end(), 0);

    for (size_t i = 0; i < data.size(); i++) {
      entries.emplace_back(index[i], data[i]);
    }
  }

  void sort() {
    std::sort(entries.begin(), entries.end(),
              [](const Entry& a, const Entry& b) {
                return a.data < b.data;
              });
  }

  void print() {
    for (const Entry& e : entries) {
      std::cout << e.index << "\t" << e.data << std::endl;
    }
  }
};  // class Series
}   // namespace NumCpp

#endif  // NUMCPP_SERIES_HPP

