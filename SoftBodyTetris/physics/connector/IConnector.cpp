//
//  IConnector.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/07.
//

#include "IConnector.hpp"

void IConnector::update( Time_sec dt ) {
    
    Force p0F = calcForceTo(0, 1);
    Force p1F = calcForceTo(1, 0);
    
    if ( p[0] -> isMovable() ) {
        p[0] -> addForce( p0F );
    }
    
    if ( p[1] -> isMovable() ) {
        p[1] -> addForce( p1F );
    }
}

double IConnector::distanceToPosition( const Position& p ) const {
    const Position& a = getPoint(0) -> getPosition();
    const Position& b = getPoint(1) -> getPosition();
    
    double lineLen = a.distanceTo(b);
    if (lineLen == 0) return a.distanceTo(p);
    
    Position prjPos = (p - a) * (b - a);
    double prj = (prjPos.x + prjPos.y) / lineLen;
    
    if (prj < 0) return a.distanceTo(p);
    if (prj > lineLen) return b.distanceTo(p);
    return abs( (p.y - a.y) * (b.x - a.x) - (p.x - a.x) * (b.y - a.y) ) / lineLen;
}
