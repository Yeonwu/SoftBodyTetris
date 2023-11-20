//
//  ElasticConnector.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/03.
//

#include "ElasticConnector.hpp"

ElasticConnector::ElasticConnector(IPoint* _p0, IPoint * _p1, double _K):
    K(_K)
{
    p[0] = _p0;
    p[1] = _p1;
    
    length = (p[0] -> getPosition() - p[1] -> getPosition()).size();
}

ElasticConnector::ElasticConnector(IPoint* _p0, IPoint * _p1, double _length, double _K):
    length(_length),
    K(_K)
{
    p[0] = _p0;
    p[1] = _p1;
}

Force ElasticConnector::calcForceTo( int idx, int otherIdx ) {
    Position p0Pos = p[idx] -> getPosition();
    Position p1Pos = p[otherIdx] -> getPosition();
    
    double distance = ( p0Pos - p1Pos ).size();
    double forceSize = K * abs( distance - length );
    
    if ( distance > length ) {
        
        Position p0FValue = ( p0Pos - p1Pos ) / distance * forceSize;
        return Force(p0FValue.x, p0FValue.y);
        
    } else if ( distance < length ) {
        Position p0FValue = ( p1Pos - p0Pos ) / distance * forceSize;
        return Force(p0FValue.x, p0FValue.y);
    }
    
    return Force(0, 0);
}

const IPoint* ElasticConnector::getPoint( int idx ) const {
    return p[idx];
}

double ElasticConnector::getLength() const {
    return length;
}