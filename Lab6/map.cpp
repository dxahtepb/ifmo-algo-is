#include <iostream>
#include <vector>
#include <fstream>
 
struct Value
{
    const std::string key;
    std::string value;
 
    Value * next;
 
    explicit
    Value(int hash, std::string key, std::string value) : next(nullptr),
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
 
    int hash(const std::string& s)
    {
        int multiplier = 263;
        int prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = s.size() - 1; i >= 0; --i)
            hash = (hash * multiplier + s[i]) % prime;
        return static_cast<int> (hash);
    }
 
 
    void add(const std::string &key, const std::string &value)
    {
        Value * x = get_value(key);
        if (x != nullptr)
        {
            x->value = value;
            return;
        }
        int h = hash(key);
        Value * node = new Value(h, key, value);
        node->next = table[h % MOD];
        table[h % MOD] = node;
    }
 
    Value * get_value(const std::string &key)
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
 
    std::string get(const std::string &key)
    {
        Value * node = get_value(key);
        return node == nullptr ? "none" : node->value;
    }
 
    void remove(const std::string &key)
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
    std::ifstream input("map.in");
    std::ofstream output("map.out");
    HashSet set;
    while (!input.eof())
    {
        std::string operation;
        std::string key;
        input >> operation >> key;
        if (operation == "put")
        {
            std::string value;
            input >> value;
            set.add(key, value);
        }
        if (operation == "delete")
        {
            set.remove(key);
        }
        if (operation == "get")
        {
            output << set.get(key) << std::endl;
        }
    }
    return 0;
}