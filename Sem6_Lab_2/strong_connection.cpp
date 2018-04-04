#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>


typedef std::vector< std::vector<int> > Graph;


enum {WHITE, GRAY, BLACK};


bool dfs_sort(int v, Graph const & graph, std::vector<int> & color, std::vector<int> & order)
{
    color[v] = BLACK;

    for (auto to : graph[v])
    {

        if (color[to] == WHITE)
        {
            dfs_sort(to, graph, color, order);
        }
    }

    order.push_back(v);
}


bool dfs_transposed(int v, int component, Graph const & graph, std::vector<int> & color,
                    std::vector<int> & components)
{
    color[v] = BLACK;
    components[v] = component;

    for (auto to : graph[v])
    {

        if (color[to] == WHITE)
        {
            dfs_transposed(to, component, graph, color, components);
        }
    }
}


uint32_t condensation(Graph const & graph, std::vector<int> & components)
{
    size_t n_vertices = graph.size();

    Graph transposed(n_vertices);

    for (int from = 0; from < n_vertices; ++from)
    {
        for (auto to : graph[from])
        {
            transposed[to].push_back(from);
        }
    }

    std::vector<int> color(n_vertices, WHITE);
    std::vector<int> order;

    for (int v = 0; v < n_vertices; ++v)
    {
        if (color[v] == WHITE)
        {
            dfs_sort(v, graph, color, order);
        }
    }

    std::reverse(order.begin(), order.end());

    color.assign(n_vertices, WHITE);

    uint32_t current_component = 0;

    for (int v : order)
    {
        if (color[v] == WHITE)
        {
            dfs_transposed(v, current_component++, transposed, color, components);
        }
    }

    return current_component;
}

int main()
{
    std::ifstream file_in("cond.in");
    std::ofstream file_out("cond.out");

    unsigned int n_vertices = 0, n_edges = 0;
    file_in >> n_vertices >> n_edges;

    std::vector<int> components(n_vertices);
    std::vector<int> color(n_vertices);
    std::vector<int> order(n_vertices);
    std::vector< std::vector<int> > graph(n_vertices);

    for (int foo = 0; foo < n_edges; ++foo)
    {
        unsigned int from = 0, to = 0;
        file_in >> from >> to;

        graph[from - 1].push_back(to - 1);
    }

    int n_comp = condensation(graph, components);

    file_out << n_comp << '\n';
    for (int v : components)
    {
        file_out << v + 1 << ' ';
    }

    return 0;
}
