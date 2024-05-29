#include "base.hpp"

#include <functional>
#include <stack>
#include <unordered_set>
#include <vector>
#include <iostream>


namespace graph {

bool operator < (const Edge& lhs, const Edge& rhs) {
    return lhs.weight < rhs.weight;
}

bool operator == (const Edge& lhs, const Edge& rhs) {
    return std::hash<graph::Edge>{}(lhs) == std::hash<graph::Edge>{}(rhs);
}

std::vector<vertex_t> IGraph::PreorderTraversal(vertex_t start) const {
    std::vector<bool> visited(VerticesCount(), false);

    std::stack<vertex_t> stack;
    stack.push(start);

    std::vector<vertex_t> result;
    while (!stack.empty()) {
        auto current_vertex = stack.top();
        stack.pop();

        visited[current_vertex] = true;
        result.push_back(current_vertex);

        for (const auto& edge: GetNextEdges(current_vertex)) {
            if (!visited[edge.to]) {
                stack.push(edge.to);
            }
        }
    }

    return result;
}

std::ostream& operator << (std::ostream& out, const IGraph& graph) {
    for (std::size_t i = 0; i < graph.VerticesCount(); ++i) {
        for (const auto& edge: graph.GetNextEdges(i)) {
            out << edge.from << " -> " << edge.to << std::endl;
        }
    }

    return out;
}

double IGraph::GetWeight(vertex_t from, vertex_t to) const {
    for (const auto& edge: GetNextEdges(from)) {
        if (edge.to == to) {
            return edge.weight;
        }
    }

    throw;
}

}  // namespace graph


void HashCombine(std::size_t& seed, std::size_t hash) {
    seed ^= hash + (seed << 3);
}

// bool operator == (const graph::Edge& lhs, const graph::Edge& rhs) {
//     return std::hash<graph::Edge>{}(lhs) == std::hash<graph::Edge>{}(rhs);
// }
