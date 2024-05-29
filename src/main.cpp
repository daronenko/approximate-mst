#include "graph/repr/base.hpp"
#include "graph/repr/arc.hpp"
#include "point.hpp"
#include "math.hpp"

#include <iostream>
#include <vector>


int main() {
    for (std::size_t points_count = 2; points_count < 10; ++points_count) {
        std::cout << std::endl;

        std::vector<double> results;
        for (std::size_t i = 0; i < 10; ++i) {
            auto points = GetPoints(points_count);

            auto approximate_salesman = GetApproximateSalesman(points);
            auto exact_salesman = GetExactSalesman(points);

            results.push_back(approximate_salesman / exact_salesman);
        }

        auto avg_result = GetAverage(results);
        auto standart_deviation = GetStandartDeviation(results, avg_result);

        std::cout << "Points count: " << points_count << std::endl;
        std::cout << "Average: " << avg_result << std::endl;
        std::cout << "Standart deviation: " << standart_deviation << std::endl;
    }

    return 0;
}
