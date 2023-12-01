//
//  Renderable.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/30.
//

#ifndef Renderable_hpp
#define Renderable_hpp

class Renderable {
public:
    virtual void update ( Time_sec dt ) = 0;
};


#endif /* Renderable_hpp */
