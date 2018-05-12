#include <iostream>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <algorithm>
#include <fstream>


const int NO_FLOW = -1;
const int NO_PREV = -1;


struct Edge
{
    int from, to, cap, flow;
    Edge(int from, int to, int cap, int flow)
            : from(from), to(to), cap(cap), flow(flow) {}

    int available_cap() const
    {
        return cap - flow;
    }
};


struct Graph
{
    std::vector< std::vector<int> > adj;
    std::vector<Edge> edges;

    explicit
    Graph(int n)
    {
        adj.resize(n);
    }

    std::vector<int> &operator [] (int idx)
    {
        return adj[idx];
    }

    void add_edge(int from, int to, int cap)
    {
        adj[from].push_back(edges.size());
        edges.emplace_back(from, to, cap, 0);
        adj[to].push_back(edges.size());
        edges.emplace_back(to, from, 0, 0);
    }

    size_t size()
    {
        return adj.size();
    }
};


int64_t push_flow(Graph & graph, int source, int sink)
{
    std::vector<int> queue;

    std::unordered_map<int, int> prev = {{source, NO_PREV}};

    queue.push_back(source);
    int idx = 0;

    while (idx < queue.size())
    {
        int u = queue[idx];
        idx += 1;
        for (auto e : graph[u])
        {
            auto edge = graph.edges[e];

            if (prev.find(edge.to) == prev.end() && edge.available_cap() > 0)
            {
                queue.push_back(edge.to);
                prev.insert({edge.to, e});
            }
        }
    }

    if (prev.find(sink) == prev.end())
    {
        return NO_FLOW;
    }

    std::vector<int> path;
    int curr = sink;
    while (prev[curr] != NO_PREV)
    {
        int e = prev[curr];
        path.push_back(e);
        curr = graph.edges[e].from;
    }

    int64_t flow = std::numeric_limits<int64_t>::max();
    for (auto e : path)
    {
        if (graph.edges[e].available_cap() < flow)
        {
            flow = graph.edges[e].available_cap();
        }
    }

    for (auto e : path)
    {
        graph.edges[e].flow += flow;
        graph.edges[e ^ 1].flow -= flow;
    }

    return flow;
}


int64_t max_flow(Graph & graph)
{
    int64_t total_flow = 0;

    while (true)
    {
        int64_t flow = push_flow(graph, 0, graph.size() - 1);
        if (flow == NO_FLOW)
        {
            break;
        }
        total_flow += flow;
    }
    return total_flow;
}


int main()
{
    std::ifstream inp_file("maxflow.in");
    std::ofstream out_file("maxflow.out");

    int n = 0, m = 0;
    inp_file >> n >> m;

    Graph graph(n);

    for (size_t i = 0; i < m; i++)
    {
        int from = 0, to = 0, cap = 0;
        inp_file >> from >> to >> cap;
        graph.add_edge(from - 1, to - 1, cap);
    }

    out_file << max_flow(graph);

    return 0;
}