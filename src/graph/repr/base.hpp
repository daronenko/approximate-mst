#pragma once

#include <functional>
#include <vector>
#include <cstdint>
#include <ostream>


namespace graph {

using vertex_t = std::uint64_t;

struct Edge {
    vertex_t from;
    vertex_t to;
    double weight;
};

bool operator < (const Edge& lhs, const Edge& rhs);

bool operator == (const Edge &lhs, const Edge &rhs);

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(vertex_t from, vertex_t to, double weight) = 0;

    [[nodiscard]] virtual std::size_t VerticesCount() const  = 0;

    [[nodiscard]] virtual std::vector<Edge> GetNextEdges(vertex_t vertex) const = 0;
    [[nodiscard]] virtual std::vector<Edge> GetPrevEdges(vertex_t vertex) const = 0;

    std::vector<vertex_t> PreorderTraversal(vertex_t start) const;

    double GetWeight(vertex_t from, vertex_t to) const;
};

std::ostream& operator << (std::ostream& out, const IGraph& graph);

}  // namespace graph


void HashCombine(std::size_t& seed, std::size_t hash);

template<>
struct std::hash<graph::Edge> {
    std::size_t operator () (const graph::Edge& edge) const noexcept {
        std::size_t hash_1 = std::hash<graph::vertex_t>{}(edge.from);
        std::size_t hash_2 = std::hash<graph::vertex_t>{}(edge.to);
        std::size_t hash_3 = std::hash<double>{}(edge.weight);

        std::size_t seed = 0;
        HashCombine(seed, hash_1);
        HashCombine(seed, hash_2);
        HashCombine(seed, hash_3);

        return seed;
    }
};

// bool operator == (const graph::Edge& lhs, const graph::Edge& rhs);
