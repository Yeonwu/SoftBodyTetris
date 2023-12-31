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

struct DidColideResult {
    bool didColide;
    std::vector<std::pair<int, int>> colidePairs;
};

class IBody: public Renderable {
    
protected:
    Position pos;
    std::vector<IPoint*> points;
    std::vector<IConnector*> connectors;
    std::vector<IConnector*> checkColideConnectors;
    double radius;
    
public:
    IBody(Position _pos);
    virtual ~IBody() = default;
    
    void update ();
    
    Position getPosition() const;
    double getRadius() const;
    
    const std::vector<IPoint *>& getPoints() const;
    virtual IBody& addPoint(IPoint * p) = 0;
    
    virtual IBody& connectPoints(int idx1, int idx2) = 0;
    const std::vector<IConnector *>& getConnectors() const;
    virtual IBody& connectPoints(int idx1, int idx2, bool checkColide) = 0;
    const std::vector<IConnector *>& getCheckColideConnectors() const;
    
    DidColideResult didColide (IBody * b);
    void calcColide (IBody * b);
    
    void addForce(Force F);
    void setVelocity(Velocity V);
    
    friend class ForceAdder;
    friend class Window;
};

#endif /* IBody_hpp */
