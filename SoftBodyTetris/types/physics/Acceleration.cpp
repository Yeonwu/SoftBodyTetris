//
//  Acceleration.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/30.
//

#include "Acceleration.hpp"

Acceleration::Acceleration ( double _x, double _y ): x( _x ), y( _y ) {}

Velocity Acceleration::operator *(const Time_sec dt) {
    return Velocity(x * dt, y * dt);
}

