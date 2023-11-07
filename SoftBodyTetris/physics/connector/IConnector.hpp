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

class IConnector {
protected:
    IPoint *p[2];
    
public:
    
    virtual const IPoint* getPoint( int idx ) const = 0;
    
    virtual double getLength() const = 0;
    
    virtual Force calcForceTo( int idx, int otherIdx ) = 0;
    
    void update();
};

#endif /* IConnector_hpp */
