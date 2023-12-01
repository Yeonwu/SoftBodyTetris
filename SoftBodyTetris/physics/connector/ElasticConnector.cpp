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
    
    Vec2D direction = ( p0Pos - p1Pos );
    
    double distance = direction.size();
    double forceSize = K * abs( distance - length );
    
    if ( distance > length ) {
        Vec2D p0FValue = direction*-1 / distance * forceSize - proj(direction, p[idx] -> getVelocity());
        return Force(p0FValue.x, p0FValue.y);
    } else if ( distance < length ) {
        Vec2D p0FValue = direction / distance * forceSize - proj(direction, p[idx] -> getVelocity());
        return Force(p0FValue.x, p0FValue.y);
    }
    
    return Force(0, 0);
}

double ElasticConnector::getLength() const {
    return length;
}
