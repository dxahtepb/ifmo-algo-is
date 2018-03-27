#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <queue>

int NOT_USED = -1;

std::vector<int> color;
std::vector< std::vector<int> > graph;

bool bfs(int v)
{
    color[v] = 0;

    std::queue<int> queue;
    queue.push(v);

    while (!queue.empty())
    {
        v = queue.front();
        queue.pop();

        for (int u : graph[v])
        {
            if (color[u] == NOT_USED)
            {
                color[u] = color[v] ^ 1;
                queue.push(u);
            }
            if (color[u] == color[v])
            {
                return true;
            }
        }
    }

    return false;
}

int main()
{
    std::ifstream file_in("bipartite.in");
    std::ofstream file_out("bipartite.out");

    unsigned int n_vertices = 0, n_edges = 0;
    file_in >> n_vertices >> n_edges;

    graph.resize(n_vertices);
    color.resize(n_vertices, NOT_USED);


    for (int foo = 0; foo < n_edges; ++foo)
    {
        unsigned int from = 0, to = 0;
        file_in >> from >> to;

        graph[from - 1].push_back(to - 1);
        graph[to - 1].push_back(from - 1);
    }

    for (int i = 0; i < n_vertices; ++i)
    {
        if (color[i] == NOT_USED)
        {
            if (bfs(i))
            {
                file_out << "NO";
                return 0;
            }
        }
    }

    file_out << "YES";

    return 0;
}
