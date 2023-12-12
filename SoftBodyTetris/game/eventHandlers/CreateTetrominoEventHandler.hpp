//
//  CreateTetrominoEventHandler.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/12.
//

#ifndef CreateTetrominoEventHandler_hpp
#define CreateTetrominoEventHandler_hpp

#include "engine.hpp"

class CreateTetrominoEventHandler: public EventHandler {
private:
    int nextTetrominoKey;
public:
    CreateTetrominoEventHandler();
    void handleFunction(SDL_Event& event);
};

#endif /* CreateTetrominoEventHandler_hpp */
