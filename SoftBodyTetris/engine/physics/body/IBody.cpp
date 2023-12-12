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

void IBody::update() {
    for (IConnector *c: connectors) {
        c -> update();
    }
    
    
    radius = 0;
    Position CoM(0, 0);
    Mass totalM = 0;
    for (IPoint *p: points) {
        p -> update();
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
int ccw( Position a, Position b, Position c );

DidColideResult IBody::didColide (IBody * b) {
    DidColideResult result = {false, };
    
    Position pos_out({-100, -100});
    Position pos_p;
    Position pos_p_old;
    Position pos0;
    Position pos1;
    Position pos0_old;
    Position pos1_old;
    
    int intersectCnt;
    int colideConnecterIdx;
    double minDistance;
    double distance;
    
    int pointIdx, connectorIdx;
    
    for (pointIdx = 0; IPoint * p: points) {
        intersectCnt = 0;
        
        pos_p = p->getPosition();
        pos_p_old = p->getOldPosition();
        
        colideConnecterIdx = -1;
        minDistance = 10000000;
        
        for (connectorIdx = 0; IConnector * c: b -> getCheckColideConnectors()) {
            pos0 = c->getPoint(0)->getPosition();
            pos1 = c->getPoint(1)->getPosition();
            pos0_old = c->getPoint(0)->getOldPosition();
            pos1_old = c->getPoint(1)->getOldPosition();
            
            if (isIntersect(pos0, pos1, pos_p, pos_out)) {
                intersectCnt += 1;
            }
            
            distance = c -> distanceToPosition(pos_p);
            if (minDistance > distance) {
                minDistance = distance;
                colideConnecterIdx = connectorIdx;
            }
            
            connectorIdx++;
        }
        
        if ((intersectCnt % 2) == 1) {
            result.didColide = true;
            result.colidePairs.push_back(std::pair(pointIdx, colideConnecterIdx));
        }
        
        pointIdx++;
    }
    
    return result;
}

void IBody::calcColide (IBody * b) {
    if (radius + b->getRadius() < pos.distanceTo(b->getPosition())) {
        return;
    }
    
    std::vector<IPoint*> targetPoints;
    std::vector<IPoint*> targetOtherPoints;

    for (auto point: points) {
        if (point->getPosition().distanceTo(b->getPosition()) < b->getRadius()) {
            targetPoints.push_back(point);
        }
    }

    for (auto point: targetOtherPoints) {
        if (point->getPosition().distanceTo(pos) < radius) {
            targetOtherPoints.push_back(point);
        }
    }
    
    Vec2D dir;
    for (auto point: targetPoints) {
        for (auto otherPoint: targetOtherPoints) {
            dir = point->getPosition() - otherPoint->getPosition();
            if ( dir.size() < 1 ) {
//                IPoint::applyColision(point, otherPoint);
                dir = dir.norm() * ((1 - dir.size()) / 2);
                point->setPosition(point->getPosition() + dir);
                otherPoint->setPosition(otherPoint->getPosition() - dir);
            }
        }
    }
    
    DidColideResult colisionCheckResult = didColide(b);
    if (colisionCheckResult.didColide == false) return;
    
    for (auto& colidePair: colisionCheckResult.colidePairs) {
        if (colidePair.second == -1) {
            continue;
        }
        
        IConnector* c = b->getCheckColideConnectors().at(colidePair.second);
        
        IPoint* A = c->getPoint(0);
        IPoint* B = c->getPoint(1);
        
        IPoint* P = getPoints().at(colidePair.first);
        
        Position V = B->getPosition() - A->getPosition();
        Position U = P->getPosition() - A->getPosition();
        
        Position linePos(0, 0);
        // 수선의 발 계산
        if ( U.dot(V) < 0 ) linePos = A->getPosition();
        else if ( U.dot(V) > V.dot(V) ) linePos = B->getPosition();
        else linePos = A->getPosition() + V * (V.dot(U) / V.dot(V));
        
        // Set position
        Position moveP = (linePos - P->getPosition());
        moveP = moveP / moveP.size() / 50;
        Position mid = (linePos + P->getPosition()) / 2;
        
        P->setPosition(mid + moveP);
        
        // Virtual linePoint -> Actual Points
        A -> setPosition(A->getPosition() + mid - moveP - linePos);
        B -> setPosition(B->getPosition() + mid - moveP - linePos);
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
    return ((a - c).cross(b - c) > 0) ? 1 : -1;
}

bool isIntersect(Position pos0, Position pos1, Position pos2, Position pos3) {
    int a = ccw( pos0, pos1, pos2 ) * ccw( pos0, pos1, pos3 );
    int b = ccw( pos2, pos3, pos0 ) * ccw( pos2, pos3, pos1 );
    
    if ( a == 0 && b == 0 ) {
        return false;
    }
    
    return ( a < 0 && b < 0 );
}
