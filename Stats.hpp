#ifndef NUMCPP_STATS_HPP
#define NUMCPP_STATS_HPP

#include <stdexcept>
#include <cstddef>    // size_t
#include <vector>
#include <cmath>      // std::pow

namespace NumCpp {
  double mean(const std::vector<double>& x);
  double moment(const std::vector<double>& x, const size_t k);
  double std(const std::vector<double>& x);
  double skew(const std::vector<double>& x);
  double kurtosis(const std::vector<double>& x, const bool excess=true);

  double mean(const std::vector<double>& x) {
    size_t n{x.size()};
    double sum = 0.0;
    for (double value : x) {
        sum += value;
    }
    return sum / n;
  }

  /**
   * Computes the k-th central moment of a sample.
   * 
   * @param x A vector of doubles representing the data points.
   * @param k The order of the central moment to compute. Must be a positive integer.
   * @return The k-th central moment of the data points in vector x.
   * @throws std::invalid_argument if the vector x is empty or if k is zero.
   * 
   * m_k = \frac{\sum_{i=1}^n(x_i - \bar{x})^k}{n}
   */
  double moment(const std::vector<double>& x, const size_t k) {
    size_t n = x.size();
    if (n == 0) {
      throw std::invalid_argument("ERROR moment(x, k). x must not be empty");
    } else if (k == 0) {
      throw std::invalid_argument("ERROR moment(x, k): k must be greater than zero");
    }

    double x_bar = mean(x);
    double sum = 0;
    for (double x_i : x) {
      sum += std::pow(x_i - x_bar, k);
    }
    return sum/n;
  }

  double std(const std::vector<double>& x) {
    return std::sqrt(moment(x, 2));
  }

  double skew(const std::vector<double>& x) {
    size_t n = x.size();
    if (n == 0) {
      throw std::invalid_argument("ERROR skew: cannot compute skewness of empty vector");
    }

    double m3 = moment(x, 3);
    double m2 = moment(x, 2);

    double skew = m3/std::sqrt(std::pow(m2, 3));

    return skew;
  }

  double kurtosis(const std::vector<double>& x, const bool excess) {
    size_t n = x.size();
    if (n == 0) {
      throw std::invalid_argument("ERROR kurtosis: cannot compute kurtosis of empty vector");
    }

    double m4 = moment(x, 4);
    double var = moment(x, 2);

    double kurt = m4/std::pow(var, 2);
    if (excess) {
      kurt -= 3;
    }

    return kurt;
  }
}

#endif  // NUMCPP_STATS_HPP

