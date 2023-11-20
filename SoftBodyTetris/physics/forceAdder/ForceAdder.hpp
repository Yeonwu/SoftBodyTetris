//
//  ForceAdder.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/17.
//

#ifndef ForceAdder_hpp
#define ForceAdder_hpp

#include "Types.hpp"
#include "MassPoint.hpp"
#include "SoftBody.hpp"

class ForceAdder {
private:
    static void addForce(IPoint & p, Force & F);
    static void addForce(IBody & b, Force & F);
public:
    static void addGravity(IPoint & p);
    static void addGravity(IBody & b);
    
    static void addDamping(IPoint & p);
    static void addDamping(IBody & b);
};

#endif /* ForceAdder_hpp */
