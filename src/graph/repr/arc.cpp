#include "base.hpp"

#include "arc.hpp"

#include <cassert>
#include <iostream>


namespace graph {

ArcGraph::ArcGraph(std::size_t size): vertices_count_(size) {
}

ArcGraph::ArcGraph(const IGraph& graph) {
    for (std::size_t from = 0; from < graph.VerticesCount(); ++from) {
        for (const auto& edge: graph.GetNextEdges(from)) {
            edges_.push_back(edge);
        }
    }
}

void ArcGraph::AddEdge(vertex_t from, vertex_t to, double weight) {
    assert(from < VerticesCount());
    assert(to < VerticesCount());
    edges_.push_back({from, to, weight});
}

[[nodiscard]] std::size_t ArcGraph::VerticesCount() const {
    return vertices_count_;
}

[[nodiscard]] std::vector<Edge> ArcGraph::GetNextEdges(vertex_t vertex) const {
    assert(vertex < VerticesCount());

    std::vector<Edge> next_vertices;
    for (const auto& edge: edges_) {
        if (edge.from == vertex) {
            next_vertices.push_back(edge);
        }
    }

    return next_vertices;
}

[[nodiscard]] std::vector<Edge> ArcGraph::GetPrevEdges(vertex_t vertex) const {
    assert(vertex < VerticesCount());

    std::vector<Edge> prev_vertices;
    for (const auto& edge: edges_) {
        if (edge.to == vertex) {
            prev_vertices.push_back(edge);
        }
    }

    return prev_vertices;
}

ArcGraph ArcGraph::GetMST() {
    std::sort(edges_.begin(), edges_.end());

    ArcGraph mst_graph(VerticesCount());

    DSU dsu(VerticesCount());
    for (const auto& edge: edges_) {
        auto first_set = dsu.FindSet(edge.from);
        auto second_set = dsu.FindSet(edge.to);
        if (first_set != second_set) {
            dsu.UnionSet(first_set, second_set);
            mst_graph.AddEdge(edge.from, edge.to, edge.weight);
            mst_graph.AddEdge(edge.to, edge.from, edge.weight);
        }
    }

    return mst_graph;
}

}  // namespace graph
