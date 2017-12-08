#include <fstream>
#include <random>

using namespace std;

int * a;

random_device rd;  //Will be used to obtain a seed for the random number engine
mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()

void swap (int & a, int & b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

int partition(int left, int right, int * il)
{
    uniform_int_distribution<> dis(left, right);
    int rand_pivot = dis(gen);
//    int rand_pivot = (left + right) / 2;
    swap(a[right], a[rand_pivot]);
    int key = a[right];
    int i = left - 1;
    for (int j = left; j <= right - 1; ++j)
    {
        if (a[j] <= key)
        {
            ++i;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[right]);
    *il = i + 1;
    while (a[(*il)--] == key) {}
    (*il) += 2;
    return i + 1;
}


int order_statistic(int left, int right, int i)
{
    while (true)
    {
        int ql;
        int q = partition(left, right, &ql);
        int k = q - left + 1;
        int kl = ql - left + 1;
        if ((i >= kl) && (i <= k))
        {
            return a[q];
        }
        if (i < k)
        {
            right = ql - 1;
        }
        else
        {
            left = q + 1;
            i -= k;
        }
    }
}

void generate_array(int n, int A, int B, int C,
                    int a_1, int a_2)
{
    a = new int[n + 1];
    a[1] = a_1;
    a[2] = a_2;

    for (int i = 3; i <= n; ++i)
    {
        a[i] = A*a[i - 2] + B*a[i - 1] + C;
    }
}

int main()
{
    ifstream input("kth.in");
    ofstream output("kth.out");

    int n = 0;
    int k = 0;
    input >> n >> k;

    int A = 0;
    int B = 0;
    int C = 0;
    int a_1 = 0;
    int a_2 = 0;

    input >> A >> B >> C >> a_1 >> a_2;

    generate_array(n, A, B, C, a_1, a_2);

    output << order_statistic(1, n, k);
    return 0;
}