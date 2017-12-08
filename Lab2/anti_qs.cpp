#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

void shuffle(vector<int> & a)
{
    for (int i = 0; i < a.size(); ++i)
    {
        swap(a[i], a[i / 2]);
        for (auto item : a)
        {
            cerr << item << " ";
        }
        cerr << endl;
    }
}

int main()
{
    ifstream input("antiqs.in");
    ofstream output("antiqs.out");

    int n = 0;
    input >> n;

    vector<int> a(n);

    for (int i = 1; i <= n; ++i)
    {
        a[i - 1] = i;
    }

    shuffle(a);

    for (auto item : a)
    {
        output << item << " ";
    }

    return 0;
}