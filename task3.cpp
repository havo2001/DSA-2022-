#include <iostream>
#include <algorithm>

class BinaryTree {
    struct Node;
public:
    BinaryTree() {
        root_ = nullptr;
    };

    bool Contain(const int &value) {
        Node *current = root_;
        if (current == nullptr) {
            return false;
        }
        while (current != nullptr) {
            if (current->value < value) {
                current = current->right;
            } else if (value < current->value) {
                current = current->left;
            } else {
                return true;
            }
        }
        return false;
    };

    void Insert(const int &value) {
        if (!Contain(value)) {
            Node *inserted_node = new Node(value);
            Node *current = root_;
            Node *previous = nullptr;
            while (current != nullptr) {
                previous = current;
                if (value < current->value) {
                    current = current->left;
                } else {
                    current = current->right;
                }
            }
            if (previous == nullptr) {
                root_ = inserted_node;
            } else {
                if (value < previous->value) {
                    previous->left = inserted_node;
                } else {
                    previous->right = inserted_node;
                }
            }
        }
    };

    void PrintRecursively(Node *node) {
        if (node == nullptr)
            return;
        if (node->left == nullptr && node->right == nullptr) {
            std::cout << node->value << " ";
            return;
        }
        if (node->left != nullptr) {
            PrintRecursively(node->left);
        }
        if (node->right != nullptr) {
            PrintRecursively(node->right);
        }
    }

    void PrintLeaves() {
        Node *temp = root_;
        PrintRecursively(temp);
    }

private:
    struct Node {
        explicit Node(int value) : value(value), left(nullptr), right(nullptr) {}

        int value;
        Node *left;
        Node *right;
    };

private:
    Node *root_;
};

int main() {
    BinaryTree new_tree;
    int value;
    while (std::cin >> value) {
        if (value == 0)
            break;
        else {
            new_tree.Insert(value);
        }
    }
    new_tree.PrintLeaves();
}
