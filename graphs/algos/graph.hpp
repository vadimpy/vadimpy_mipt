#pragma once
#include <string>
#include <unordered_map>

namespace graph {

    typedef unsigned int node_t;
    typedef int weight_t;

    typedef std::unordered_map<node_t, weight_t>  adjacency;
    typedef std::unordered_map<node_t, adjacency> adjacency_list;

    class Graph
    {
        public:
            Graph(std::string &graph_description);
            adjacency_list g;
            bool non_negative_weights;
            void print();
        private:
            void parse_input_data(std::string const &graph_description);
    };
};