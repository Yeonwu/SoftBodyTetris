//
//  Vec2D.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/01.
//

#ifndef Vec2D_hpp
#define Vec2D_hpp
#include "Position.hpp"
#include "Velocity.hpp"

class Vec2D {
public:
    double x;
    double y;
    
    Vec2D();
    Vec2D(double _x, double _y);
    Vec2D(Position pos);
    Vec2D(Velocity V);
    
    Vec2D operator +(const Vec2D& other) const;
    Vec2D operator -(const Vec2D& other) const;
    Vec2D operator *(double n) const;
    Vec2D operator /(double n) const;
    
    double dot(const Vec2D& other) const;
    double cross(const Vec2D& other) const;
    double size() const;
    Vec2D proj(const Vec2D& other) const;
};

Vec2D proj(const Vec2D& v, const Vec2D& u);

#endif /* Vec2D_hpp */
