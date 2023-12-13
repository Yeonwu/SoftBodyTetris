//
//  CreateTetrominoEventHandler.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/12.
//

#include "CreateTetrominoEventHandler.hpp"
#include "Tetromino.hpp"

CreateTetrominoEventHandler::CreateTetrominoEventHandler(ControlEventHandler* _controlEventHandler): controlEventHandler(_controlEventHandler) {
    nextTetrominoKey = static_cast<TetrominoKey>(realRandom(0, 6));
}

void CreateTetrominoEventHandler::handleFunction(SDL_Event &event) {
    auto* tetromino = new Tetromino ({(double)event.button.x, (double)event.button.y}, nextTetrominoKey);
    tetromino->activate();
    nextTetrominoKey = static_cast<TetrominoKey>(realRandom(0, 6));
    
    controlEventHandler->setTargetTetromino(tetromino);
}
