#include <vector>
#include <fstream>
#include <queue>
#include <limits>
#include <iostream>
#include <list>


struct Edge
{
    int from, to;
    bool true_edge;
    int64_t cap, flow;
    Edge(int from, int to, int64_t cap, int64_t flow, bool true_edge)
            : from(from), to(to), cap(cap), flow(flow), true_edge(true_edge) {}

    int64_t available_cap() const
    {
        return cap - flow;
    }
};


struct Graph
{
    std::vector< std::vector<int> > adj;
    std::vector<Edge> edges;
    std::vector<int> levels;
    std::vector<int> ptr;

    explicit
    Graph(int n)
    {
        adj.resize(n);
        levels.resize(n);
        ptr.resize(n);
    }

    std::vector<int> &operator [] (int idx)
    {
        return adj[idx];
    }

    void add_edge(int from, int to, int64_t cap)
    {
        adj[from].push_back(edges.size());
        edges.emplace_back(from, to, cap, 0, (from != 0 && to != size() - 1));
        adj[to].push_back(edges.size());
        edges.emplace_back(to, from, 0, 0, 0);
    }

    size_t size() const
    {
        return adj.size();
    }
};


bool bfs(Graph & graph, int source, int sink)
{
    graph.levels.assign(graph.size(), -1);

    std::queue<int> queue;

    queue.push(source);
    graph.levels[source] = 0;

    while (!queue.empty() && graph.levels[sink] == -1)
    {
        int from = queue.front();
        queue.pop();

        for (auto id : graph[from])
        {
            int to = graph.edges[id].to;

            if (graph.levels[to] == -1 && graph.edges[id].available_cap() > 0)
            {
                queue.push(to);
                graph.levels[to] = graph.levels[from] + 1;
            }
        }
    }

    return graph.levels[sink] != -1;
}


int64_t dfs(Graph & graph, int u, int sink, int64_t flow)
{
    if (flow == 0)
    {
        return 0;
    }
    if (u == sink)
    {
        return flow;
    }

    while (graph.ptr[u] < graph[u].size())
    {
        int id = graph[u][graph.ptr[u]];
        int v = graph.edges[id].to;

        if (graph.levels[u] + 1 != graph.levels[v])
        {
            graph.ptr[u]++;
            continue;
        }

        int64_t pushed_flow = dfs(
                graph, v, sink, std::min(flow, graph.edges[id].available_cap())
        );

        if (pushed_flow != 0)
        {
            graph.edges[id].flow += pushed_flow;
            graph.edges[id ^ 1].flow -= pushed_flow;
            return pushed_flow;
        }

        graph.ptr[u]++;
    }

    return 0;
}


int64_t dinic(Graph & graph, int source, int sink)
{
    int64_t max_flow = 0;

    while (true)
    {
        if (!bfs(graph, source, sink))
        {
            break;
        }

        graph.ptr.assign(graph.size(), 0);

        int64_t flow = dfs(graph, source, sink, std::numeric_limits<int64_t>::max());
        while (flow != 0)
        {
            max_flow += flow;
            flow = dfs(graph, source, sink, std::numeric_limits<int64_t>::max());
        }
    }

    return max_flow;
}


bool circulation(Graph & graph)
{
    for (auto edge : graph.edges)
    {
        if (edge.from == 0)
        {
            if (edge.flow < edge.cap)
            {
                return false;
            }
        }
    }
    return true;
}


int main()
{
    std::ifstream inp_file("circulation.in");
    std::ofstream out_file("circulation.out");

    int n = 0, m = 0;
    inp_file >> n >> m;

    Graph graph(n+2);

    for (size_t i = 0; i < m; i++)
    {
        int from = 0, to = 0;
        int64_t min_cap = 0, max_cap = 0;
        inp_file >> from >> to >> min_cap >> max_cap;
        graph.add_edge(0, to, min_cap);
        graph.add_edge(from, to, max_cap-min_cap);
        graph.add_edge(from, graph.size() - 1, min_cap);
    }

    dinic(graph, 0, graph.size() - 1);

    if (circulation(graph))
    {
        out_file << "YES" << std::endl;
        for (size_t id = 0; id < graph.edges.size(); ++id)
        {
            auto edge = graph.edges[id];
            if (edge.true_edge)
            {
                out_file << edge.flow + graph.edges[id-2].cap << std::endl;
            }
        }
    }
    else
    {
        out_file << "NO";
    }

    return 0;
}


