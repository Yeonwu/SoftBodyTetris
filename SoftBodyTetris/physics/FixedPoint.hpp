//
//  FixedPoint.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/03.
//

#ifndef FixedPoint_hpp
#define FixedPoint_hpp

#include "Types.hpp"
#include "IPoint.hpp"

class FixedPoint: IPoint {
    Position pos;
public:
    FixedPoint( Position _pos );
    
    Position getPosition() const;
    void update( Time_sec dt );
};

#endif /* FixedPoint_hpp */
