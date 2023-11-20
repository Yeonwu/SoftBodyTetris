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
    Position pos;
    Force F;
    Velocity V;
    
public:
    MassPoint( Position _pos, Mass _M );
    MassPoint( Position _pos, Mass _M, Velocity _V, Force _F);
    
    Position getPosition() const;
    void setPosition(Position _pos);
    
    Velocity getVelocity() const;
    
    void update( Time_sec dt );
    bool isMovable() const;
    
    void updatePosition( Time_sec dt );
    void updateVelocity( Time_sec dt );
    void addForce( Force _F );
};

#endif /* MassPoint_hpp */