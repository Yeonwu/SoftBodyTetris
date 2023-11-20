//
//  MassPoint.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/10/26.
//

#include "MassPoint.hpp"
#include <stdio.h>

MassPoint::MassPoint( Position _pos, Mass _M ):
    pos(_pos),
    M(_M),
    F({0, 0}),
    V({0, 0})
{}


MassPoint::MassPoint( Position _pos, Mass _M, Velocity _V, Force _F):
    pos(_pos),
    M(_M),
    F(_F),
    V(_V)
{}

Position MassPoint::getPosition() const {
    return pos;
}

void MassPoint::setPosition(Position _pos) {
    pos = _pos;
}

Velocity MassPoint::getVelocity() const {
    return V;
}

void MassPoint::update( Time_sec dt ) {
    updateVelocity( dt );
    updatePosition( dt );
    
    F.x = 0;
    F.y = 0;
}

bool MassPoint::isMovable() const {
    return true;
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
