//
//  Position.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/30.
//

#ifndef Position_hpp
#define Position_hpp

#include <cmath>

class Position{
public:
    double x;
    double y;
    
    Position(double _x, double _y);
    
    Position operator +( Position pos ) const;
    void operator +=( const Position pos );
    
    Position operator -( Position pos ) const;
    void operator -=( const Position pos);
    
    Position operator *( double n ) const;
    Position operator *( const Position &other ) const;
    double prod( const Position &other ) const;
    
    Position operator /( double n ) const;
    void operator /=( double n );
    
    
    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;
    bool operator< (const Position& other) const;
    bool operator<=(const Position& other) const;
    bool operator> (const Position& other) const;
    bool operator>=(const Position& other) const;
    
    
    double size() const;
    
    double distanceTo (const Position& other) const;
};

#endif /* Position_hpp */
