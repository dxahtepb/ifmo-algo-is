#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

class Queue
{
    const int MODULO = 65536;

    queue<uint16_t> queue;

public:
    uint32_t get()
    {
        auto result = queue.front();
        queue.pop();
        return result;
    }

    void put(int64_t value)
    {
        queue.push((uint16_t) (value % MODULO));
    }
};

void read_source(ifstream & input, vector<string> & program)
{
    string line;
    while (getline(input, line))
    {
        program.push_back(line);
    }
}

void scan_labels(vector<string> & source, unordered_map<string, int> & labels)
{
    for (int i = 0; i < source.size(); i++)
    {
        if (source[i][0] == ':')
        {
            labels[source[i].substr(1)] = i;
        }
    }
}

void run_program(vector<string> & source, ofstream & output_stream)
{
    Queue queue;
    unordered_map<string, int> labels;
    vector<int64_t> registers(26);
    scan_labels(source, labels);

    int64_t x, y;
    for (int i = 0; i < source.size(); i++)
    {
        string command = source[i];
        switch (command[0])
        {
            case '+':
                x = queue.get();
                y = queue.get();
                queue.put(x + y);
                break;
            case '-':
                x = queue.get();
                y = queue.get();
                queue.put(x - y);
                break;
            case '*':
                x = queue.get();
                y = queue.get();
                queue.put(x * y);
                break;
            case '/':
                x = queue.get();
                y = queue.get();
                queue.put(y != 0 ? x / y : 0);
                break;
            case '%':
                x = queue.get();
                y = queue.get();
                queue.put(y != 0 ? x % y : 0);
                break;
            case '>':
                registers[command[1] - 'a'] = queue.get();
                break;
            case '<':
                queue.put(registers[command[1] - 'a']);
                break;
            case 'P':
                if (command.length() == 1)
                    output_stream << queue.get() << endl;
                else
                    output_stream << registers[command[1] - 'a'] << endl;
                break;
            case 'C':
                if (command.length() == 1)
                    output_stream << (unsigned char) queue.get();
                else
                    output_stream << (unsigned char) registers[command[1] - 'a'];
                break;
            case ':':
                break;
            case 'J':
                i = labels[command.substr(1)];
                break;
            case 'Z':
                if (registers[command[1] - 'a'] == 0)
                {
                    i = labels[command.substr(2)];
                }
                break;
            case 'E':
                if (registers[command[1] - 'a'] == registers[command[2] - 'a'])
                {
                    i = labels[command.substr(3)];
                }
                break;
            case 'G':
                if (registers[command[1] - 'a'] > registers[command[2] - 'a'])
                {
                    i = labels[command.substr(3)];
                }
                break;
            case 'Q':
                i = source.size();
                break;
            default:
                queue.put(atoll(command.c_str()));
                break;
        }
    }
}

int main()
{
    ifstream input("quack.in");
    ofstream output("quack.out");

    vector<string> source;
    read_source(input, source);
    run_program(source, output);

    return 0;
}
