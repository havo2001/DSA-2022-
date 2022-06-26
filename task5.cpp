#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <cmath>

const double EPS = 1E-9;
struct Point {
    double x;
    double y;
};

struct Segment {
    Point left;
    Point right;
    int index;

    double get_y(double x) const {
        if (abs(left.x - right.x) < EPS)
            return left.y;
        return left.y + (right.y - left.y) * (x - left.x) / (right.x - left.x);
    }
};

int Orientation(Point first, Point second, Point third) {
    double value = (third.x - first.x) * (second.y - first.y) - (second.x - first.x) * (third.y - first.y);
    if (fabs(value) < EPS)
        return 0;
    else if (value < 0)
        return -1;
    else
        return 1;
}

bool Between(Point first, Point second, Point third) {
    return third.x >= std::min(first.x, second.x) && third.y >= std::min(first.y, second.y)
           && third.x <= std::max(first.x, second.x) && third.y <= std::max(first.y, second.y);
}

bool Intersect(Segment first, Segment second) {
    if ((Orientation(first.left, first.right, second.left) != Orientation(first.left, first.right, second.right))
        && (Orientation(second.left, second.right, first.left) != Orientation(second.left, second.right, first.right)))
        return true;
    if ((Orientation(first.left, first.right, second.left) == 0 && Between(first.left, first.right, second.left)) ||
        (Orientation(first.left, first.right, second.right) == 0 && Between(first.left, first.right, second.right)) ||
        (Orientation(second.left, second.right, first.left) == 0 && Between(second.left, second.right, first.left)) ||
        (Orientation(second.left, second.right, first.right) == 0 && Between(second.left, second.right, first.right)))
        return true;
    return false;
}

bool operator<(const Segment &first, const Segment &second) {
    double x = std::max(std::min(first.left.x, first.right.x), std::min(second.left.x, second.right.x));
    return first.get_y(x) < second.get_y(x) - EPS;
}

struct Stick {
    double x;
    bool is_left;
    int index;

    bool operator<(const Stick &stick) const {
        if (fabs(x - stick.x) > EPS)
            return x < stick.x;
        return is_left > stick.is_left;
    }

    Stick(double x, int is_left, int index) : x(x), is_left(is_left), index(index) {};
};

std::set<Segment>::iterator predecessor(std::set<Segment> &set, std::set<Segment>::iterator it) {
    return it == set.begin() ? set.end() : --it;
}

std::set<Segment>::iterator successor(std::set<Segment> &set, std::set<Segment>::iterator it) {
    return ++it;
}

std::pair<int, int> FindIntersection(std::vector<Segment> &segments) {
    size_t size = segments.size();
    std::vector<Stick> sticks;
    for (int i = 0; i < size; ++i) {
        sticks.emplace_back(std::min(segments[i].left.x, segments[i].right.x), true, i);
        sticks.emplace_back(std::max(segments[i].left.x, segments[i].right.x), false, i);
    }
    std::sort(sticks.begin(), sticks.end());
    std::set<Segment> working_stick;
    std::vector<std::set<Segment>::iterator> it;
    it.resize(size);
    for (int i = 0; i < sticks.size(); ++i) {
        int index = sticks[i].index;
        if (sticks[i].is_left) {
            auto next = working_stick.lower_bound(segments[index]);
            auto prev = predecessor(working_stick, next);
            if (next != working_stick.end() && Intersect(*next, segments[index])) {
                return std::make_pair(next->index + 1, index + 1);
            }
            if (prev != working_stick.end() && Intersect(*prev, segments[index])) {
                return std::make_pair(prev->index + 1, index + 1);
            }
            it[index] = working_stick.insert(next, segments[index]);
        } else {
            auto next = successor(working_stick, it[index]);
            auto prev = predecessor(working_stick, it[index]);

            if (next != working_stick.end() && prev != working_stick.end() && Intersect(*next, *prev))
                return std::make_pair(prev->index + 1, next->index + 1);
            working_stick.erase(it[index]);
        }
    }
    return std::make_pair(-1, -1);
}

int main() {
    int number_of_segments;
    std::cin >> number_of_segments;
    std::vector<Segment> segments;
    for (int i = 0; i < number_of_segments; ++i) {
        Point left{};
        Point right{};
        std::cin >> left.x >> left.y >> right.x >> right.y;
        Segment stick({left, right, i});
        segments.push_back(stick);
    }
    std::pair<int, int> intersection = FindIntersection(segments);
    if (intersection.first == -1 && intersection.second == -1)
        std::cout << "NO" << std::endl;
    else
        std::cout << "YES" << std::endl << intersection.first << " " << intersection.second << std::endl;
}
