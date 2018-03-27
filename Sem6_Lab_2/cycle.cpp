#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

enum {WHITE, GRAY, BLACK};
int NO_CYCLE = -1;

std::vector<int> parents;
std::vector<int> color;
std::vector< std::vector<int> > graph;

int dfs(int v)
{
    color[v] = GRAY;

    for (int u : graph[v])
    {
        if (color[u] == GRAY)
        {
            parents[u] = v;
            return v;
        }

        if (color[u] == WHITE)
        {
            parents[u] = v;
            int cycle_start = dfs(u);
            if (cycle_start != NO_CYCLE)
            {
                return cycle_start;
            }
        }
    }

    color[v] = BLACK;

    return NO_CYCLE;
}

int main()
{
    std::ifstream file_in("cycle.in");
    std::ofstream file_out("cycle.out");

    unsigned int n_vertices = 0, n_edges = 0;
    file_in >> n_vertices >> n_edges;

    graph.resize(n_vertices);
    color.resize(n_vertices, WHITE);
    parents.resize(n_vertices, -1);


    for (int foo = 0; foo < n_edges; foo++)
    {
        unsigned int from = 0, to = 0;
        file_in >> from >> to;

        graph[from - 1].push_back(to - 1);
    }

    for (int i = 0; i < n_vertices; i++)
    {
        if (color[i] == WHITE)
        {
            int cycle_start = dfs(i);
            if (cycle_start != NO_CYCLE)
            {
                file_out << "YES\n";
                file_out << cycle_start + 1 << ' ';

                std::vector<int> cycle;

                for (int v = parents[cycle_start]; v != cycle_start; v = parents[v])
                {
                    cycle.push_back(v + 1);
                }

                std::reverse(cycle.begin(), cycle.end());

                for (int v : cycle)
                {
                    file_out << v << ' ';
                }

                return 0;
            }
        }
    }

    file_out << "NO\n";

    return 0;
}
