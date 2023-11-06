//
//  MassPoint.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/10/26.
//

#include "MassPoint.hpp"
#include <stdio.h>

MassPoint::MassPoint( Mass _M, Position _pos, Velocity _V, Force _F):
    M(_M),
    pos(_pos),
    F(_F),
    V(_V){}

Position MassPoint::getPosition() const {
    return pos;
}

void MassPoint::update( Time_sec dt ) {
    updateVelocity( dt );
    updatePosition( dt );
    
    F.x = 0;
    F.y = 0;
}

void MassPoint::updateVelocity( Time_sec dt ) {
    V += F / M * dt;
}

void MassPoint::updatePosition( Time_sec dt ) {
    // dx = v * dt, millisec to sec
    pos += V * dt;
}

void MassPoint::addForce( Force _F ) {
    F += _F;
}
