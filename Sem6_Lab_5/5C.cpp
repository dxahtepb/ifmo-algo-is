#include <vector>
#include <fstream>
#include <queue>
#include <limits>
#include <iostream>
#include <list>


typedef std::pair< int64_t, std::list<int> > Decomposition;
const int64_t NO_PATH = -1;


struct Edge
{
    int from, to, number, id;
    int64_t cap, flow;
    Edge(int from, int to, int64_t cap, int64_t flow, int number, int id)
            : from(from), to(to), cap(cap), flow(flow), number(number), id(id) {}

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

    void add_edge(int from, int to, int64_t cap, int number)
    {
        adj[from].push_back(edges.size());
        edges.emplace_back(from, to, cap, 0, number, edges.size());
        adj[to].push_back(edges.size());
        edges.emplace_back(to, from, 0, 0, number, edges.size());
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


void simple_decomposition(Graph & graph, int start,
                          Decomposition & p)
{
    p.first = NO_PATH;
    p.second.clear();

    std::vector<char> used(graph.size());
    int v = start;

    while (!used[v])
    {
        if (v == graph.size() - 1)
        {
            break;
        }

        int edge_id = -1;
        for (auto u : graph[v])
        {
            if (graph.edges[u].flow > 0)
            {
                edge_id = u;
                break;
            }
        }

        if (edge_id == -1)
        {
            p.first = NO_PATH;
            p.second.clear();
            return;
        }

        p.second.push_back(edge_id);
        used[v] = 1;
        v = graph.edges[edge_id].to;
    }

    if (used[v])
    {
        while (graph.edges[p.second.front()].from != v)
        {
            p.second.pop_front();
        }
    }

    int64_t decomp_flow = std::numeric_limits<int64_t>::max();
    for (auto edge_id : p.second)
    {
        if (graph.edges[edge_id].flow < decomp_flow)
        {
            decomp_flow = graph.edges[edge_id].flow;
        }
    }


    for (auto edge_id : p.second)
    {
        graph.edges[edge_id].flow -= decomp_flow;
    }

    p.first = decomp_flow;
}


void full_decomposition(Graph & graph, std::vector<Decomposition> & decompositions,
                        int start)
{
    Decomposition p;
    simple_decomposition(graph, start, p);

    while (p.first != NO_PATH)
    {
        decompositions.emplace_back(p.first, p.second);
        simple_decomposition(graph, start, p);
    }
}


int main()
{
    std::ifstream inp_file("decomposition.in");
    std::ofstream out_file("decomposition.out");

    int n = 0, m = 0;
    inp_file >> n >> m;

    Graph graph(n);

    for (size_t i = 0; i < m; i++)
    {
        int from = 0, to = 0;
        int64_t cap = 0;
        inp_file >> from >> to >> cap;
        graph.add_edge(from - 1, to - 1, cap, i + 1);
    }

    dinic(graph, 0, graph.size() - 1);

    std::vector<Decomposition> decompositions;
    full_decomposition(graph, decompositions, 0);

    out_file << decompositions.size() << std::endl;
    for (auto const & decomp : decompositions)
    {
        out_file << decomp.first << ' ' << decomp.second.size() << ' ';
        for (auto const & edge_id : decomp.second)
        {
            out_file << graph.edges[edge_id].number << ' ';
        }
        out_file << std::endl;
    }

    return 0;
}
