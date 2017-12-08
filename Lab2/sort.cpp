#include <iostream>
#include <fstream>
#include <vector>
 
using namespace std;
 
vector<int> a;
vector<int> tmp;
 
void copy_array(int left, int right)
{
    for (int i = left; i < right; ++i)
    {
        a[i] = tmp[i];
    }
}
 
void merge(int left, int middle, int right)
{
    int i = left;
    int j = middle;
 
    for (int k = left; k < right; ++k) {
        if (j == right || (i < middle && a[i]<=a[j])) {
            tmp[k] = a[i];
            i++;
        } else {
            tmp[k] = a[j];
            j++;
        }
    }
 
    copy_array(left, right);
}
 
void merge_sort(int left, int right)
{
    if (right <= left + 1)
    {
        return;
    }
 
    int middle = (left + right) / 2;
    merge_sort(left, middle);
    merge_sort(middle, right);
    merge(left, middle, right);
}
 
int main()
{
    ifstream input("sort.in");
    ofstream output("sort.out");
 
    int n = 0;
    input >> n;
 
    a.resize(n);
    tmp.resize(n);
 
    for (int i = 0; i < n; ++i)
    {
        input >> a[i];
    }
 
    merge_sort(0, n);
 
    for (auto it : a)
    {
        output << it << " ";
    }
 
    return 0;
}