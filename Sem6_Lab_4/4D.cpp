#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_map>


const __int128 INF = std::numeric_limits<__int128>::max();


typedef std::vector< std::vector< std::pair<uint32_t, int64_t> > > Graph;


void get_shortest_paths(Graph const & graph, uint32_t s, std::vector<__int128> & distance,
                        std::vector<bool> & reachable, std::vector<bool> & shortest)
{
    distance[s] = 0;
    reachable[s] = true;
    std::queue<uint32_t> queue;

    for (size_t n = 0; n < graph.size(); ++n)
    {
        for (size_t v = 0; v < graph.size(); ++v)
        {
            for (auto edge : graph[v])
            {
                uint32_t u = edge.first;
                int64_t w = edge.second;

                if (distance[v] != INF && distance[u] > distance[v] + w)
                {
                    distance[u] = distance[v] + w;
                    reachable[u] = true;

                    if (n == graph.size() - 1)
                    {
                        queue.push(u);
                    }
                }
            }
        }
    }

    std::vector<bool> used(graph.size(), false);

    while (!queue.empty())
    {
        auto v = queue.front();
        queue.pop();

        used[v] = true;
        shortest[v] = false;

        for (auto edge : graph[v])
        {
            auto u = edge.first;
            if (!used[u])
            {
                queue.push(u);
            }
        }
    }

    distance[s] = 0;
    reachable[s] = true;
}


int main()
{
    std::ifstream inp_file("path.in");
    std::ofstream out_file("path.out");

    uint32_t n_vertex = 0, n_edges = 0, start_v = 0;
    inp_file >> n_vertex >> n_edges >> start_v;

    Graph graph(n_vertex);

    for (size_t i = 0; i < n_edges; ++i)
    {
        uint32_t u = 0, v = 0;
        int64_t w = 0;
        inp_file >> u >> v >> w;

        graph[u - 1].emplace_back(v - 1, w);
    }

    std::vector<__int128> distances(n_vertex, INF);
    std::vector<bool> reachable(n_vertex, false);
    std::vector<bool> has_shortest(n_vertex, true);

    get_shortest_paths(graph, start_v - 1, distances, reachable, has_shortest);

    for (size_t i = 0; i < graph.size(); ++i)
    {
        if (!reachable[i])
        {
            out_file << '*' << std::endl;
        }
        else if (!has_shortest[i])
        {
            out_file << '-' << std::endl;
        }
        else
        {
            out_file << static_cast<int64_t>(distances[i]) << std::endl;
        }
    }

    return 0;
}
