#include <iostream>
#include <string>
#include <vector>

//KMP using prefix function
void KMP(std::string str, std::string pattern) {
    int size_str = str.size();
    int size_pattern = pattern.size();
    std::vector<int> prefix(size_pattern);
    prefix[0] = 0;
    int j = 0;
    for (int i = 1; i < prefix.size(); ++i) {
        if (pattern[i] == pattern[j]) {
            j++;
            prefix[i] = j;
            continue;
        } else {
            if (j == 0) {
                prefix[i] = 0;
                continue;
            } else {
                j = prefix[j - 1];
            }
        }
    }
    int i = 0;
    j = 0;
    while (i < size_str) {
        if (str[i] == pattern[j]) {
            i++;
            j++;
        }
        if (j == size_pattern) {
            std::cout << i - j << " ";
            j = prefix[j - 1];
        } else if (i < size_str && str[i] != pattern[j]) {
            if (j == 0)
                i++;
            else
                j = prefix[j - 1];
        }
    }
}

int main() {
    std::string pattern;
    std::cin >> pattern;
    std::string str;
    std::cin >> str;
    KMP(str, pattern);
}
