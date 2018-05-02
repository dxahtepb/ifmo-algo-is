#include <fstream>
#include <vector>
#include <limits>
#include <queue>
#include <unordered_set>
#include <algorithm>
#include <iostream>
 
 
typedef std::vector< std::vector< std::pair<int, int> > > Graph;
 
 
enum {WHITE, GRAY, BLACK};
 
 
bool bfs(int root, Graph const & graph)
{
    std::unordered_set<int> used;
    used.insert(root);
 
    std::queue<int> queue;
    queue.push(root);
 
    while (!queue.empty())
    {
        int u = queue.front();
        queue.pop();
 
        for (auto v : graph[u])
        {
            int to = v.first;
 
            if (used.find(to) == used.end())
            {
                queue.push(to);
                used.insert(to);
            }
        }
    }
 
    return used.size() == graph.size();
}
 
 
bool dfs_sort(int v, Graph const & graph, std::vector<int> & color, std::vector<int> & order)
{
    color[v] = BLACK;
 
    for (auto edge : graph[v])
    {
        int to = edge.first;
 
        if (color[to] == WHITE)
        {
            dfs_sort(to, graph, color, order);
        }
    }
 
    order.push_back(v);
}
 
 
bool dfs_transposed(int v, int component, Graph const & graph, std::vector<int> & color,
                    std::vector<int> & components)
{
    color[v] = BLACK;
    components[v] = component;
 
    for (auto edge : graph[v])
    {
        int to = edge.first;
 
        if (color[to] == WHITE)
        {
            dfs_transposed(to, component, graph, color, components);
        }
    }
}
 
 
uint32_t condensation(Graph const & graph, std::vector<int> & components)
{
    size_t n_vertices = graph.size();
 
    Graph transposed(n_vertices);
 
    for (int from = 0; from < n_vertices; ++from)
    {
        for (auto const & edge : graph[from])
        {
            int to = edge.first;
            int weight = edge.second;
 
            transposed[to].push_back({from, weight});
        }
    }
 
    std::vector<int> color(n_vertices, WHITE);
    std::vector<int> order;
 
    for (int v = 0; v < n_vertices; ++v)
    {
        if (color[v] == WHITE)
        {
            dfs_sort(v, graph, color, order);
        }
    }
 
    std::reverse(order.begin(), order.end());
 
    color.assign(n_vertices, WHITE);
 
    uint32_t current_component = 0;
    for (int v : order)
    {
        if (color[v] == WHITE)
        {
            dfs_transposed(v, current_component++, transposed, color, components);
        }
    }
 
    return current_component;
}
 
 
int64_t find_mst(Graph & graph, uint32_t n, int root)
{
    int64_t res = 0;
 
    std::vector<int> min_edge(n, std::numeric_limits<int>::max());
 
    for (auto const &u : graph)
    {
        for (auto const &edge : u)
        {
            int to = edge.first;
            int weight = edge.second;
 
            min_edge[to] = std::min(weight, min_edge[to]);
        }
    }
 
    for (int from = 0; from < graph.size(); ++from)
    {
        if (from != root)
        {
            res += min_edge[from];
        }
    }
 
    Graph zero_graph(n);
 
    for (int from = 0; from < graph.size(); ++from)
    {
        for (int edge = 0; edge < graph[from].size(); ++edge)
        {
            int to = graph[from][edge].first;
            int weight = graph[from][edge].second;
 
            if (weight == min_edge[to])
            {
                zero_graph[from].push_back({to, weight - min_edge[to]});
            }
        }
    }
 
    if (bfs(root, zero_graph))
    {
        return res;
    }
 
    std::vector<int> new_components(n);
 
    uint32_t n_comp = condensation(zero_graph, new_components);
 
    Graph new_edges(n_comp);
 
    for (int from = 0; from < graph.size(); ++from)
    {
        for (auto const &edge : graph[from])
        {
            int to = edge.first;
            int weight = edge.second;
 
            if (new_components[from] != new_components[to])
            {
                new_edges[new_components[from]].push_back({new_components[to], weight - min_edge[to]});
            }
        }
    }
 
    res += find_mst(new_edges, n_comp, new_components[root]);
 
    return res;
}
 
 
int main()
{
    std::ifstream inp_file("chinese.in");
    std::ofstream out_file("chinese.out");
 
    uint32_t n_vertex = 0, n_edges = 0;
    inp_file >> n_vertex >> n_edges;
 
    Graph graph(n_vertex);
 
    for (int i = 0; i < n_edges; ++i)
    {
        int u = 0, v = 0, w = 0;
        inp_file >> u >> v >> w;
 
        graph[u - 1].push_back({v - 1, w});
    }
 
    if (bfs(0, graph))
    {
        int64_t mst = find_mst(graph, n_vertex, 0);
        out_file << "YES\n" << mst;
    }
    else
    {
        out_file << "NO";
    }
 
    return 0;
}