//
//  IBody.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/17.
//

#include "IBody.hpp"

bool isIntersect(Position pos0, Position pos1, Position pos2, Position pos3);

IBody::IBody() {}

const std::vector<IPoint*>& IBody::getPoints() const {
    return points;
}
const std::vector<IConnector*>& IBody::getConnectors() const {
    return connectors;
}

const std::vector<IConnector *>& IBody::getCheckColideConnectors() const {
    return checkColideConnectors;
}

void IBody::update( Time_sec dt ) {
    for (IConnector *c: connectors) {
        c -> update( dt );
    }
    
    for (IPoint *p: points) {
        p -> update( dt );
    }
}

bool IBody::didColide (IBody * b) {
    std::vector<IPoint*>* collidePoints = new std::vector<IPoint*>();
    std::vector<IConnector*>* collideConnectors = new std::vector<IConnector*>();
    
    std::vector<IConnector *> connectors = b -> getCheckColideConnectors();
    
    Position pos_out({-1, -1});
    
    for (IPoint * p: points) {
        int intersectCnt = 0;
        
        Position pos_p = p->getPosition();
        for (IConnector * c: connectors) {
            
            Position pos0 = c->getPoint(0)->getPosition();
            Position pos1 = c->getPoint(1)->getPosition();
            
            if (isIntersect(pos0, pos1, pos_p, pos_out)) {
                intersectCnt += 1;
                collidePoints -> push_back(p);
                collideConnectors -> push_back(c);
            }
        }
        
        if ((intersectCnt % 2) == 1) return true;
    }
    
    return false;
}


int crossProduct( Position a, Position b ) {
    return ( a.x * b.y - a.y * b.x );
}

int direction( Position a, Position b, Position c ) {
    Position ca( a.x - c.x, a.y - c.y );
    Position cb( b.x - c.x, b.y - c.y );

    return (crossProduct(ca, cb) > 0) ? 1 : -1;
}

bool isIntersect(Position pos0, Position pos1, Position pos2, Position pos3) {
    return (
            direction( pos0, pos1, pos2 ) * direction( pos0, pos1, pos3 ) < 0
         && direction( pos2, pos3, pos0 ) * direction( pos2, pos3, pos1 ) < 0
    );
}
