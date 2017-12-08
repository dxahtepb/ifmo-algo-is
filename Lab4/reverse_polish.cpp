#include <vector>
#include <fstream>

using namespace std;

struct stack{
    vector<int> st;
    int size = 0;

    explicit stack(int m)
    {
        st.resize(m);
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

int eval(int a, char op, int b)
{
    if (op == '+')
        return a + b;
    if (op == '-')
        return a - b;
    if (op == '*')
        return a * b;
}

int main()
{
    ifstream input("postfix.in");
    ofstream output("postfix.out");

    string expression;
    getline(input, expression);

    stack acc(expression.size());

    for (auto & ch : expression)
    {
        if (ch == ' ')
            continue;
        if (isdigit(ch))
            acc.push(ch - '0');
        else
            acc.push(eval(acc.pop(), ch, acc.pop()));
    }

    output << acc.pop();

    return 0;
}