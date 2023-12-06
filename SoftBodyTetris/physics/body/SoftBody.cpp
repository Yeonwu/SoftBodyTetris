//
//  SoftBody.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/17.
//

#include "SoftBody.hpp"
#include "ElasticConnector.hpp"
#include "FixedPoint.hpp"
#include "utils.hpp"
#include <vector>

SoftBody::SoftBody(Position _pos, double _K):
    IBody(_pos),
    K(_K)
{}

void SoftBody::update ( Time_sec dt ) {
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
    
    // 회전 각도 계산
    double A = 0.f, B = 0.f;
    for (int idx = 0; idx < shapePoints.size(); idx++)
    {
        Vec2D curShape = points.at(idx)->getPosition() - pos;
        Vec2D idealShape = shapePoints.at(idx).getPosition();
        
        A += curShape.dot(idealShape);
        B += curShape.cross(idealShape);
    }
    double angle = -atan2(B, A);

    // 모양에 맞추기
    for (int idx = 0; idx < shapePoints.size(); idx++)
    {
        Position target = pos + rotate(shapePoints.at(idx).getPosition(), angle);
        Position diff = (target - points.at(idx)->getPosition()) * K;
        points.at(idx)->addForce({diff.x, diff.y});
    }
}

SoftBody& SoftBody::addPoint(IPoint * p) {
    
    points.push_back(p);
    shapePoints.push_back({p->getPosition() - pos});
    
    return *this;
}

SoftBody& SoftBody::connectPoints(int idx1, int idx2) {
    return connectPoints(idx1, idx2, true, K);
}

SoftBody& SoftBody::connectPoints(int idx1, int idx2, double _K) {
    return connectPoints(idx1, idx2, true, _K);
}

SoftBody& SoftBody::connectPoints(int idx1, int idx2, bool checkColide) {
    return connectPoints(idx1, idx2, checkColide, K);
}

SoftBody& SoftBody::connectPoints(int idx1, int idx2, bool checkColide, double _K) {
    ElasticConnector* ec = new ElasticConnector(points.at(idx1), points.at(idx2), _K);
    
    if (checkColide) {
        checkColideConnectors.push_back(ec);
    }
    
    connectors.push_back(ec);
    
    return *this;
}
