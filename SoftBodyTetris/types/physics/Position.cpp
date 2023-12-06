//
//  Position.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/30.
//

#include "Position.hpp"

Position::Position(double _x, double _y): x(_x), y(_y)  {}

Position Position::operator +( Position pos ) const {
    pos.x += x;
    pos.y += y;
    return pos;
}

void Position::operator +=( const Position pos ) {
    x += pos.x;
    y += pos.y;
}

Position Position::operator -( Position pos ) const {
    pos.x = x - pos.x;
    pos.y = y - pos.y;
    return pos;
}

void Position::operator -=( const Position pos) {
    x -= pos.x;
    y -= pos.y;
}

Position Position::operator *( double n ) const {
    Position pos( x * n, y * n );
    return pos;
}

Position Position::operator *( const Position &other ) const {
    Position pos( x * other.x, y * other.y );
    return pos;
}

double Position::prod( const Position &other ) const {
    return x * other.x + y * other.y;
}

Position Position::operator /( double n ) const {
    Position pos( x / n, y / n );
    return pos;
}

void Position::operator /=( double n ) {
    x /= n;
    y /= n;
}


bool Position::operator==(const Position& other) const { return (x == other.x && y == other.y); }
bool Position::operator!=(const Position& other) const { return !(*this == other); }
bool Position::operator< (const Position& other) const { return (x < other.x || (x == other.x && y < other.y)); }
bool Position::operator<=(const Position& other) const { return !(other < *this); }
bool Position::operator> (const Position& other) const { return (other < *this); }
bool Position::operator>=(const Position& other) const { return !(*this < other); }


double Position::size() const {
    return std::sqrt( x * x + y * y );
}

double Position::distanceTo (const Position& other) const {
    return (*this - other).size();
}
