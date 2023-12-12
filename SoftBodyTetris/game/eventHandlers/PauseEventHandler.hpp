//
//  PauseEventHandler.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/12.
//

#ifndef PauseEventHandler_hpp
#define PauseEventHandler_hpp

#include "engine.hpp"

class PauseEventHandler: public EventHandler {
private:
    bool isPaused;
public:
    PauseEventHandler();
    void handleFunction (SDL_Event& event);
};

#endif /* PauseEventHandler_hpp */
