#include "math.hpp"

#include <vector>
#include <cmath>


double GetAverage(const std::vector<double>& values) {
    double total = 0;
    for (auto value: values) {
        total += value;
    }

    return total / values.size();
}

double GetStandartDeviation(const std::vector<double>& values, double avg_value) {
    double result = 0;
    for (auto value: values) {
        result += std::pow(value - avg_value, 2);
    }

    return std::sqrt(result / values.size());
}
