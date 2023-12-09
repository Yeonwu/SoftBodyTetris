//
//  Types.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/10/26.
//

#ifndef Types_h
#define Types_h

#include <stdint.h>
#include <limits>

#include "Vec2D.hpp"

typedef double Mass;
extern const double MASS_MAX;

typedef double Time_millis;
typedef uint64_t Time_sec;
extern const Time_sec updateTimeGap;
extern const Time_millis dt;

typedef Vec2D Position;
typedef Vec2D Velocity;
typedef Vec2D Force;
typedef Vec2D Acceleration;

#include "Color.hpp"
#include "Renderable.hpp"

#endif /* Types_h */
