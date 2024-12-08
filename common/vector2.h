#ifndef VECTOR2_H
#define VECTOR2_H

#include <vector>
#include <unordered_set>
#include <algorithm>

template <class T>
struct vector2 {
    vector2(T _x, T _y) {
        x = _x;
        y = _y;
    }
    T x;
    T y;
    T manhattanlength() { return abs(x) + abs(y); };
    std::string to_string() { return "(" + std::to_string(x) + "," + std::to_string(y) + ") "; }
};

template <class T>
vector2<T> operator+(const vector2<T> &lhs, const vector2<T> &rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y}; };
template <class T>
vector2<T> operator-(const vector2<T> &lhs, const vector2<T> &rhs) { return {lhs.x - rhs.x, lhs.y - rhs.y}; };
template <class T>
vector2<T> operator*(const vector2<T> &lhs, int mult) { return {lhs.x * mult, lhs.y * mult}; };
template <class T>
bool operator==(const vector2<T> &lhs, const vector2<T> &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; };
template <class T>
bool operator<(const vector2<T> &a, const vector2<T> &b) {
    if (a.y == b.y) return a.x < b.x;
    return a.y < b.y;
};
template <class T>
bool operator>(const vector2<T> &a, const vector2<T> &b) {
    if (a.y == b.y) return a.x > b.x;
    return a.y > b.y;
};

namespace std {
template <class T>
struct std::hash<vector2<T>> {
    std::size_t operator()(const vector2<T> &k) const { return hash<long long>()(((long long)k.x) ^ (((long long)k.y) << 32)); };
};
}  // namespace std

template <class T>
std::vector<vector2<T>> lerp(vector2<T> min, vector2<T> max, vector2<T> ignore) {
    std::vector<vector2<T>> res;
    int xmod = (min.x < max.x) ? 1 : -1;
    int ymod = (min.y < max.y) ? 1 : -1;
    for (int xx = min.x; xx != (max.x + xmod); xx += xmod)
        for (int yy = min.y; yy != (max.y + ymod); yy += ymod)
            if (ignore.x != xx || ignore.y != yy) res.push_back(vector2<T>{xx, yy});
    return res;
};

template <class T>
std::vector<vector2<T>> lerp(vector2<T> min, vector2<T> max) {
    std::vector<vector2<T>> res;
    int xmod = (min.x < max.x) ? 1 : -1;
    int ymod = (min.y < max.y) ? 1 : -1;
    for (T xx = min.x; xx != (max.x + xmod); xx += xmod)
        for (T yy = min.y; yy != (max.y + ymod); yy += ymod) res.push_back(vector2<T>{xx, yy});
    return res;
};
#endif