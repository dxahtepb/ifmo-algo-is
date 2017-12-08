#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

struct stack{
    vector<char> st;
    int size = 0;

    explicit stack(int m)
    {
        st.resize(m);
    }

    void push(char value)
    {
        st[++size] = value;
    }

    char pop()
    {
        return st[size--];
    }

    char top()
    {
        return st[size];
    }

    bool empty()
    {
        return size == 0;
    }
};

char inv_bracket(char bracket)
{
    if (bracket == '[')
        return ']';
    if (bracket == '(')
        return ')';
}

bool check_brackets(string sequence)
{
    stack st(sequence.size());

    for (auto & bracket : sequence)
    {
        if (bracket == '(' || bracket == '[')
            st.push(bracket);
        else
            if (!st.empty() && bracket == inv_bracket(st.top()))
                st.pop();
            else
                return false;
    }

    return st.empty();
}

int main()
{
    ifstream input("brackets.in");
    ofstream output("brackets.out");

    string sequence;
    while (getline(input, sequence))
    {
        output << (check_brackets(sequence) ? "YES" : "NO") << '\n';
    }

    return 0;
}