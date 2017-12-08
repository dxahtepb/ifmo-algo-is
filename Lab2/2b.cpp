#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct runner {
    int place;
    string name;
    string country;
};

vector<runner> a;
vector<runner> tmp;

void inline copy_runner_a_tmp(int i)
{
    a[i].name = tmp[i].name;
    a[i].place = tmp[i].place;
    a[i].country = tmp[i].country;
}

void inline copy_runner_tmp_a(int i, int j)
{
    tmp[i].name = a[j].name;
    tmp[i].place = a[j].place;
    tmp[i].country = a[j].country;
}

void copy_array(int left, int right)
{
    for (int i = left; i < right; ++i)
    {
        a[i] = tmp[i];
    }
}

bool compare_runner(int i, int j)
{
    return a[i].country <= a[j].country;
}

void merge(int left, int middle, int right)
{
    int i = left;
    int j = middle;

    for (int k = left; k < right; ++k) {
        if (j == right || (i < middle && compare_runner(i, j)))
        {
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
    ifstream input("race.in");
    ofstream output("race.out");

    int n = 0;
    input >> n;

    a.resize(n);
    tmp.resize(n);

    string inp_country;
    string inp_runner;

    for (int i = 0; i < n; ++i)
    {
        input >> inp_country >> inp_runner;
        a[i].name = inp_runner;
        a[i].place = i+1;
        a[i].country = inp_country;
    }

    merge_sort(0, n);

    string curr_country = "";

    for (int i = 0; i < n; i++)
    {
        if (curr_country != a[i].country)
        {
            curr_country = a[i].country;
            output << "=== " << a[i].country << " ===" << endl;
        }
        output << a[i].name << endl;
    }

    return 0;
}