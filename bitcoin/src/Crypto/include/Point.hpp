#pragma once

#include <iostream>
#include <optional>
#include <string>

namespace crypto
{

class Point
{
  public:
    Point(int x, int y, int a, int b);
    Point(std::optional<int> x, std::optional<int> y, int a, int b);
    ~Point() = default;

    friend bool operator==(const Point& lhs, const Point& rhs);
    friend bool operator!=(const Point& lhs, const Point& rhs);
    friend Point operator+(const Point& lhs, const Point& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Point& element);
    
    std::optional<int> X;
    std::optional<int> Y;
    int A;
    int B;

  protected:
    friend bool operator==(const std::optional<int>& lhs, const std::optional<int>& rhs);
    friend bool operator!=(const std::optional<int>& lhs, const std::optional<int>& rhs);
};

} // namespace crypto
