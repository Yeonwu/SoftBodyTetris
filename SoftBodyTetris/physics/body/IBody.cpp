//
//  IBody.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/17.
//

#include "IBody.hpp"
#include "MassPoint.hpp"

IBody::IBody(Position _pos): pos(_pos) {
    radius = 0;
}

IBody::~IBody() {
    
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
    
    
    radius = 0;
    Position CoM(0, 0);
    Mass totalM = 0;
    for (IPoint *p: points) {
        p -> update( dt );
        CoM += p->getPosition() * p->getMass();
        totalM += p->getMass();
    }
    
    pos = CoM / (totalM);

    double distance;
    radius = 0;
    for (IPoint *p: points) {
        distance = (p->getPosition() - pos).size();
        if (radius < distance) {
            radius = distance;
        }
    }
}

bool isIntersect( Position pos0, Position pos1, Position pos2, Position pos3 );

DidColideResult IBody::didColide (IBody * b) {
    DidColideResult result = {false, };
    if (radius + b->getRadius() < (pos - b->getPosition()).size()) {
        return result;
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
        
        if ((intersectCnt % 2) == 1) {
            result.didColide = true;
            result.colidePairs.push_back(std::pair(pointIdx, mostCloseConnecterIdx));
        }
        
        pointIdx++;
    }
    
    return result;
}

void IBody::calcColide (IBody * b) {
    DidColideResult colisionCheckResult = didColide(b);
    if (colisionCheckResult.didColide == false) return;
    for (auto& colidePair: colisionCheckResult.colidePairs) {
        IConnector* c = b->getCheckColideConnectors().at(colidePair.second);
        
        IPoint* A = c->getPoint(0);
        IPoint* B = c->getPoint(1);
        
        IPoint* P = getPoints().at(colidePair.first);
        
        Position V = B->getPosition() - A->getPosition();
        Position U = P->getPosition() - A->getPosition();
        
        Position linePos(0, 0);
        // 수선의 발 계산
        if ( U.prod(V) < 0 ) linePos = A->getPosition();
        else if ( U.prod(V) > V.prod(V) ) linePos = B->getPosition();
        else linePos = A->getPosition() + V * (V.prod(U) / V.prod(V));
        
        
        Position moveP = (linePos - P->getPosition());
        moveP = moveP / moveP.size();
        P->setPosition(P->getPosition() + moveP + moveP / moveP.size() / 100);
        
        IPoint* linePoint = new MassPoint(linePos, A->getMass() + B->getMass());
        linePoint->setVelocity((A->getMass()*A->getVelocity() + B->getMass()*B->getVelocity()) / (A->getMass()+B->getMass()));
        
        // Change position & velocity, Elastic collision.
        IPoint::applyColision(P, linePoint);
        
        // Virtual linePoint -> Actual Points
        Position dP = (linePoint->getPosition() - linePos) * 10;
        
        A -> setPosition(A->getPosition() + dP);
        B -> setPosition(B->getPosition() + dP);
        
        A -> setVelocity( A->getMass()/(A->getMass() + B->getMass()) * linePoint->getVelocity() );
        B -> setVelocity( B->getMass()/(A->getMass() + B->getMass()) * linePoint->getVelocity() );
    }
}

void IBody::addForce(Force F) {
    for (auto point: points) {
        point->addForce(F);
    }
}

void IBody::setVelocity(Velocity V) {
    for (auto point: points) {
        point->setVelocity(V);
    }
}


int ccw( Position a, Position b, Position c ) {
    Vec2D ca( a.x - c.x, a.y - c.y );
    Vec2D cb( b.x - c.x, b.y - c.y );

    return (ca.cross(cb) > 0) ? 1 : -1;
}

bool isIntersect(Position pos0, Position pos1, Position pos2, Position pos3) {
    int a = ccw( pos0, pos1, pos2 ) * ccw( pos0, pos1, pos3 );
    int b = ccw( pos2, pos3, pos0 ) * ccw( pos2, pos3, pos1 );
    
    if ( a == 0 && b == 0 ) {
        if (pos0 > pos1) std::swap(pos1, pos0);
        if (pos2 > pos3) std::swap(pos2, pos3);
        
        return pos2 <= pos1 && pos0 <= pos3;
    }
    
    return ( a <= 0 && b <= 0 );
}
