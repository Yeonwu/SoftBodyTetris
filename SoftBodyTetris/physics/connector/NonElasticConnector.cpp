//
//  NonElasticConnector.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/07.
//

#include "NonElasticConnector.hpp"

NonElasticConnector::NonElasticConnector(IPoint* p0, IPoint* p1) {
    length = (p0 -> getPosition() - p1 -> getPosition()).size();
    
    
}

NonElasticConnector::NonElasticConnector(IPoint* p0, IPoint* p1, double _length): length(_length)
{
    p[0] = p0;
    p[1] = p1;
}

const IPoint* NonElasticConnector::getPoint( int idx ) const {
    return p[idx];
}

double NonElasticConnector::getLength() const {
    return length;
}

Force NonElasticConnector::calcForceTo( int idx, int otherIdx ) {
//    Position p0Pos = p[idx] -> getPosition();
//    Position p1Pos = p[otherIdx] -> getPosition();
//
//    if (length > ( p0Pos - p1Pos ).size()) {
//        return Force( 0, 0 );
//    }
//
//    Force p0F = p[idx] -> getForce();
//
//    Position Tdir = p1Pos - p0Pos;
//
//    Position TValue = Tdir * ((p0F.x * Tdir.x + p0F.y * Tdir.y) / pow(Tdir.size(), 2));
//
//    return Force( TValue.x, TValue.y);
    return Force(0, 0);
}

