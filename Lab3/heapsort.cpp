#include <fstream>
#include <vector>
#include <iostream>

using namespace std;

void heapify(vector<int> & a, int i, int end)
{
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    int largest = 0;

    if (l <= end && a[l] > a[i])
        largest = l;
    else
        largest = i;

    if (r <= end && a[r] > a[largest])
        largest = r;

    if (largest != i)
    {
        swap(a[i], a[largest]);
        heapify(a, largest, end);
    }
}

void build_heap(vector<int> & a)
{
    for (int i = a.size() / 2; 0 <= i; --i)
    {
        heapify(a, i, a.size()-1);
    }
}

void heap_sort(vector<int> & a)
{
    build_heap(a);

    for (int end = a.size() - 1; 0 < end; )
    {
        swap(a[0], a[end]);
        --end;
        heapify(a, 0, end);
    }
}

int main()
{
    ifstream input("sort.in");
    ofstream output("sort.out");

    int n = 0;
    input >> n;

    vector<int> a(n);

    for (int i = 0; i < n; ++i)
    {
        input >> a[i];
    }

    heap_sort(a);

    for (auto & item : a)
    {
        output << item << " ";
    }

    return 0;
}