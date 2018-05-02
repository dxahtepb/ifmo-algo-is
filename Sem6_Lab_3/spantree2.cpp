#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
 
 
struct DSU
{
private:
    unsigned int size;
    std::vector<unsigned int> parents;
    std::vector<unsigned int> set_size;
 
public:
    explicit
    DSU(unsigned int size) : size(size)
    {
        parents.resize(size);
        set_size.resize(size, 0);
        for (size_t i = 0; i < size; ++i)
        {
            parents[i] = i;
        }
    }
 
    void union_set(unsigned int a, unsigned int b)
    {
        unsigned int set_a = get_set(a);
        unsigned int set_b = get_set(b);
 
        if (set_a == set_b)
        {
            return;
        }
 
        if (set_size[set_a] < set_size[set_b])
        {
            std::swap(set_a, set_b);
        }
 
        parents[set_b] = set_a;
        set_size[set_a] += set_size[set_b];
    }
 
    unsigned int get_set(unsigned int a)
    {
        return a == parents[a] ? a : parents[a] = get_set(parents[a]);
    }
};
 
 
int main()
{
    std::ifstream inp_file("spantree2.in");
    std::ofstream out_file("spantree2.out");
 
    std::vector< std::pair< int, std::pair<int, int> > > graph;
 
    unsigned int n = 0, m = 0;
    inp_file >> n >> m;
 
    for (int i = 0; i < m; ++i)
    {
        int from = 0, to = 0, w = 0;
        inp_file >> from >> to >> w;
 
        graph.push_back({w, {from - 1, to - 1}});
    }
 
    DSU components(n);
 
    std::sort(graph.begin(), graph.end());
 
    int mst = 0;
 
    for (auto edge : graph)
    {
        int u = edge.second.first;
        int v = edge.second.second;
        int w = edge.first;
 
        if (components.get_set(u) != components.get_set(v))
        {
            components.union_set(u, v);
 
            mst += w;
        }
    }
 
    out_file << mst;
 
    return 0;
}