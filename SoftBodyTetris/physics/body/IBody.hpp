//
//  IBody.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/17.
//

#ifndef IBody_hpp
#define IBody_hpp

#include <vector>

#include "Types.hpp"
#include "IPoint.hpp"
#include "IConnector.hpp"

class IBody {
    
protected:
    std::vector<IPoint *> points;
    std::vector<IConnector *> connectors;
    
public:
    IBody();
    void update ( Time_sec dt );
    
    const std::vector<IPoint *>& getPoints() const;
    const std::vector<IConnector *>& getConnectors() const;
    
    friend class ForceAdder;
    friend class Window;
};

#endif /* IBody_hpp */