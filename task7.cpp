#include <iostream>
#include <algorithm>

class AVLTree {
    struct Node;
public:
    AVLTree() {
        root_ = nullptr;
    };

    void Insert(int value) {
        if (!Contain(value)) {
            root_ = InsertRecursively(root_, value);
        }
    }

    int GetNext(int value) {
        int min_value = 1000000001;
        Node *temp = root_;
        while (temp != nullptr) {
            if (temp->value > value) {
                min_value = (temp->value < min_value) ? temp->value : min_value;
                temp = temp->left;
            } else if (temp->value < value) {
                temp = temp->right;
            } else {
                min_value = temp->value;
                break;
            }
        }
        return (min_value == 1000000001) ? -1 : min_value;
    }

private:
    struct Node {
        explicit Node(int value) : value(value), left(nullptr), right(nullptr), height(1) {}

        int value;
        Node *left;
        Node *right;
        int height;
    };

    int GetHeight(Node *node) {
        if (node == nullptr)
            return 0;
        else
            return node->height;
    }

    Node *RotateRight(Node *node) {
        Node *temp = node->left;
        Node *temp_right = temp->right;
        temp->right = node;
        node->left = temp_right;
        node->height = (GetHeight(node->left) > GetHeight(node->right)) ? GetHeight(node->left) + 1 :
                       GetHeight(node->right) + 1;
        temp->height = (GetHeight(temp->left) > GetHeight(temp->right)) ? GetHeight(temp->left) + 1 :
                       GetHeight(temp->right) + 1;
        return temp;
    }

    Node *RotateLeft(Node *node) {
        Node *temp = node->right;
        Node *temp_left = temp->left;
        temp->left = node;
        node->right = temp_left;
        node->height = (GetHeight(node->left) > GetHeight(node->right)) ? GetHeight(node->left) + 1 :
                       GetHeight(node->right) + 1;
        temp->height = (GetHeight(temp->left) > GetHeight(temp->right)) ? GetHeight(temp->left) + 1 :
                       GetHeight(temp->right) + 1;
        return temp;
    }

    Node *InsertRecursively(Node *node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }
        if (value > node->value)
            node->right = InsertRecursively(node->right, value);
        else
            node->left = InsertRecursively(node->left, value);

        node->height = (GetHeight(node->left) > GetHeight(node->right)) ? GetHeight(node->left) + 1 :
                       GetHeight(node->right) + 1;

        int balance_value = GetHeight(node->left) - GetHeight(node->right);
        if (balance_value < -1 && value > node->right->value)
            return RotateLeft(node);
        if (balance_value > 1 && value < node->left->value)
            return RotateRight(node);
        if (balance_value > 1 && value > node->left->value) {
            node->left = RotateLeft(node->left);
            return RotateRight(node);
        }
        if (balance_value < -1 && value < node->right->value) {
            node->right = RotateRight(node->right);
            return RotateLeft(node);
        }
        return node;
    }

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

private:
    Node *root_;
};

int main() {
    AVLTree new_tree;
    int number_of_commands;
    std::cin >> number_of_commands;
    char last_command = '\0';
    int last_value = 0;
    for (int i = 0; i < number_of_commands; ++i) {
        char ch;
        int value;
        std::cin >> ch;
        std::cin >> value;
        if (ch == '+' && (last_command == '\0' || last_command == '+')) {
            new_tree.Insert(value);
            last_command = ch;
        } else if (ch == '+' && last_command == '?') {
            new_tree.Insert((value + last_value) % 1000000000);
            last_command = ch;
        } else {
            last_command = ch;
            last_value = new_tree.GetNext(value);
            std::cout << last_value << std::endl;

        }
    }
}
