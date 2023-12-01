//
//  Velocity.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/30.
//

#include "Velocity.hpp"

Velocity::Velocity( double _x, double _y ): x(_x), y(_y) {}

Velocity Velocity::operator +( Velocity v ) const {
    v.x += x;
    v.y += y;
    return v;
}
void Velocity::operator +=( const Velocity v ) {
    x += v.x;
    y += v.y;
}

Position Velocity::operator *( const Time_sec dt ) const {
    return { x * dt, y * dt };
}

Velocity operator *( const double n, Velocity v ) {
    return { v.x * n, v.y * n };
}

Velocity Velocity::operator /( const double n ) const {
    return { x / n, y / n };
}

double Velocity::size() {
    return std::sqrt( x * x + y * y );
}
