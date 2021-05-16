#include "graph.hpp"
#include <vector>

namespace graph {
    struct distance {
        weight_t dist;
        node_t node;
        bool operator<(const distance& x) const {
            return dist < x.dist;
        }
    };
    typedef struct distance distance;
    typedef struct {
        node_t node;
        std::vector<distance> dist_v;
    } distances;

    std::vector<distance> dijkstra(const Graph &gr, const node_t start_node);
    std::pair<bool, std::vector<distance>> bellman_ford(const Graph &gr, const node_t start_node);
    std::pair<bool, std::vector<distances>> johnson(Graph gr);
}