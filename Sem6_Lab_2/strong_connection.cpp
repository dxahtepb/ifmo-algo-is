#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

enum {WHITE, GRAY, BLACK};

std::vector<int> components;
std::vector<int> color;
std::vector<int> order;
std::vector< std::vector<int> > graph;
std::vector< std::vector<int> > transposed_graph;

bool dfs_sort(int v)
{
    color[v] = BLACK;

    for (int u : graph[v])
    {
        if (color[u] == WHITE)
        {
            dfs_sort(u);
        }
    }

    order.push_back(v);
}

bool dfs_transposed(int v, int component)
{
    color[v] = BLACK;
    components[v] = component;

    for (int u : transposed_graph[v])
    {
        if (color[u] == WHITE)
        {
            dfs_transposed(u, component);
        }
    }
}

int main()
{
    std::ifstream file_in("cond.in");
    std::ofstream file_out("cond.out");

    unsigned int n_vertices = 0, n_edges = 0;
    file_in >> n_vertices >> n_edges;

    graph.resize(n_vertices);
    transposed_graph.resize(n_vertices);
    color.resize(n_vertices, WHITE);
    components.resize(n_vertices, -1);


    for (int foo = 0; foo < n_edges; ++foo)
    {
        unsigned int from = 0, to = 0;
        file_in >> from >> to;

        graph[from - 1].push_back(to - 1);
        transposed_graph[to - 1].push_back(from - 1);
    }

    for (int v = 0; v < n_vertices; ++v)
    {
        if (color[v] == WHITE)
        {
            dfs_sort(v);
        }
    }

    std::reverse(order.begin(), order.end());

    color.assign(n_vertices, WHITE);

    int current_component = 1;
    for (int v : order)
    {
        if (color[v] == WHITE)
        {
            dfs_transposed(v, current_component++);
        }
    }

    file_out << current_component - 1 << '\n';
    for (int v : components)
    {
        file_out << v << ' ';
    }

    return 0;
}
