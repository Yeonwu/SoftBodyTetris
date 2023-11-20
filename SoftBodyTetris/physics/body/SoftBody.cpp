//
//  SoftBody.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/17.
//

#include "SoftBody.hpp"
#include "ElasticConnector.hpp"
#include "FixedPoint.hpp"
#include <vector>

SoftBody::SoftBody(Position _pos, double _K):
    pos(_pos),
    K(_K)
{}

SoftBody& SoftBody::addPoint(IPoint * p) {
    p -> setPosition(p -> getPosition() + pos);
    points.push_back(p);
    
    return *this;
}

SoftBody& SoftBody::connectPoints(int idx1, int idx2) {
    return connectPoints(idx1, idx2, K);
}

SoftBody& SoftBody::connectPoints(int idx1, int idx2, double _K) {
    connectors.push_back(new ElasticConnector(points.at(idx1), points.at(idx2), _K));
    
    return *this;
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

bool SoftBody::didColide (IBody * b) {
    std::vector<IConnector *> connectors = b -> getConnectors();
    
    int intersectCnt = 0;
    Position pos_out({-1, -1});
    
    for (IPoint * p: points) {
        Position pos_p = p->getPosition();
        for (IConnector * c: connectors) {
            
            Position pos0 = c->getPoint(0)->getPosition();
            Position pos1 = c->getPoint(1)->getPosition();
            
            if (isIntersect(pos0, pos1, pos_p, pos_out)) {
                intersectCnt += 1;
            }
        }
    }
    
    return intersectCnt % 2;
}
