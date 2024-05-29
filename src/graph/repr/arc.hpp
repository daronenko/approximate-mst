#pragma once

#include "base.hpp"
// #include "graph/mst/mst.hpp"
#include "graph/dsu/dsu.hpp"

#include <vector>


namespace graph {

class ArcGraph: public IGraph {
 public:
    explicit ArcGraph(std::size_t size);

    explicit ArcGraph(const IGraph& graph);

    void AddEdge(vertex_t from, vertex_t to, double weight) override;

    [[nodiscard]] std::size_t VerticesCount() const override;

    [[nodiscard]] std::vector<Edge> GetNextEdges(vertex_t vertex) const override;

    [[nodiscard]] std::vector<Edge> GetPrevEdges(vertex_t vertex) const override;

    ArcGraph GetMST();

 private:
    std::size_t vertices_count_;
    std::vector<Edge> edges_;
};

}  // namespace graph
