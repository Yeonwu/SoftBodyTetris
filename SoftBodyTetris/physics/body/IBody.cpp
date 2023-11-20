//
//  IBody.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/17.
//

#include "IBody.hpp"

IBody::IBody() {}

const std::vector<IPoint*>& IBody::getPoints() const {
    return points;
}
const std::vector<IConnector*>& IBody::getConnectors() const {
    return connectors;
}

void IBody::update( Time_sec dt ) {
    for (IConnector *c: connectors) {
        c -> update( dt );
    }
    
    for (IPoint *p: points) {
        p -> update( dt );
    }
}
