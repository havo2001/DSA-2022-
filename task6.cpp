#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>

class SuffixTrieNode {
public:
    SuffixTrieNode *parent = nullptr;
    SuffixTrieNode *suffix_link = nullptr;
    SuffixTrieNode *next = nullptr;
    std::vector<int> index;
    std::unordered_map<char, SuffixTrieNode *> children;
    char ch;
};

class SuffixTrie {
private:
    SuffixTrieNode *root_;
public:
    SuffixTrie(std::vector<std::pair<int, std::string>> input) {
        root_ = new SuffixTrieNode;
        for (int i = 0; i < input.size(); ++i) {
            Insert(input[i].first, input[i].second);
        }
    }

    void Insert(int index, std::string str) {
        int size = str.size();
        SuffixTrieNode *temp = root_;
        for (int i = 0; i < size; ++i) {
            if (temp->children.find(str[i]) != temp->children.end()) {
                temp = temp->children[str[i]];
                continue;
            }
            temp->children[str[i]] = new SuffixTrieNode;
            temp->children[str[i]]->parent = temp;
            temp->children[str[i]]->ch = str[i];
            temp = temp->children[str[i]];
        }
        temp->index.push_back(index);
    }


    SuffixTrieNode *Next(SuffixTrieNode *node, char ch) {
        while (node != root_ && node->children.find(ch) == node->children.end()) {
            node = GetSuffixLink(node);
        }
        if (node == root_ && node->children.find(ch) == node->children.end()) {
            node = root_;
            return node;
        }
        return node->children[ch];
    }

    SuffixTrieNode *GetSuffixLink(SuffixTrieNode *node) {
        if (node->suffix_link == nullptr) {
            if (node->parent == root_ || node == root_)
                node->suffix_link = root_;
            else
                node->suffix_link = Next(GetSuffixLink(node->parent), node->ch);
        }
        return node->suffix_link;
    }

    SuffixTrieNode *GetNext(SuffixTrieNode *node) {
        if (node->next == nullptr) {
            SuffixTrieNode *suffix_link_node = GetSuffixLink(node);
            if (suffix_link_node == root_)
                node->next = root_;
            else
                node->next = suffix_link_node->index.empty() ? GetNext(suffix_link_node) : suffix_link_node;

        }
        return node->next;
    }

    std::vector<int> Suffix(std::string str) {
        int size = str.length();
        std::vector<int> suffix(size, 0);
        SuffixTrieNode *temp = root_;
        for (int i = 0; i < size; ++i) {
            temp = Next(temp, str[i]);
            SuffixTrieNode *copy = temp;
            while (copy != root_) {
                for (int j = 0; j < copy->index.size(); ++j) {
                    if (copy->index[j] <= i)
                        suffix[i - copy->index[j]]++;
                }
                copy = GetNext(copy);
            }
        }
        return suffix;
    }
};

void Solve() {
    std::string pattern;
    std::cin >> pattern;
    std::string str;
    std::cin >> str;
    int pattern_size = pattern.size();
    int str_size = str.size();
    int index = 0;
    std::vector<std::pair<int, std::string>> input;
    for (int i = 0; i < pattern_size; ++i) {
        if (pattern[i] != '?')
            continue;
        else {
            if (index != i)
                input.emplace_back(i - 1, pattern.substr(index, i - index));
            index = i + 1;
        }
    }
    if (pattern_size != index) {
        input.emplace_back(pattern_size - 1, pattern.substr(index, pattern_size - index));
    }
    SuffixTrie suffix_tree(input);
    std::vector<int> suffix = suffix_tree.Suffix(str);
    for (int i = 0; i < suffix.size(); ++i) {
        if (suffix[i] == input.size() && i + pattern_size <= str_size) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    Solve();
    return 0;
}

