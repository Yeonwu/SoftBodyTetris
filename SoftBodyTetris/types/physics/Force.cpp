//
//  Force.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/30.
//

#include "Force.hpp"
#include <cmath>

Force::Force( double _x, double _y ): x( _x ), y( _y ) {}

Force Force::operator + ( Force f ) {
    f.x += x;
    f.y += y;
    return f;
}

void Force::operator += ( const Force f ) {
    x += f.x;
    y += f.y;
}


double Force::size() {
    return std::sqrt( x * x + y * y );
}

Force Force::operator * ( const double n ) {
    return {x * n, y * n};
}

Acceleration Force::operator /( const Mass m ) {
    return Acceleration(x / m, y / m);
}
