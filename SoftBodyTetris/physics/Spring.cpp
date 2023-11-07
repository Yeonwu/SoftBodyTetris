//
//  Spring.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/03.
//

#include "Spring.hpp"

Spring::Spring(IPoint* _p0, IPoint * _p1, double _length, double _K):
    length(_length),
    K(_K)
{
    p[0] = _p0;
    p[1] = _p1;
}

void Spring::update() {
    Position p0Pos = p[0] -> getPosition();
    Position p1Pos = p[1] -> getPosition();
    
    double distance = ( p0Pos - p1Pos ).size();
    double forceSize = K * abs( distance - length );
    
    if ( distance > length ) {
        
        Position p0FValue = ( p0Pos - p1Pos ) / distance * forceSize;
        Force p0F(p0FValue.x, p0FValue.y);
        p[0] -> addForce(p0F);
        
        Position p1FValue = ( p1Pos - p0Pos ) / distance * forceSize;
        Force p1F(p1FValue.x, p1FValue.y);
        p[1] -> addForce(p1F);
        
    } else if ( distance < length ) {
        
        Position p0FValue = ( p1Pos - p0Pos ) / distance * forceSize;
        Force p0F(p0FValue.x, p0FValue.y);
        p[0] -> addForce(p0F);
        
        Position p1FValue = ( p0Pos - p1Pos ) / distance * forceSize;
        Force p1F(p1FValue.x, p1FValue.y);
        p[1] -> addForce(p1F);
        
    }
}

const IPoint* Spring::getPoint( int idx ) const {
    return p[idx];
}

double Spring::getLength() const {
    return length;
}
