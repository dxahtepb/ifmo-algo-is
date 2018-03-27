#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <unordered_set>

enum {WHITE, GRAY, BLACK};

std::vector<int> topsorted;
std::vector<int> color;
std::vector< std::unordered_set<int> > graph;

void dfs(int v)
{
    for (auto u : graph[v])
    {
        if (color[u] == WHITE)
        {
            dfs(u);
        }
    }

    topsorted.push_back(v);
    color[v] = BLACK;
}

int main()
{
    std::ifstream file_in("hamiltonian.in");
    std::ofstream file_out("hamiltonian.out");

    unsigned int n_vertices = 0, n_edges = 0;
    file_in >> n_vertices >> n_edges;

    graph.resize(n_vertices);
    color.resize(n_vertices, WHITE);

    for (int i = 0; i < n_edges; ++i)
    {
        unsigned int from = 0, to = 0;
        file_in >> from >> to;

        graph[from - 1].insert(to - 1);
    }

    for (int v = 0; v < n_vertices; ++v)
    {
        if (color[v] == WHITE)
        {
            dfs(v);
        }
    }

    std::reverse(topsorted.begin(), topsorted.end());

    for (auto it = topsorted.begin() + 1; it != topsorted.end(); ++it)
    {
        if (graph[*(it-1)].find(*it) == graph[*it].end())
        {
            file_out << "NO";
            return 0;
        }
    }

    file_out << "YES";

    return 0;
}