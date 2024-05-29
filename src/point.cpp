#include "point.hpp"
#include "graph/repr/base.hpp"
#include "graph/repr/arc.hpp"

#include <random>
#include <cmath>
#include <limits>


double GetLen(const Point& lhs, const Point& rhs) {
    return std::sqrt(
        std::pow(lhs.x - rhs.x, 2) +
        std::pow(lhs.y - rhs.y, 2)
    );
}

std::vector<Point> GetPoints(std::size_t count) {
    std::random_device rand_device;
    std::default_random_engine generator(rand_device());
    std::uniform_real_distribution<double> dist(-1.0, 1.0);

    std::vector<Point> points;
    while (count--) {
        double s = 0, u, v;
        while (!(0 < s && s <= 1)) {
            u = dist(generator);
            v = dist(generator);
            s = u * u + v * v;
        }

        double x = u * std::sqrt((-2 * std::log(s)) / s);
        double y = v * std::sqrt((-2 * std::log(s)) / s);
        points.push_back({x, y});
    }

    return points;
}

void FillGraph(const std::vector<Point>& points, graph::IGraph& graph) {
    for (std::size_t i = 0; i < points.size() - 1; ++i) {
        for (std::size_t j = i + 1; j < points.size(); ++j) {
            double weight = GetLen(points[i], points[j]);
            graph.AddEdge(i, j, weight);
        }
    }
}

double GetApproximateSalesman(const std::vector<Point>& points) {
    graph::ArcGraph graph(points.size());
    FillGraph(points, graph);

    auto mst = graph.GetMST();
    auto preorder_vertices = mst.PreorderTraversal(0);

    double approximate_solution = 0;
    for (std::size_t i = 0; i < preorder_vertices.size() - 1; ++i) {
        approximate_solution += GetLen(
            points[preorder_vertices[i]],
            points[preorder_vertices[i + 1]]
        );
    }

    return approximate_solution;
}

double GetExactSalesman(std::vector<Point> points) {
    double min_solution = std::numeric_limits<double>::max();
    
    std::vector<std::size_t> point_ids(points.size());
    for (std::size_t i = 0; i < points.size(); ++i) {
        point_ids[i] = i;
    }

    do {
        double current_solution = 0;
        for (std::size_t i = 0; i < points.size() - 1; ++i) {
            current_solution += GetLen(points[point_ids[i]], points[point_ids[i + 1]]);
        }

        min_solution = std::min(min_solution, current_solution);
    } while (std::next_permutation(point_ids.begin(), point_ids.end()));

    return min_solution;
}
