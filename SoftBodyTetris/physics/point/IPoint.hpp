//
//  Point.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/06.
//

#ifndef Point_hpp
#define Point_hpp

#include "Types.hpp"

class IPoint {
public:
    virtual Position getPosition() const = 0;
    virtual void update( Time_sec dt ) = 0;
    virtual bool isMovable() const = 0;
    virtual void addForce( Force _F ) = 0;
};

#endif /* Point_hpp */
