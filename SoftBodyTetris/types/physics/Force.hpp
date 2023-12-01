//
//  Force.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/30.
//

#ifndef Force_hpp
#define Force_hpp

#include "Acceleration.hpp"
#include "Mass.hpp"

class Force {
public:
    double x;
    double y;
    
    Force( double _x, double _y );
    
    Force operator + ( Force f );
    
    void operator += ( const Force f );
    
    Acceleration operator /( const Mass m );
    
    double size();
};

#endif /* Force_hpp */
