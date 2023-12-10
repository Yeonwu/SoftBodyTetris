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
    virtual ~IConnector() = default;
    
    IPoint* getPoint( int idx );
    
    virtual void update() = 0;
    
    virtual double getLength() const = 0;
    
    virtual Force calcForceTo( int idx, int otherIdx ) = 0;
    
    double distanceToPosition( const Position& pos ) const;
    double oldDistanceToPosition( const Position& pos ) const;
};

#endif /* IConnector_hpp */
