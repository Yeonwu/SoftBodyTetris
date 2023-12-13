//
//  ControlEventHandler.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/12.
//

#ifndef ControlEventHandler_hpp
#define ControlEventHandler_hpp

#include "engine.hpp"
#include "Tetromino.hpp"

class ControlEventHandler: public EventHandler {
private:
    Tetromino* targetTetromino;
public:
    ControlEventHandler();
    void setTargetTetromino(Tetromino* _targetTetromino);
    void handleFunction(SDL_Event& event);
};

#endif /* ControlEventHandler_hpp */
