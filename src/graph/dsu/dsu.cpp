#include "dsu.hpp"
#include "graph/repr/base.hpp"

#include <stack>


namespace graph {

DSU::DSU(std::size_t size): parent_(size), rank_(size, 1) {
    for (vertex_t i = 0; i < size; ++i) {
        parent_[i] = i;
    }
}

vertex_t DSU::FindSet(vertex_t u) {
    std::stack<vertex_t> stack;
    stack.push(u);

    while (parent_[u] != u) {
        stack.push(parent_[u]);
        u = parent_[u];
    }

    vertex_t& root = u;

    while (!stack.empty()) {
        parent_[stack.top()] = root;
        stack.pop();
    }

    return root;
}

void DSU::UnionSet(vertex_t u, vertex_t v) {
    u = FindSet(u);
    v = FindSet(v);

    if (u != v) {
        if (rank_[u] < rank_[v]) {
            std::swap(u, v);
        }

        parent_[v] = u;
        rank_[u] += rank_[v];
    }
}

}  // namespace graph
