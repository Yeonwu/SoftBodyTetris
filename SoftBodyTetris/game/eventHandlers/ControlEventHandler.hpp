//
//  ControlEventHandler.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/12.
//

#ifndef ControlEventHandler_hpp
#define ControlEventHandler_hpp

#include "engine.hpp"

class ControlEventHandler: public EventHandler {
private:
    Entity* targetTetromino;
public:
    ControlEventHandler(Entity* tetromino);
    void handleFunction(SDL_Event& event);
};

#endif /* ControlEventHandler_hpp */
