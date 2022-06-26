#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

struct Hole {
    double x;
    double y;
};

bool Clockwise(Hole first, Hole second, Hole third) {
    return ((second.y - first.y) * (third.x - second.x) -
            (second.x - first.x) * (third.y - second.y)) > 0;
}

double Distance(Hole first, Hole second) {
    return sqrt((first.x - second.x) * (first.x - second.x) +
                (first.y - second.y) * (first.y - second.y));
}

static bool Comparator(Hole &first, Hole &second) {
    return (first.x < second.x) || (first.x == second.x && first.y < second.y);
}

double LengthOfFence(std::vector<Hole> &holes) {
    size_t size = holes.size();
    std::vector<Hole> convex_hull(3 * size);
    std::sort(holes.begin(), holes.end(), Comparator);
    int index = 0;

    for (int i = 0; i < size; ++i) {
        while (!Clockwise(convex_hull[index - 2], convex_hull[index - 1], holes[i]) && index >= 2)
            index--;
        convex_hull[index] = holes[i];
        index++;
    }
    for (int i = size - 2, j = index + 1; i >= 0; --i) {
        while (!Clockwise(convex_hull[index - 2], convex_hull[index - 1], holes[i]) && index >= j)
            index--;
        convex_hull[index] = holes[i];
        index++;
    }
    convex_hull.resize(index);

    double ans = 0;
    for (int i = 0; i < convex_hull.size() - 1; ++i) {
        ans += Distance(convex_hull[i], convex_hull[i + 1]);
    }
    return ans;
}

int main() {
    int number_of_holes;
    std::cin >> number_of_holes;
    std::vector<Hole> holes;
    for (int i = 0; i < number_of_holes; ++i) {
        double x;
        double y;
        std::cin >> x;
        std::cin >> y;
        holes.push_back({x, y});
    }
    printf("%lf\n", LengthOfFence(holes));
}
