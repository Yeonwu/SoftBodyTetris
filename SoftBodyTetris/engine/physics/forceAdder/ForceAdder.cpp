//
//  ForceAdder.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/17.
//

#include "ForceAdder.hpp"

const double G = 500;
const double DampingC = 4;

void ForceAdder::addForce(IPoint & p, Force & F) {
    p.addForce(F);
}

void ForceAdder::addForce(IBody & b, Force & F) {
    for (IPoint * p: b.points) {
        addForce(*p, F);
    }
}

void ForceAdder::addGravity(IPoint & p) {
    Force gravity = Force(0, G * p.getMass());
    addForce(p, gravity);
}

void ForceAdder::addGravity(IBody & b) {
    for (IPoint* p: b.getPoints()) {
        addGravity(*p);
    }
}

void ForceAdder::addDamping(IPoint & p) {
    Vec2D dampingVal = p.getVelocity() * -DampingC;
    Force damping = Force(dampingVal.x, dampingVal.y);
    addForce(p, damping);
}

void ForceAdder::addDamping(IBody & b) {
    for (IPoint * p: b.points) {
        addDamping(*p);
    }
}
