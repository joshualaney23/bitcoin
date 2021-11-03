#pragma once

#include <iostream>
#include <string>

namespace crypto
{

class Point
{
  public:
    Point(int x, int y, int a, int b);
    ~Point() = default;

    friend bool operator==(const Point& lhs, const Point& rhs);
    friend bool operator!=(const Point& lhs, const Point& rhs);
    friend Point operator+(const Point& other);
    // friend Point operator-(const Point& other);
    // friend Point operator*(const Point& other);
    // // Note: Bitwise OR is commandeered for the power operator
    // friend Point operator^(const int& power);
    // friend Point operator/(const Point& other);
    friend std::ostream& operator<<(std::ostream& os, const Point& element);
    
    int X;
    int Y;
    int A;
    int B;
};

} // namespace crypto
