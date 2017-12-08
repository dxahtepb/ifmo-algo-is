#include <vector>
#include <fstream>
 
using namespace std;
 
struct stack{
    vector<int> st;
    int size = 0;
 
    explicit stack(int m)
    {
        st.resize(m + 1);
    }
 
    void push(int value)
    {
        st[++size] = value;
    }
 
    int pop()
    {
        return st[size--];
    }
};
 
int main()
{
    ifstream input("stack.in");
    ofstream output("stack.out");
 
    int m = 0;
    input >> m;
 
    stack a(m);
 
    for (int i = 0; i < m; ++i)
    {
        string command;
        input >> command;
 
        if (command == "+")
        {
            int x = 0;
            input >> x;
            a.push(x);
        }
        else if (command == "-")
        {
            output << a.pop() << '\n';
        }
    }
 
    return 0;
}