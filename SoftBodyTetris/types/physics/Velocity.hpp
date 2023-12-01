//
//  Velocity.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/30.
//

#ifndef Velocity_hpp
#define Velocity_hpp

#include "Time.hpp"
#include "Position.hpp"

class Velocity {
public:
    double x;
    double y;
    
    Velocity( double _x, double _y );
    
    Velocity operator +( Velocity v ) const;
    void operator +=( const Velocity v );
    
    Position operator *( const Time_sec dt ) const;
    
    Velocity operator /( const double n ) const;
    double size();
    
};

Velocity operator *( const double n, Velocity v );


#endif /* Velocity_hpp */
