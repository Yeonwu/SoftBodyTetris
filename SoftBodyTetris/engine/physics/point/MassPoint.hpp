//
//  MassPoint.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/10/26.
//

#ifndef MassPoint_hpp
#define MassPoint_hpp

#include "Types.hpp"
#include "IPoint.hpp"

class MassPoint: public IPoint {
private:
    Mass M;
    Position oldPos;
    Position pos;
    Force F;
    Velocity V;
    
public:
    MassPoint( Position _pos, Mass _M );
    MassPoint( Position _pos, Mass _M, Velocity _V, Force _F);
    
    Mass getMass() const;
    
    Position getPosition() const;
    Position getOldPosition() const;
    void setPosition(Position _pos);
    void setOldPosition(Position _pos);
    
    Velocity getVelocity() const;
    void setVelocity(Velocity _V);
    
    void update();
    bool isMovable() const;
    
    void updatePosition();
    void updateVelocity();
    
    void addForce( Force _F );
    Force getForce ();
};

#endif /* MassPoint_hpp */
