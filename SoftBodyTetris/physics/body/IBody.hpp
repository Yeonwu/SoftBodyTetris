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

class IBody: public Renderable {
    
protected:
    Position pos;
    std::vector<IPoint *> points;
    std::vector<IConnector *> connectors;
    std::vector<IConnector*> checkColideConnectors;
    double radius;
    
public:
    IBody(Position _pos);
    void update ( Time_sec dt );
    
    Position getPosition() const;
    double getRadius() const;
    const std::vector<IPoint *>& getPoints() const;
    const std::vector<IConnector *>& getConnectors() const;
    const std::vector<IConnector *>& getCheckColideConnectors() const;
    
    std::pair<int, int> didColide (IBody * b);
    IPoint* calcColide (IBody * b);
    
    friend class ForceAdder;
    friend class Window;
};

#endif /* IBody_hpp */
