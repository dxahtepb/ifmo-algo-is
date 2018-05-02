#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <set>
#include <iostream>
 
 
const int64_t INF = std::numeric_limits<int64_t>::max();
 
 
typedef std::vector< std::vector< std::pair<uint32_t, int32_t> > > Graph;
 
 
std::vector<int64_t>
dijkstra(Graph const &graph, uint32_t start)
{
    std::vector<int64_t> dist(graph.size(), INF);
    std::set< std::pair<int64_t, uint32_t> > queue;
 
    dist[start] = 0;
    queue.insert({0, start});
 
    while (!queue.empty())
    {
        auto min_edge = *queue.begin();
        queue.erase(queue.begin());
 
        auto from = min_edge.second;
 
        for (auto edge : graph[from])
        {
            uint32_t to = edge.first;
            int32_t weight = edge.second;
 
            if (dist[to] > dist[from] + weight)
            {
                queue.erase({dist[to], to});
                dist[to] = dist[from] + weight;
                queue.insert({dist[to], to});
            }
        }
    }
 
    return dist;
}
 
 
int main()
{
    std::ifstream inp_file("pathbgep.in");
    std::ofstream out_file("pathbgep.out");
 
    uint32_t n_vertex = 0, n_edges = 0;
    inp_file >> n_vertex >> n_edges;
 
    Graph graph(n_vertex);
 
    for (size_t i = 0; i < n_edges; ++i)
    {
        uint32_t from = 0, to = 0;
        int32_t weight = 0;
 
        inp_file >> from >> to >> weight;
 
        graph[from - 1].emplace_back(to - 1, weight);
        graph[to - 1].emplace_back(from - 1, weight);
    }
 
    auto dist = dijkstra(graph, 0);
 
    for (auto x : dist)
    {
        out_file << x << ' ';
    }
 
    return 0;
}