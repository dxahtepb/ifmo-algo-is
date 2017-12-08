#include <fstream>
#include <vector>

using namespace std;

int turtle(vector<vector<int>> & a, int h, int w) {
    for (int i = h-1; i >= 0; i--) {
        for (int j = 0; j < w; j++) {
            int down_value = 0, left_value = 0;
            if (i != h-1) {
                down_value = a[i+1][j];
            }
            if (j != 0) {
                left_value = a[i][j-1];
            }
            a[i][j] += (left_value > down_value ? left_value : down_value);
        }
    }
    return a[0][w-1];
}

int main() {
    ios_base::sync_with_stdio(false);
    ifstream fin;
    fin.open("turtle.in");
    int h, w;
    fin >> h >> w;
    vector<vector<int>> a;
    int foo;
    for (int i = 0; i < h; i++) {
        a.emplace_back(vector<int>());
        for (int j = 0; j < w; j++) {
            fin >> foo;
            a[i].push_back(foo);
        }
    }
    fin.close();

    int ans = turtle(a, h, w);

    ofstream fout;
    fout.open("turtle.out");
    fout << ans;
    fout.close();

    return 0;
}