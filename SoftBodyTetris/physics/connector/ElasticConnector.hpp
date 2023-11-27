//
//  ElasticConnector.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/03.
//

#ifndef ElasticConnector_hpp
#define ElasticConnector_hpp

#include "Types.hpp"
#include "IPoint.hpp"
#include "IConnector.hpp"

class ElasticConnector: public IConnector {
    double length;
    double K;

public:
    ElasticConnector(IPoint* _p0, IPoint * _p1, double _K);
    ElasticConnector(IPoint* _p0, IPoint * _p1, double _length, double _K);
    
    double getLength() const;
    
    Force calcForceTo( int idx, int otherIdx );
};

#endif /* ElasticConnector_hpp */
