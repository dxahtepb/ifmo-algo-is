#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

void count_sort(vector<string> & a, int digit)
{
    vector<int> count((unsigned int) 'z' + 1);

    for (auto & s : a)
    {
        ++count[s[digit]];
    }

    int pos = 0;
    for (char i = 'a'; i <= 'z'; ++i)
    {
        int add_pos = count[i];
        count[i] = pos;
        pos += add_pos;
    }

    vector<string> b(a.size());

    for (auto & s : a)
    {
        char d = s[digit];
        b[count[d]++] = s;
    }

    a = b;
}

void radix_sort(vector<string> & a, int m, int k)
{
    for (int step = 1; step <= k; ++step)
    {
        count_sort(a, m - step);
    }
}

using namespace std;

int main()
{
    ifstream input("radixsort.in");
    ofstream output("radixsort.out");

    int n = 0;
    int m = 0;
    int k = 0;
    input >> n >> m >> k;

    vector<string> a(n);

    for (int i = 0; i < n; ++i)
    {
        input >> a[i];
    }

    radix_sort(a, m, k);

    for (auto & s : a)
    {
        output << s << '\n';
    }

    return 0;
}