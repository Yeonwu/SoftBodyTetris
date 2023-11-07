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
    IPoint* p[2];
    double length;
    double K;

public:
    Spring(IPoint* _p1, IPoint * _p2, double _length, double _K);
    
    const IPoint* getPoint( int idx ) const;
    
    double getLength() const;
    
    void update();
};

#endif /* Spring_hpp */
