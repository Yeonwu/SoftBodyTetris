//
//  ForceAdder.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/17.
//

#include "ForceAdder.hpp"

const double G = 5000;
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
    Force gravity = Force(0, G);
    addForce(p, gravity);
}

void ForceAdder::addGravity(IBody & b) {
    Force gravity = Force(0, G);
    addForce(b, gravity);
}


void ForceAdder::addDamping(IPoint & p) {
    Position DampingVal = p.getVelocity() * -DampingC;
    Force Damping = Force(DampingVal.x, DampingVal.y);
    addForce(p, Damping);
}

void ForceAdder::addDamping(IBody & b) {
    for (IPoint * p: b.points) {
        addDamping(*p);
    }
}
