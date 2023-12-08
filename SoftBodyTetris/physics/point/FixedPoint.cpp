//
//  FixedPoint.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/03.
//

#include "FixedPoint.hpp"

FixedPoint::FixedPoint( Position _pos ): FixedPoint(_pos, MASS_MAX)  {}
FixedPoint::FixedPoint( Position _pos, Mass _M): pos(_pos), M(_M) {}

Mass FixedPoint::getMass() const {
    return M;
}

Position FixedPoint::getPosition() const {
    return pos;
}

Position FixedPoint::getOldPosition() const {
    return pos;
}

void FixedPoint::setPosition(Position _pos) {}

Velocity FixedPoint::getVelocity() const {
    return Velocity(0, 0);
}

void FixedPoint::setVelocity(Velocity _V) {}

void FixedPoint::update( Time_sec dt ) {}

bool FixedPoint::isMovable() const {
    return false;
}

void FixedPoint::addForce( Force _F ) {}
