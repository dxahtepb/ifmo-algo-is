#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct heap_element {
    int value;
    int number;

    explicit heap_element(int v, int n) : value(v), number(n) {}
    heap_element() : value(0), number(0) {}

    bool operator< (const heap_element& other) const
    {
        return this->value < other.value;
    }

    heap_element& operator= (int other)
    {
        this->value = other;
        return *this;
    }

    bool operator== (int other) const
    {
        return this->number == other;
    }
};

template <typename T>
class priority_queue
{
    vector<T> heap;

    void sift_up(int i)
    {
        while (true)
        {
            int parent = i == 0 ? 0 : (i - 1) / 2;
            if (heap[i] < heap[parent])
            {
                swap(heap[i], heap[parent]);
                i = parent;
            }
            else
                break;
        }
    }

    void sift_down(int i)
    {
        int l = 2 * i + 1;
        int r = 2 * i + 2;
        int smallest = i;

        if (l < heap.size() && heap[l] < heap[i])
            smallest = l;

        if (r < heap.size() && heap[r] < heap[smallest])
            smallest = r;

        if (smallest != i)
        {
            swap(heap[i], heap[smallest]);
            sift_down(smallest);
        }
    }

    int find(int key)
    {
        for (int i = 0; i < heap.size(); i++)
        {
            if (heap[i] == key)
            {
                return i;
            }
        }
    }

public:
    bool extract_min(T& min)
    {
        if (heap.empty())
            return false;
        min = heap[0];
        swap(heap[0], heap[heap.size() - 1]);
        heap.pop_back();
        sift_down(0);
        return true;
    }

    void push(T elem)
    {
        heap.push_back(elem);
        sift_up(heap.size() - 1);
    }

    void decrease_key(int key, int new_value)
    {
        int i = find(key);
        heap[i] = new_value;
        sift_up(i);
    }
};

int main()
{
    ifstream input("priorityqueue.in");
    ofstream output("priorityqueue.out");

    priority_queue<heap_element> queue;
    int line_number = 0;
    while (!input.eof())
    {
        line_number++;
        string operation;
        input >> operation;

        if (operation == "push")
        {
            int key;
            input >> key;
            queue.push(heap_element(key, line_number));
        }
        else if (operation == "extract-min")
        {
            heap_element min_key;
            if (queue.extract_min(min_key))
                output << min_key.value << endl;
            else
                output << "*" << endl;
        }
        else if (operation == "decrease-key")
        {
            int number, new_value;
            input >> number >> new_value;
            queue.decrease_key(number, new_value);
        }
    }

    return 0;
}
