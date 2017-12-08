#include <vector>
#include <fstream>
#include <iostream>
#include <exception>

using namespace std;

struct Node
{
    int key;
    Node* children[2];

    Node(int key) : key(key)
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

    Node* search(Node* node, int key)
    {
        if (node == nullptr || node->key == key)
        {
            return node;
        }
        return search(node->children[((key < node->key) ? 0 : 1)], key);
    }

    Node* insert(Node* node, int key)
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

    Node* remove(Node* node, int key)
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

    Node* next(Node* node, int key)
    {
        Node* current = node;
        Node* possible = nullptr;

        while (current != nullptr)
        {
            if (current->key <= key)
            {
                current = current->children[1];
            }
            else
            {
                possible = current;
                current = current->children[0];
            }
        }

        return possible;
    }

    Node* prev(Node* node, int key)
    {
        Node* current = node;
        Node* possible = nullptr;

        while (current != nullptr)
        {
            if (key <= current->key)
            {
                current = current->children[0];
            }
            else
            {
                possible = current;
                current = current->children[1];
            }
        }

        return possible;
    }

public:
    void insert(int key)
    {
        if (!exists(key))
            root = insert(root, key);
    }

    bool exists(int key)
    {
        return search(root, key) != nullptr;
    }

    void remove(int key)
    {
        if (exists(key))
            root = remove(root, key);
    }

    int next(int key)
    {
        Node* next_node = next(root, key);
        if (next_node == nullptr)
        {
            throw exception();
        }
        return next_node->key;
    }

    int prev(int key)
    {
        Node* prev_node = prev(root, key);
        if (prev_node == nullptr)
        {
            throw exception();
        }
        return prev_node->key;
    }

    ~Tree()
    {
        delete root;
    }
};

int main()
{
    ifstream input("bstsimple.in");
    ofstream output("bstsimple.out");

    Tree tree;

    while (!input.eof())
    {
        string operation;
        int key;
        input >> operation >> key;

        if (operation == "insert")
        {
            tree.insert(key);
        }
        else if (operation == "delete")
        {
            tree.remove(key);
        }
        else if (operation == "exists")
        {
            output << (tree.exists(key) ? "true" : "false") << endl;
        }
        else if (operation == "next")
        {
            try
            {
                output << tree.next(key) << endl;
            }
            catch (exception & ex)
            {
                output << "none" << endl;
            }
        }
        else if (operation == "prev")
        {
            try
            {
                output << tree.prev(key) << endl;
            }
            catch (exception & ex)
            {
                output << "none" << endl;
            }
        }
    }

    return 0;
}