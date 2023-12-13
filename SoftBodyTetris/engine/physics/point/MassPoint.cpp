//
//  MassPoint.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/10/26.
//

#include "MassPoint.hpp"

MassPoint::MassPoint( Position _pos, Mass _M, Velocity _V, Force _F):
    pos(_pos),
    oldPos(_pos),
    M(_M),
    F(_F),
    V(_V)
{}

MassPoint::MassPoint( Position _pos, Mass _M ): MassPoint(_pos, _M, {0, 0}, {0, 0}) {}

Mass MassPoint::getMass() const {
    return M;
}

Position MassPoint::getPosition() const {
    return pos;
}

Position MassPoint::getOldPosition() const {
    return oldPos;
}

void MassPoint::setPosition(Position _pos) {
    oldPos = pos;
    pos = _pos;
}

void MassPoint::setOldPosition(Position _pos) {
    oldPos = _pos;
}

Velocity MassPoint::getVelocity() const {
    return (pos - oldPos) / dt;
}

void MassPoint::setVelocity(Velocity _V) {
    setPosition(_V * dt + pos);
}

void MassPoint::update() {
    updateVelocity();
    updatePosition();
    
    F.x = 0;
    F.y = 0;
}

bool MassPoint::isMovable() const {
    return true;
}

void MassPoint::updateVelocity() {
    V += F / M * dt;
}

void MassPoint::updatePosition() {
    Position curPos = pos;
    pos = 2*curPos - oldPos + F / M * dt * dt;
    oldPos = curPos;
//    oldPos = pos;
//    pos += V * dt;
}

void MassPoint::addForce( Force _F ) {
    F += _F;
}

Force MassPoint::getForce () {
    return F;
}
