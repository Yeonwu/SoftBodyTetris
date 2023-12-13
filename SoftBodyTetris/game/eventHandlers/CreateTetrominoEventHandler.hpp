//
//  CreateTetrominoEventHandler.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/12.
//

#ifndef CreateTetrominoEventHandler_hpp
#define CreateTetrominoEventHandler_hpp

#include "engine.hpp"
#include "Tetromino.hpp"
#include "ControlEventHandler.hpp"

class CreateTetrominoEventHandler: public EventHandler {
private:
    TetrominoKey nextTetrominoKey;
    ControlEventHandler* controlEventHandler;
public:
    CreateTetrominoEventHandler(ControlEventHandler* _controlEventHandler);
    void handleFunction(SDL_Event& event);
    int getNextTetrominoKey;
};

#endif /* CreateTetrominoEventHandler_hpp */
