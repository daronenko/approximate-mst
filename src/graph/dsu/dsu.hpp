#pragma once

#include "graph/repr/base.hpp"

#include <vector>


namespace graph {

class DSU {
 public:
    explicit DSU(std::size_t size);

    vertex_t FindSet(vertex_t u);

    void UnionSet(vertex_t u, vertex_t v);

 private:
    std::vector<vertex_t> parent_;
    std::vector<std::size_t> rank_;
};

}  // namespace graph
