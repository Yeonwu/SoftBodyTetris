//
//  NonElasticConnector.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/07.
//

#ifndef NonElasticConnector_hpp
#define NonElasticConnector_hpp

#include "Types.hpp"
#include "IPoint.hpp"
#include "IConnector.hpp"

class NonElasticConnector: public IConnector{
    IPoint *p[2];
    double length;
    
public:
    NonElasticConnector(IPoint* p0, IPoint* p1);
    NonElasticConnector(IPoint* p0, IPoint* p1, double _length);
    
    const IPoint* getPoint( int idx ) const;
    
    double getLength() const;
    
    Force calcForceTo( int idx, int otherIdx );
};

#endif /* NonElasticConnector_hpp */
