//
//  IConnector.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/07.
//

#ifndef IConnector_hpp
#define IConnector_hpp

#include "Types.hpp"
#include "IPoint.hpp"

class IConnector: public Renderable {
protected:
    IPoint *p[2];
    
public:
    
    IPoint* getPoint( int idx );
    
    virtual double getLength() const = 0;
    
    virtual Force calcForceTo( int idx, int otherIdx ) = 0;
    
    double distanceToPosition( const Position& pos ) const;
    double oldDistanceToPosition( const Position& pos ) const;
    
    void update( Time_sec dt );
};

#endif /* IConnector_hpp */
