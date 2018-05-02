#include <fstream>
#include <vector>
 
int main()
{
    std::ifstream inp_file("input.txt");
    std::ofstream out_file("output.txt");
 
    std::vector<uint32_t> degrees;
 
    uint32_t n_vertices = 0, n_edges = 0;
    inp_file >> n_vertices >> n_edges;
 
    degrees.resize(n_vertices, 0);
 
    for (int i = 0; i < n_edges; ++i)
    {
        uint32_t u = 0, v = 0;
        inp_file >> u >> v;
 
        degrees[u - 1]++;
        degrees[v - 1]++;
    }
 
    for (uint32_t x : degrees)
    {
        out_file << x << " ";
    }
}