#include <iostream>
#include <vector>
#include <fstream>
 
 
struct Node
{
    std::string key;
    Node* children[2];
 
    Node(std::string key) : key(key)
    {
        children[0] = children[1] = nullptr;
    }
 
    ~Node()
    {
        delete children[0];
        delete children[1];
    }
};
 
class Tree
{
    Node* root = nullptr;
 
    int size = 0;
 
    Node* search(Node* node, std::string &key)
    {
        if (node == nullptr || node->key == key)
        {
            return node;
        }
        return search(node->children[((key < node->key) ? 0 : 1)], key);
    }
 
    Node* insert(Node* node, std::string &key)
    {
        if (node == nullptr)
        {
            return new Node(key);
        }
        node->children[((key < node->key) ? 0 : 1)] =
                insert(node->children[((key < node->key) ? 0 : 1)], key);
        return node;
    }
 
    int children_count(Node* node)
    {
        int count = 0;
        for (int i = 0; i < 2; i++)
        {
            if (node->children[i] != nullptr)
            {
                count++;
            }
        }
        return count;
    }
 
    Node* remove(Node* node, std::string &key)
    {
        if (node == nullptr)
        {
            return node;
        }
        if (node->key != key)
        {
            node->children[((key < node->key) ? 0 : 1)] =
                    remove(node->children[((key < node->key) ? 0 : 1)], key);
        }
        else
        {
            int count = children_count(node);
            if (count < 2)
            {
                node = node->children[((node->children[0] != nullptr) ? 0 : 1)];
            }
            else
            {
                Node* min_from_right_subtree = minimum(node->children[1]);
                node->key = min_from_right_subtree->key;
                node->children[1] = remove(node->children[1], node->key);
            }
        }
        return node;
    }
 
    Node* minimum(Node* node)
    {
        if (node->children[0] == nullptr)
        {
            return node;
        }
        return minimum(node->children[0]);
    }
 
    std::vector<std::string> trav;
 
    void make_trav(Node * v)
    {
        if (v == nullptr)
        {
            return;
        }
        make_trav(v->children[0]);
        trav.push_back(v->key);
        make_trav(v->children[1]);
    }
public:
    void insert(std::string &key)
    {
        if (!exists(key))
        {
            root = insert(root, key);
            size++;
        }
    }
 
    bool exists(std::string &key)
    {
        return search(root, key) != nullptr;
    }
 
    void remove(std::string &key)
    {
        if (exists(key))
        {
            root = remove(root, key);
            size--;
        }
    }
 
    int get_size()
    {
        return size;
    }
 
    std::vector<std::string> traversal()
    {
        trav.resize(0);
        make_trav(root);
        return trav;
    }
 
    ~Tree()
    {
        delete root;
    }
};
 
struct Value
{
    const std::string key;
    Tree * tree;
 
    Value * next;
 
    explicit
    Value(int hash, std::string key, std::string value) : next(nullptr),
                                                          key(key)
    {
        tree = new Tree();
        tree->insert(value);
    }
};
 
struct MultiMap
{
    const unsigned int MOD = 96557;
    std::vector<Value *> table;
 
    MultiMap()
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
 
    void add(const std::string &key, std::string &value)
    {
        Value * x = get_value(key);
        if (x != nullptr)
        {
            x->tree->insert(value);
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
 
    std::vector<std::string> get(const std::string &key)
    {
        Value * node = get_value(key);
        if (node == nullptr)
        {
            return std::vector<std::string>();
        }
        return node->tree->traversal();
    }
 
    void remove(const std::string &key, std::string &value)
    {
        int h = hash(key);
        Value * node = table[h % MOD];
        Value * prev_node = nullptr;
        while (node != nullptr)
        {
            if (node->key == key)
            {
                node->tree->remove(value);
                if (node->tree->get_size() == 0)
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
            }
            prev_node = node;
            node = node->next;
        }
    }
 
    void remove_all(const std::string &key)
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
                    delete node->tree;
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
    std::ifstream input("multimap.in");
    std::ofstream output("multimap.out");
    MultiMap map;
    while (!input.eof())
    {
        std::string operation;
        std::string key;
        input >> operation >> key;
        if (operation == "put")
        {
            std::string value;
            input >> value;
            map.add(key, value);
        }
        if (operation == "delete")
        {
            std::string value;
            input >> value;
            map.remove(key, value);
        }
        if (operation == "deleteall")
        {
            map.remove_all(key);
        }
        if (operation == "get")
        {
            std::vector<std::string> vector = map.get(key);
            output << vector.size();
            for (std::string s : vector)
            {
                output << " " << s;
            }
            output << std::endl;
        }
    }
    return 0;
}