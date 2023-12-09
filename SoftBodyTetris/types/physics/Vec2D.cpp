/* Vec2D_hpp */
//
//  Vec2D.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/01.
//

#include <cmath>
#include "Vec2D.hpp"

Vec2D::Vec2D(double _x, double _y): x(_x), y(_y) {}
Vec2D::Vec2D(): Vec2D(0, 0) {}

Vec2D Vec2D::operator +(const Vec2D& other) const { return {x + other.x, y + other.y}; }
Vec2D Vec2D::operator -(const Vec2D& other) const { return {x - other.x, y - other.y}; }
Vec2D Vec2D::operator *(double n) const { return {x * n, y * n}; }
Vec2D Vec2D::operator *(const Vec2D& other) const { return {x * other.x, y * other.y}; }
Vec2D operator *( const double n, Vec2D v ) { return v * n; }
Vec2D Vec2D::operator /(double n) const { return {x / n, y / n}; }

void Vec2D::operator +=(const Vec2D& other) { *this = *this + other; }
void Vec2D::operator -=(const Vec2D& other) { *this = *this - other; }
void Vec2D::operator *=(double n) { *this = *this * n; }
void Vec2D::operator *=(const Vec2D& other) { *this = *this * other; }
void Vec2D::operator /=(double n) { *this = *this / n; }

double Vec2D::dot(const Vec2D& other) const { return x*other.x + y*other.y; }

double Vec2D::cross(const Vec2D& other) const { return ( x * other.y - y * other.x ); }

Vec2D Vec2D::proj(const Vec2D& other) const { return other * this->dot(other) / other.dot(other); }

Vec2D proj(const Vec2D& v, const Vec2D& u) { return v.proj(u); }

double Vec2D::size() const { return std::sqrt(x*x + y*y); }

double Vec2D::distanceTo(const Vec2D& other) const { return (*this - other).size(); }

bool Vec2D::operator==(const Vec2D& other) const { return (x == other.x && y == other.y); }
bool Vec2D::operator!=(const Vec2D& other) const { return !(*this == other); }
bool Vec2D::operator< (const Vec2D& other) const { return (x < other.x || (x == other.x && y < other.y)); }
bool Vec2D::operator<=(const Vec2D& other) const { return !(other < *this); }
bool Vec2D::operator> (const Vec2D& other) const { return (other < *this); }
bool Vec2D::operator>=(const Vec2D& other) const { return !(*this < other); }
