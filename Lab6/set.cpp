#include <iostream>
#include <vector>
#include <fstream>
#include <memory>

struct Value
{
    const int hash;
    const int key;
    int value;

    Value * next;

    explicit
    Value(int hash, int key, int value) : next(nullptr), hash(hash),
                                          key(key), value(value) {}

//    Value() : next(nullptr), hash(0),
//              key(0), value(0) {}
};

struct HashSet
{
//    const unsigned int MOD = 200001;
    const unsigned int MOD = 96557;
    std::vector<Value *> table;

    HashSet()
    {
        table.resize(MOD);
    }

    int hash(int x)
    {
        x = x ^ (x >> 16);
        return x;
    }

    void add(int key)
    {
        if (exists(key))
        {
            return;
        }
        int h = hash(key);
        Value * node = new Value(h, key, key);
        node->next = table[h % MOD];
        table[h % MOD] = node;
    }

    Value * get(int key)
    {
        Value * node = table[hash(key) % MOD];
        while (node != nullptr)
        {
            if (node->key == key)
            {
                return node;
            }
            node = node->next;
        }
        return nullptr;
    }

    bool exists(int key)
    {
        return (get(key) != nullptr);
    }

    void remove(int key)
    {
        int h = hash(key);
        Value * node = table[h % MOD];
        Value * prev_node = nullptr;
        while (node != nullptr)
        {
            if (node->key == key)
            {
                if (prev_node == nullptr)
                {
                    table[h % MOD] = node->next;
                }
                else
                {
                    prev_node->next = node->next;
                    node->next = nullptr;
                }
                return;
            }
            prev_node = node;
            node = node->next;
        }
    }
};


int main()
{
    std::ifstream input("set.in");
    std::ofstream output("set.out");
    HashSet set;
    while (!input.eof())
    {
        std::string operation;
        int key;
        input >> operation >> key;
        if (operation == "insert")
        {
            set.add(key);
        }
        if (operation == "delete")
        {
            set.remove(key);
        }
        if (operation == "exists")
        {
            output << (set.exists(key) ? "true" : "false") << std::endl;
        }
    }
    return 0;
}