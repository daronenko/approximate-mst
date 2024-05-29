#pragma once

#include "graph/repr/base.hpp"

#include <vector>


struct Point {
    double x, y;
};

double GetLen(const Point& lhs, const Point& rhs);

std::vector<Point> GetPoints(std::size_t count);

void FillGraph(const std::vector<Point>& points, graph::IGraph& graph);

double GetApproximateSalesman(const std::vector<Point>& points);
double GetExactSalesman(std::vector<Point> points);
