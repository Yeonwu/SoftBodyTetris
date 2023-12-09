//
//  SoftBody.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/17.
//

#ifndef SoftBody_hpp
#define SoftBody_hpp

#include <vector>
#include "IPoint.hpp"
#include "FixedPoint.hpp"
#include "IConnector.hpp"
#include "IBody.hpp"
#include "Types.hpp"

class SoftBody: public IBody {
    std::vector<FixedPoint> shapePoints;
    double K;
    
public:
    SoftBody(Position _pos, double _K);
    
    void update () override;
    
    SoftBody& addPoint(IPoint * p);
    SoftBody& connectPoints(int idx1, int idx2);
    SoftBody& connectPoints(int idx1, int idx2, bool checkColide);
    SoftBody& connectPoints(int idx1, int idx2, double _K);
    SoftBody& connectPoints(int idx1, int idx2, bool checkColide, double _K );
};

#endif /* SoftBody_hpp */
