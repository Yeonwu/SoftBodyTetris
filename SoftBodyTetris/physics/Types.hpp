//
//  Types.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/10/26.
//

#ifndef Types_h
#define Types_h

#include <cmath>
#include <stdint.h>

typedef uint64_t Time_millis;
typedef double Time_sec;

typedef double Mass;

class Position {
public:
    double x;
    double y;
    
    Position(double _x, double _y): x(_x), y(_y) {}
    
    Position operator +( Position pos ) const {
        pos.x += x;
        pos.y += y;
        return pos;
    }
    
    void operator +=( const Position pos ) {
        x += pos.x;
        y += pos.y;
    }
    
    Position operator -( Position pos ) const {
        pos.x -= x;
        pos.y -= y;
        return pos;
    }
    void operator -=( const Position pos) {
        x -= pos.x;
        y -= pos.y;
    }
    
    Position operator *(double n) const {
        Position pos( x * n, y * n );
        return pos;
    }
    
    Position operator /(double n) const {
        Position pos( x / n, y / n );
        return pos;
    }
    
    double size() {
        return std::sqrt( x * x + y * y );
    }
};

class Velocity {
public:
    double x;
    double y;
    
    Velocity( double _x, double _y ): x( _x ), y( _y ) {}
    
    Velocity operator +( Velocity v ) const {
        v.x += x;
        v.y += y;
        return v;
    }
    void operator +=( const Velocity v ) {
        x += v.x;
        y += v.y;
    }
    
    Position operator *( const Time_sec dt ) const {
        return { x * dt, y * dt };
    }
    
    double size() {
        return std::sqrt( x * x + y * y );
    }
    
};

class Acceleration {
public:
    double x;
    double y;
    
    Acceleration ( double _x, double _y ): x( _x ), y( _y ) {}
    
    Velocity operator *(const Time_sec dt) {
        return Velocity(x * dt, y * dt);
    }
};

class Force {
public:
    double x;
    double y;
    
    Force( double _x, double _y ): x( _x ), y( _y ) {}
    
    Force operator + ( Force f ) {
        f.x += x;
        f.y += y;
        return f;
    }
    
    void operator += ( const Force f ) {
        x += f.x;
        y += f.y;
    }
    
    Acceleration operator /( const Mass m ) {
        return Acceleration(x / m, y / m);
    }
    
    double size() {
        return std::sqrt( x * x + y * y );
    }
};

#endif /* Types_h */
