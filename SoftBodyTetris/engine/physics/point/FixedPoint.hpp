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
    Mass M;
public:
    FixedPoint( Position _pos );
    FixedPoint( Position _pos, Mass _M);
    
    Mass getMass() const;
    
    Position getPosition() const;
    Position getOldPosition() const;
    void setPosition(Position _pos);
    void setOldPosition(Position _pos);
    
    Velocity getVelocity() const;
    void setVelocity(Velocity _V);
    
    void update();
    bool isMovable() const;
    void addForce( Force _F );
    Force getForce();
};

#endif /* FixedPoint_hpp */
