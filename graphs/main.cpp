#include <iostream>
#include <graph.hpp>
#include <algos.hpp>

using namespace graph;

int main()
{
    std::string in;
    std::getline(std::cin, in);

    graph::Graph gr(in);
    gr.print();

    auto dist_table = johnson(gr);
    if (!dist_table.first) {
        std::cout << "Negative loop!";
    }
    std::cout << "\nShortest distances:\n\n";
    for (auto node_distances : dist_table.second) {
        std::cout << "Node " << node_distances.node << ":\n\n";
        for (auto distance : node_distances.dist_v)
            std::cout << '\t' << distance.node << " : " << distance.dist << '\n';
        std::cout << "\n\n";
    }
    return 0;
}