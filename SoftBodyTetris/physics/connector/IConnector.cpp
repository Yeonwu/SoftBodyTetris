//
//  IConnector.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/07.
//

#include "IConnector.hpp"

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
