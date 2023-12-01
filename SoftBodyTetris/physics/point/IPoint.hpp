//
//  IPoint.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/30.
//

#ifndef IPoint_hpp
#define IPoint_hpp

#include "Types.hpp"

class IPoint: public Renderable {
public:
    
    virtual ~IPoint() = default;
    
    virtual Mass getMass() const = 0;
    
    virtual Position getPosition() const = 0;
    virtual void setPosition(Position _pos) = 0;
    
    virtual Velocity getVelocity() const = 0;
    virtual void setVelocity(Velocity _V) = 0;
    
    virtual void update( Time_sec dt ) = 0;
    virtual bool isMovable() const = 0;
    virtual void addForce( Force _F ) = 0;
    
    static void applyColision(IPoint* A, IPoint* B);
};

#endif /* IPoint_hpp */
