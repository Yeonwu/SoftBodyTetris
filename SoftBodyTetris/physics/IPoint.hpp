//
//  Point.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/06.
//

#ifndef Point_hpp
#define Point_hpp

#include "Types.hpp"

class IPoint {
    virtual Position getPosition() const = 0;
    virtual void update(Time_sec dt) = 0;
};

#endif /* Point_hpp */
