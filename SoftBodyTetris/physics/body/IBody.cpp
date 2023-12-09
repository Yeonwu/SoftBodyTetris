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
int ccw( Position a, Position b, Position c );

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
        Position pos_p_old = p->getOldPosition();
        
        int colideConnecterIdx = -1;
        double minDistance = 10000000;
        
        for (int connectorIdx = 0; IConnector * c: connectors) {
            
            Position pos0 = c->getPoint(0)->getPosition();
            Position pos1 = c->getPoint(1)->getPosition();
            Position pos0_old = c->getPoint(0)->getOldPosition();
            Position pos1_old = c->getPoint(1)->getOldPosition();
            
            if (isIntersect(pos0, pos1, pos_p, pos_out)) {
                intersectCnt += 1;
            }
            
            if (minDistance > c -> distanceToPosition(pos_p)) {
                minDistance = c -> distanceToPosition(pos_p);
                colideConnecterIdx = connectorIdx;
            }
            // 아니면 그냥 이동 경로 - 현재 Connector, 이동 경로 - 과거 Connector 중 하나만 intersect하면 통과한거 아닌가?
            // Old line, position에 왼쪽, New line, position에 오른쪽일 경우 통과했다는 뜻.
            bool oldFlag = isIntersect(pos0, pos1, pos_p, pos_p_old);
            bool newFlag = isIntersect(pos0_old, pos1_old, pos_p, pos_p_old);
            if ( !oldFlag && newFlag) {
                double oldDistance = c -> oldDistanceToPosition(pos_p_old);
                if (minDistance > oldDistance) {
                    minDistance = oldDistance;
                    colideConnecterIdx = connectorIdx;
                }
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
    DidColideResult colisionCheckResult = didColide(b);
    if (colisionCheckResult.didColide == false) return;
    for (auto& colidePair: colisionCheckResult.colidePairs) {
        if (colidePair.second == -1) {
            printf("!!!!\n");
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
        linePos = linePos - moveP;
        
        IPoint* linePoint = new MassPoint(linePos, A->getMass() + B->getMass());
        linePoint->setVelocity((A->getMass()*A->getVelocity() + B->getMass()*B->getVelocity()) / (A->getMass()+B->getMass()));
        
        // Change velocity, Elastic collision.
        IPoint::applyColision(P, linePoint);
        
        // Virtual linePoint -> Actual Points
        A -> setPosition(A->getPosition() - moveP);
        B -> setPosition(B->getPosition() - moveP);
        
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
//        if (pos0 > pos1) std::swap(pos1, pos0);
//        if (pos2 > pos3) std::swap(pos2, pos3);
        
        return false;//pos2 <= pos1 && pos0 <= pos3;
    }
    
    return ( a < 0 && b < 0 );
}
