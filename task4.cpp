#include <iostream>
#include <vector>

class Heap {
public:
    Heap() {
        heap_.resize(0);
    };

    int Insert(const int &element) {
        heap_.push_back(element);
        return SiftUp(heap_.size() - 1);
    }

    void RemoveMax() {
        if (heap_.empty()) {
            std::cout << -1 << std::endl;
            return;
        }
        int max = heap_[0];
        heap_[0] = heap_[heap_.size() - 1];
        heap_.pop_back();
        if (heap_.empty())
            std::cout << 0 << " " << max << std::endl;
        else {
            std::cout << SiftDown(0) << " " << max << std::endl;
        }
    }

    void Print() {
        for (int i = 0; i < heap_.size(); ++i)
            std::cout << heap_[i] << " ";
    }

    int GetSize() {
        return heap_.size();
    }

private:
    int SiftUp(int index) {
        while (index > 0 && heap_[index] > heap_[GetParent(index)]) {
            std::swap(heap_[index], heap_[GetParent(index)]);
            index = GetParent(index);
        }
        return index + 1;
    }

    int SiftDown(int index) {
        while (HasLeftChild(index)) {
            int j = GetLeftChild(index);
            if (HasRightChild(index) &&
                (heap_[GetRightChild(index)] > heap_[GetLeftChild(index)])) {
                j = GetRightChild(index);
            }
            if (heap_[index] >= heap_[j]) {
                break;
            }
            std::swap(heap_[index], heap_[j]);
            index = j;
        }
        return index + 1;
    }

    int GetLeftChild(int index) const {
        return 2 * index + 1;
    }

    int GetRightChild(int index) const {
        return 2 * index + 2;
    }

    int GetParent(int index) const {
        return (index + 1) / 2 - 1;
    }

    bool HasLeftChild(int index) const {
        return 2 * index + 1 < heap_.size();
    }

    bool HasRightChild(int index) const {
        return 2 * index + 2 < heap_.size();
    }

private:
    std::vector<int> heap_;
};

int main() {
    Heap priority_queue;
    int max_size;
    int number_of_queries;
    std::cin >> max_size;
    std::cin >> number_of_queries;
    for (int i = 0; i < number_of_queries; ++i) {
        int type;
        std::cin >> type;
        if (type == 1) {
            priority_queue.RemoveMax();
        } else if (type == 2) {
            int value;
            std::cin >> value;
            if (priority_queue.GetSize() < max_size) {
                std::cout << priority_queue.Insert(value) << std::endl;
            } else {
                std::cout << -1 << std::endl;
            }
        }
    }
    priority_queue.Print();
}