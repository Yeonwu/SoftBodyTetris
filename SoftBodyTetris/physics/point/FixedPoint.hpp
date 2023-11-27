//
//  FixedPoint.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/03.
//

#ifndef FixedPoint_hpp
#define FixedPoint_hpp

#include "Types.hpp"
#include "IPoint.hpp"

class FixedPoint: public IPoint {
    Position pos;
public:
    FixedPoint( Position _pos );
    
    Mass getMass() const;
    
    Position getPosition() const;
    void setPosition(Position _pos);
    
    Velocity getVelocity() const;
    
    void update( Time_sec dt );
    bool isMovable() const;
    void addForce( Force _F );
};

#endif /* FixedPoint_hpp */
