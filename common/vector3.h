#ifndef VECTOR3_H
#define VECTOR3_H

#include <vector>
#include <algorithm>
#include "../common/vector2.h"

template<class T>
struct vector3 {
  vector3() {x = 0; y = 0; z = 0;};
  vector3(T _x, T _y, T _z) { x = _x; y = _y; z = _z;}
  T x;
  T y;
  T z;
  T manhattanlength() { return abs(x)+abs(y)+abs(z); };
  std::string to_string() { return "("+std::to_string(x)+","+std::to_string(y)+","+std::to_string(z)+") "; }

  vector2<T> xy() { return {x,y}; };
  vector2<T> yz() { return {y,z}; };
  vector2<T> xz() { return {x,z}; };
};

template<class T>
vector3<T> operator +(const vector3<T> &lhs, const vector3<T> &rhs) { return { lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z }; };
template<class T>
vector3<T> operator +=(const vector3<T> &lhs, const vector3<T> &rhs) { return { lhs.x+rhs.x, lhs.y+rhs.y, lhs.z+rhs.z }; };
template<class T>
vector3<T> operator -(const vector3<T> &lhs, const vector3<T> &rhs) { return { lhs.x-rhs.x, lhs.y-rhs.y, lhs.z-rhs.z }; };
template<class T>
vector3<T> operator *(const vector3<T> &lhs, int mult) { return { lhs.x*mult, lhs.y*mult, lhs.z*mult }; };
template<class T>
bool operator ==(const vector3<T> &lhs, const vector3<T> &rhs) { return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z; };

template<class T>
bool operator<(const vector3<T>& a, const vector3<T>& b) { return (a.z==b.z)?((a.y==b.y)?a.x<b.x:a.y<b.y):a.z<b.z;};
template<class T>
bool operator>(const vector3<T>& a, const vector3<T>& b) { return (a.z==b.z)?((a.y==b.y)?a.x>b.x:a.y>b.y):a.z>b.z;};
#endif