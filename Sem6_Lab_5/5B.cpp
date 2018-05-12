#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>


typedef std::vector< std::vector<char> > Graph;


bool dfs(Graph const & graph, int idx_n,
         std::vector<int> & match_m, std::vector<char> & busy, int m)
{
    for (int idx_m = 0; idx_m < m; ++idx_m)
    {
        if (graph[idx_n][idx_m] && !busy[idx_m])
        {
            busy[idx_m] = 1;

            if (match_m[idx_m] == -1 ||
                dfs(graph, match_m[idx_m], match_m, busy, m))
            {
                match_m[idx_m] = idx_n;
                return true;
            }
        }
    }
    return false;
}


int max_matching(Graph const & graph, int n, int m)
{
    std::vector<int> match_m(m, -1);
    std::vector<char> busy(m, 0);

    for (int idx_n = 0; idx_n < n; ++idx_n)
    {
        busy.assign(m, 0);
        dfs(graph, idx_n, match_m, busy, m);
    }

    return m - std::count(match_m.begin(), match_m.end(), -1);
}


int main()
{
    std::ifstream inp_file("matching.in");
    std::ofstream out_file("matching.out");

    int n = 0, m = 0, k = 0;
    inp_file >> n >> m >> k;

    Graph graph(n);

    for (auto &v : graph)
    {
        v.resize(m, 0);
    }

    for (int i = 0; i < k; ++i)
    {
        int from = 0, to = 0;
        inp_file >> from >> to;
        graph[from - 1][to - 1] = 1;
    }

    out_file << max_matching(graph, n, m);

    return 0;
}