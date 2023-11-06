//
//  Spring.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/03.
//

#ifndef Spring_hpp
#define Spring_hpp

#include "Types.hpp"
#include "MassPoint.hpp"

class Spring {
    MassPoint* p[2];
    double length;
    double K;

public:
    Spring(MassPoint* _p1, MassPoint * _p2, double _length, double _K);
    
    const MassPoint* getMassPoint( int idx ) const;
    
    double getLength() const;
    
    void update();
};

#endif /* Spring_hpp */
