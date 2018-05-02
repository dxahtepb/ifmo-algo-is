#include <fstream>
#include <vector>
#include <queue>
#include <limits>
#include <set>
#include <iostream>
 
 
const int64_t INF = std::numeric_limits<int64_t>::max();
 
 
typedef std::vector< std::vector< std::pair<uint32_t, int32_t> > > Graph;
 
 
int64_t
dijkstra_bounded(Graph const & graph, uint32_t start, uint32_t finish)
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
 
    return dist[finish] == INF ? -1 : dist[finish];
}
 
 
int main()
{
    std::ifstream inp_file("pathmgep.in");
    std::ofstream out_file("pathmgep.out");
 
    uint32_t n_vertex = 0, start_v = 0, finish_v = 0;
    inp_file >> n_vertex >> start_v >> finish_v;
 
    Graph graph(n_vertex);
 
    for (size_t from = 0; from < n_vertex; ++from)
    {
        for (size_t to = 0; to < n_vertex; ++to)
        {
            int32_t weight = 0;
            inp_file >> weight;
 
            if (from == to || weight == -1)
            {
                continue;
            }
 
            graph[from].emplace_back(to, weight);
        }
    }
 
    auto dist = dijkstra_bounded(graph, --start_v, --finish_v);
 
    out_file << dist;
 
    return 0;
}