//
//  IConnector.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/07.
//

#include <cmath>
#include "IConnector.hpp"

IPoint* IConnector::getPoint( int idx ) {
    return p[idx];
}

void IConnector::update() {
    
    Force p0F = calcForceTo(0, 1);
    Force p1F = calcForceTo(1, 0);
    
    if ( p[0] -> isMovable() ) {
        p[0] -> addForce( p0F );
    }
    
    if ( p[1] -> isMovable() ) {
        p[1] -> addForce( p1F );
    }
}

double calcDistanceToPosition ( const Position& pos, const Position& a, const Position& b) {
    double lineLen = a.distanceTo(b);
    if (lineLen == 0) return a.distanceTo(pos);
    
    Position prjPos = (pos - a) * (b - a);
    double prj = (prjPos.x + prjPos.y) / lineLen;
    
    if (prj < 0) return a.distanceTo(pos);
    if (prj > lineLen) return b.distanceTo(pos);
    return abs( (pos.y - a.y) * (b.x - a.x) - (pos.x - a.x) * (b.y - a.y) ) / lineLen;
}

double IConnector::distanceToPosition( const Position& pos ) const {
    const Position& a = p[0] -> getPosition();
    const Position& b = p[1] -> getPosition();
    
    return calcDistanceToPosition(pos, a, b);
}

double IConnector::oldDistanceToPosition( const Position& pos ) const {
    const Position& a = p[0] -> getOldPosition();
    const Position& b = p[1] -> getOldPosition();
    
    return calcDistanceToPosition(pos, a, b);
}
