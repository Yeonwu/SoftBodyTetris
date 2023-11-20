//
//  FixedPoint.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/03.
//

#include "FixedPoint.hpp"

FixedPoint::FixedPoint( Position _pos ): pos(_pos) {}

Position FixedPoint::getPosition() const {
    return pos;
}

void FixedPoint::setPosition(Position _pos) {
    pos = _pos;
}

Velocity FixedPoint::getVelocity() const {
    return Velocity(0, 0);
}

void FixedPoint::update( Time_sec dt ) {}

bool FixedPoint::isMovable() const {
    return false;
}

void FixedPoint::addForce( Force _F ) {}