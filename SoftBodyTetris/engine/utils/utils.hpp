//
//  utils.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/27.
//

#ifndef utils_hpp
#define utils_hpp

#include "Types.hpp"

Color HSVtoRGB(float H, float S,float V);
Position rotate(Position pos, double angle);
Position rotate(Position pos, double y, double x);
Position constrainDistance(Position& point, Position& anchor, double distance);

#endif /* utils_hpp */
