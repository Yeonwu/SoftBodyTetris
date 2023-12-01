//
//  Acceleration.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/30.
//

#ifndef Acceleration_hpp
#define Acceleration_hpp

#include "Velocity.hpp"
#include "Time.hpp"

class Acceleration {
public:
    double x;
    double y;
    
    Acceleration ( double _x, double _y );
    Velocity operator *(const Time_sec dt);
};


#endif /* Acceleration_hpp */
