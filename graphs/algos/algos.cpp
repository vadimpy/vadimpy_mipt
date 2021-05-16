#include "algos.hpp"
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <limits.h>
#include <utility>

#define INF_DIS INT_MAX / 2
#define S_NODE 666
using namespace graph;

std::vector<distance> graph::dijkstra(const Graph &gr, const node_t start_node) {
    
    auto const &g = gr.g;
    std::unordered_map<node_t, weight_t> dist_table;
    std::priority_queue<distance> q;

    for (auto it : g)
        dist_table[it.first] = -1;
    dist_table[start_node] = 0;

    q.push(distance{0, start_node});

    while (!q.empty())
    {
        auto nearest_node = q.top();
        q.pop();
        for (auto adj : g.find(nearest_node.node)->second) {
            auto node = adj.first;
            auto weight = adj.second;
            weight_t dist_to_node = dist_table[nearest_node.node] + weight;
            weight_t current_estimation = dist_table[node];
            if ((dist_to_node < current_estimation) || (current_estimation == -1)) {
                dist_table[node] = dist_to_node;
                q.push({dist_to_node, node});
            }
        }
    }

    std::vector<distance> res_table;
    res_table.reserve(dist_table.size());
    for (auto it : dist_table)
        res_table.push_back(distance{it.second, it.first});

    return res_table;
}

std::pair<bool, std::vector<distance>> graph::bellman_ford(const Graph &gr, const node_t start_node) {
    
    auto const &g = gr.g;
    std::unordered_map<node_t, weight_t> dist_table;
    std::unordered_map<node_t, node_t> prec_table;
    std::vector<distance> res_table;

    for (auto it : g)
        dist_table[it.first] = INF_DIS;
    dist_table[start_node] = 0;
    
    for (int i = 1; i <= g.size(); ++i)
        for(auto adj_list : g) {
            auto u = adj_list.first;
            for (auto adj : adj_list.second) {
                auto v = adj.first;
                auto w = adj.second;
                if (dist_table[v] > dist_table[u] + w) {
                    dist_table[v] = dist_table[u] + w;
                    prec_table[v] = u;
                }
            }
    }

    for(auto adj_list : g) {
        auto u = adj_list.first;
        for (auto adj : adj_list.second) {
            auto v = adj.first;
            auto w = adj.second;
            if (dist_table[v] > dist_table[u] + w) {
                return std::make_pair(false, res_table);
            }
        }
    }

    res_table.reserve(dist_table.size());
    for (auto it : dist_table)
        res_table.push_back(distance{it.second, it.first});

    return std::make_pair(true, res_table);

}

std::pair<bool, std::vector<distances>> graph::johnson(Graph gr) {
    std::vector<distances> res_table;
    res_table.reserve(gr.g.size());
    if (gr.non_negative_weights) {
        for (auto it : gr.g) {
            node_t node = it.first;
            auto node_result = dijkstra(gr, node);
            res_table.push_back(distances{node, node_result});
        }
        return std::make_pair(true, res_table);
    }
    else {
        std::unordered_map<node_t, weight_t> s_weights;
        std::unordered_map<node_t, weight_t> h;
        for (auto it : gr.g)
            s_weights[it.first] = 0;
        gr.g.emplace(S_NODE, s_weights);
        auto bf_res = bellman_ford(gr, S_NODE);
        if (!bf_res.first)
            return std::make_pair(false, res_table);
        else {
            for (auto dis : bf_res.second)
                h[dis.node] = dis.dist;
            gr.g.erase(S_NODE);
            for(auto &&adj_list : gr.g) {
                auto &u = adj_list.first;
                for (auto &&adj : adj_list.second) {
                    auto v = adj.first;
                    auto &w = adj.second;
                    w = w + h[u] - h[v];
                }
            }
            for (auto it : gr.g) {
                node_t u = it.first;
                auto node_result = dijkstra(gr, u);
                for (int i = 0; i < node_result.size(); ++i) {
                    auto v = node_result[i].node;
                    node_result[i].dist = node_result[i].dist + h[v] - h[u]; 
                }
                res_table.push_back(distances{u, node_result});
            }
            return std::make_pair(true, res_table);
        }
    }
}