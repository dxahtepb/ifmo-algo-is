#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct queue
{
    vector<int> q;
    int l = 0;
    int r = 0;

    explicit queue(int size)
    {
        q.resize(size + 1);
    }

    void push(int value)
    {
        q[++r] = value;
    }

    int pop()
    {
        return q[++l];
    }
};

int main()
{
    ifstream input("queue.in");
    ofstream output("queue.out");

    int m = 0;
    input >> m;

    queue q(m);

    for (int i = 0; i < m; ++i)
    {
        string command;
        input >> command;

        if (command == "+")
        {
            int x = 0;
            input >> x;
            q.push(x);
        }
        else if (command == "-")
        {
            output << q.pop() << '\n';
        }
    }

    return 0;
}