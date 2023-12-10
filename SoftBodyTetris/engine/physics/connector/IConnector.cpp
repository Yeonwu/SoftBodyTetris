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
    return calcDistanceToPosition(pos, p[0] -> getPosition(), p[1] -> getPosition());
}

double IConnector::oldDistanceToPosition( const Position& pos ) const {
    return calcDistanceToPosition(pos, p[0] -> getOldPosition(), p[1] -> getOldPosition());
}
