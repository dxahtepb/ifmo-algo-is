#include <fstream>
#include <limits>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
 
 
const int32_t INF = std::numeric_limits<int32_t>::max();
const int64_t NO_EDGE = 1000000000;
 
typedef std::vector< std::vector< std::pair<int32_t, int32_t> > > Graph;
 
 
bool find_neg_cycle(Graph const & graph, int32_t s, std::vector<int32_t> & neg_cycle)
{
    std::vector<int64_t> distances(graph.size(), INF);
    std::vector<int32_t> parents(graph.size(), -1);
 
    distances[s] = 0;
    int32_t cycle_start = -1;
 
    for (size_t n = 0; n < graph.size(); ++n)
    {
        for (size_t from = 0; from < graph.size(); ++from)
        {
            for (auto edge : graph[from])
            {
                int32_t to = edge.first;
                int32_t weight = edge.second;
 
                if (distances[to] > distances[from] + weight)
                {
                    if (n == graph.size() - 1)
                    {
                        cycle_start = to;
                    }
                    distances[to] = distances[from] + weight;
                    parents[to] = from;
                }
            }
        }
    }
 
    if (cycle_start == -1)
    {
        return false;
    }
    else
    {
        for (int i = 0; i < graph.size(); ++i)
        {
            cycle_start = parents[cycle_start];
        }
 
        auto curr = cycle_start;
 
        while (!(curr == parents[cycle_start] && neg_cycle.size() > 1))
        {
            neg_cycle.push_back(curr);
            curr = parents[curr];
        }

        std::reverse(neg_cycle.begin(), neg_cycle.end());
        return true;
    }
}
 
 
int main()
{
    std::ifstream inp_file("negcycle.in");
    std::ofstream out_file("negcycle.out");
 
    uint32_t n_vertex = 0;
    inp_file >> n_vertex;
 
    Graph graph(n_vertex);
 
    for (size_t from = 0; from < n_vertex; ++from)
    {
        for (size_t to = 0; to < n_vertex; ++to)
        {
            int32_t weight = 0;
            inp_file >> weight;
 
            if (weight == NO_EDGE)
            {
                continue;
            }
 
            graph[from].emplace_back(to, weight);
        }
    }
 
    std::vector<int32_t> neg_cycle;

    if (find_neg_cycle(graph, 0, neg_cycle))
    {
        if (!neg_cycle.empty())
        {
            out_file << "YES" << std::endl << neg_cycle.size() << std::endl;
            for (auto u : neg_cycle)
            {
                out_file << u + 1 << ' ';
            }
            out_file << std::endl;
            return 0;
        }
    }
 
    out_file << "NO" << std::endl;
 
    return 0;
}