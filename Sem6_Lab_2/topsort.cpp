#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

enum {WHITE, GRAY, BLACK};

std::vector<int> topsorted;
std::vector<int> color;
std::vector< std::vector<int> > graph;

bool dfs(int v)
{
    color[v] = GRAY;

    for (auto u : graph[v])
    {
        if (color[u] == GRAY)
        {
            return true;
        }
        if (color[u] == WHITE)
        {
            if (dfs(u))
            {
                return true;
            }
        }
    }

    topsorted.push_back(v);
    color[v] = BLACK;

    return false;
}

int main()
{
    std::ifstream file_in("topsort.in");
    std::ofstream file_out("topsort.out");

    unsigned int n_vertices = 0, n_edges = 0;
    file_in >> n_vertices >> n_edges;

    graph.resize(n_vertices);
    color.resize(n_vertices, WHITE);


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
            if (dfs(i))
            {
                file_out << "-1\n";
                return 0;
            }
        }
    }

    std::reverse(topsorted.begin(), topsorted.end());

    for (auto x : topsorted)
    {
        file_out << x + 1 << " ";
    }

    return 0;
}