#include "graph.hpp"
#include <sstream>
#include <iostream>

using namespace graph;

Graph::Graph(std::string &graph_description) : non_negative_weights(true) {
    parse_input_data(graph_description);
}

void Graph::parse_input_data(std::string const &graph_description){
    
    enum fsm_state{
        from_id,
        to_id,
        weight
    };

    std::stringstream in(graph_description);
    fsm_state state = fsm_state::from_id;
    
    std::string token;
    adjacency adj;
    node_t to_node_id;
    node_t from_node_id;
    weight_t w;

    while (! in.eof()) {
        in >> token;
        switch (state) {
        case fsm_state::from_id:
            token = token.substr(0, token.size()-1);
            from_node_id = std::stoi(token);
            state = fsm_state::to_id;
        break;
        case fsm_state::to_id:
            if (token != ";") {
                to_node_id = std::stoi(token);
                state = fsm_state::weight;
            }
            else {
                g[from_node_id] = adj;
                adj.clear();
                state = fsm_state::from_id;
            }
        break;
        case fsm_state::weight:
            token = token.substr(1, token.size()-1);
            w = std::stoi(token);
            if (w < 0)
                non_negative_weights = false;
            adj[to_node_id] = w;
            state = fsm_state::to_id;
        break;
        }
    }
}

void Graph::print() {
    std::cout << "\nProcessed graph:\n\n";
    for (auto from_node : g) {
        std::cout << "Node " << from_node.first << " edges:\n\n";
        if (from_node.second.size() == 0)
            std::cout << "\tno edges\n";
        for (auto it : from_node.second)
            std::cout << '\t' << it.first << " : " << it.second << '\n';
        std::cout << std::endl;
    }
}