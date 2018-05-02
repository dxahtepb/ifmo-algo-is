#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
 
 
typedef std::vector< std::vector< std::pair<int, int> > > Graph;
 
 
int INF = std::numeric_limits<int>::max();
 
 
std::vector< std::vector<int64_t> > floyd_warshall(Graph const & graph)
{
    std::vector< std::vector<int64_t> > dist(graph.size());
 
    for (size_t i = 0; i < graph.size(); ++i)
    {
        dist[i].resize(graph.size(), INF);
 
        dist[i][i] = 0;
 
        for (auto edge : graph[i])
        {
            dist[i][edge.first] = edge.second;
        }
    }
 
    for (size_t k = 0; k < graph.size(); ++k)
    {
        for (size_t i = 0; i < graph.size(); ++i)
        {
            for (size_t j = 0; j < graph.size(); ++j)
            {
                dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
 
    return dist;
}
 
 
int main()
{
    std::ifstream inp_file("pathsg.in");
    std::ofstream out_file("pathsg.out");
 
    uint32_t n_vertex = 0, n_edges = 0;
    inp_file >> n_vertex >> n_edges;
 
    Graph graph(n_vertex);
 
    for (int i = 0; i < n_edges; ++i)
    {
        int u = 0, v = 0, w = 0;
        inp_file >> u >> v >> w;
 
        graph[u - 1].push_back({v - 1, w});
    }
 
    auto dist = floyd_warshall(graph);
 
    for (int i = 0; i < graph.size(); ++i)
    {
        for (int j = 0; j < graph.size(); ++j)
        {
            out_file << dist[i][j] << ' ';
        }
        out_file << std::endl;
    }
 
    return 0;
}