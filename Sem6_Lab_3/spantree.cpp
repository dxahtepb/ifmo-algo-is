#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <cassert>
#include <limits>
 
 
struct Point
{
    int x, y;
    unsigned int ind;
 
    Point(int x, int y, unsigned int ind) : x(x), y(y), ind(ind)
    {}
 
    Point(std::initializer_list<int> list)
    {
        assert(list.size() == 3);
        x = *list.begin();
        y = *(list.begin() + 1);
        ind = static_cast<unsigned int> (*(list.begin() + 2));
    }
 
    bool operator != (const Point & other)
    {
        return ind != other.ind;
    }
 
    bool operator == (const Point & other)
    {
        return ind == other.ind;
    }
};
 
 
double get_length(Point a, Point b)
{
    return  (b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y);
}
 
 
int main()
{
    std::ifstream inp_file("spantree.in");
    std::ofstream out_file("spantree.out");
 
    std::vector< Point > graph;
 
    unsigned int n = 0;
    inp_file >> n;
 
    for (int i = 0; i < n; ++i)
    {
        int x = 0, y = 0;
        inp_file >> x >> y;
 
        graph.push_back({x, y, i});
    }
 
    double mst = 0;
 
    std::vector<double> dist(n, std::numeric_limits<double>::max());
    std::vector<bool> used(n, false);
 
    dist[0] = 0;
 
    for (int i = 0; i < n; ++i)
    {
        int v = -1;
 
        for (int j = 0; j < n; ++j)
        {
            if (!used[j] && (v == -1 || dist[j] < dist[v]))
            {
                v = j;
            }
        }
 
        used[v] = true;
 
        for (int j = 0; j < n; ++j)
        {
            double len = get_length(graph[j], graph[v]);
 
            if (!used[j] && dist[j] > len)
            {
                dist[j] = len;
            }
        }
    }
 
    for (auto x : dist)
    {
        mst += sqrt(x);
    }
 
    out_file << std::setprecision(15) << mst;
 
    return 0;
}