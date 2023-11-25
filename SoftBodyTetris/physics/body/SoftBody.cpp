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
    IBody(_pos),
    K(_K)
{}

SoftBody& SoftBody::addPoint(IPoint * p) {
    p -> setPosition(p -> getPosition() + pos);
    points.push_back(p);
    
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
