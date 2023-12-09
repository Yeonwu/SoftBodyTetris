//
//  IPoint.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/30.
//
#include "IPoint.hpp"
#include <vector>

Vec2D calcColisionVelocity(Vec2D pa, Vec2D pb, Vec2D va, Vec2D vb, Mass ma, Mass mb) {
    return va - (pa - pb) * (2*mb / (ma + mb)) * (va - vb).dot(pa - pb) / (pa - pb).dot(pa - pb);
}

std::pair<Vec2D, Vec2D> getColisionVelocity(IPoint* A, IPoint* B) {
    Vec2D pa = A->getPosition();
    Vec2D pb = B->getPosition();
    Vec2D va = A->getVelocity();
    Vec2D vb = B->getVelocity();
    Mass ma = A->getMass();
    Mass mb = B->getMass();

    return std::pair(calcColisionVelocity(pa, pb, va, vb, ma, mb), calcColisionVelocity(pb, pa, vb, va, mb, ma));
}


void IPoint::applyColision(IPoint* A, IPoint* B) {
    auto vNew = getColisionVelocity(A, B);
    
    A->setVelocity({vNew.first.x, vNew.first.y});
    B->setVelocity({vNew.second.x, vNew.second.y});
}
