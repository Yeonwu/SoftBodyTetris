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

class MassPoint: IPoint {
private:
    Mass M;
    Position pos;
    Force F;
    Velocity V;
    
public:
    MassPoint( Mass _M, Position _pos, Velocity _V, Force _F);
    
    Position getPosition() const;
    void update( Time_sec dt );
    
    void updatePosition( Time_sec dt );
    void updateVelocity( Time_sec dt );
    void addForce( Force _F );
    
};

#endif /* MassPoint_hpp */
