//
//  IBody.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/17.
//

#include "IBody.hpp"
#include "MassPoint.hpp"

int crossProduct( Position a, Position b );
int direction( Position a, Position b, Position c );
bool isIntersect( Position pos0, Position pos1, Position pos2, Position pos3 );

IBody::IBody(Position _pos): pos(_pos) {
    radius = 0;
}

Position IBody::getPosition() const {
    return pos;
}

double IBody::getRadius() const{
    return radius;
}

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
    
    double distance;
    radius = 0;
    for (IPoint *p: points) {
        p -> update( dt );
        
        distance = (p->getPosition() - pos).size();
        if (radius < distance) {
            radius = distance;
        }
    }
}

std::pair<int, int> IBody::didColide (IBody * b) {
    if (radius + b->getRadius() < (pos - b->getPosition()).size()) {
        return std::pair(-1, -1);
    }
    
    std::vector<IConnector *> connectors = b -> getCheckColideConnectors();
    
    Position pos_out({-1, -1});
    
    for (int pointIdx = 0; IPoint * p: points) {
        int intersectCnt = 0;
        
        Position pos_p = p->getPosition();
        
        int mostCloseConnecterIdx = -1;
        double minDistance = 10000000;
        
        for (int connectorIdx = 0; IConnector * c: connectors) {
            
            Position pos0 = c->getPoint(0)->getPosition();
            Position pos1 = c->getPoint(1)->getPosition();
            
            if (isIntersect(pos0, pos1, pos_p, pos_out)) {
                intersectCnt += 1;
            }
            
            if (minDistance > c -> distanceToPosition(pos_p)) {
                minDistance = c -> distanceToPosition(pos_p);
                mostCloseConnecterIdx = connectorIdx;
            }
            
            connectorIdx++;
        }
        
        if ((intersectCnt % 2) == 1) return std::pair(pointIdx, mostCloseConnecterIdx);
        
        pointIdx++;
    }
    
    return std::pair(-1, -1);
}

IPoint* IBody::calcColide (IBody * b) {
    std::pair colisionCheckResult = didColide(b);
    if (colisionCheckResult.first == -1) return NULL;
    
    IConnector* c = b->getConnectors().at(colisionCheckResult.second);
    
    IPoint* A = c->getPoint(0);
    IPoint* B = c->getPoint(1);
    
    IPoint* P = getPoints().at(colisionCheckResult.first);
    
    Position V = B->getPosition() - A->getPosition();
    Position U = P->getPosition() - A->getPosition();

    Position linePos(0, 0);
    
    if ( U.prod(V) < 0 ) linePos = A->getPosition();
    else if ( U.prod(V) > V.prod(V) ) linePos = B->getPosition();
    else linePos = A->getPosition() + V * (V.prod(U) / V.prod(V));
    
    return new MassPoint(linePos, A->getMass() + B->getMass());
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
