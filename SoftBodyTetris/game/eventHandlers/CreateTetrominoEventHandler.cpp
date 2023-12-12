//
//  CreateTetrominoEventHandler.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/12.
//

#include "CreateTetrominoEventHandler.hpp"
#include "Tetromino.hpp"

CreateTetrominoEventHandler::CreateTetrominoEventHandler() {
    nextTetrominoKey = realRandom(0, 6);
}

void CreateTetrominoEventHandler::handleFunction(SDL_Event &event) {
    Entity* tetromino = createTetrominoEntity({(double)event.button.x, (double)event.button.y}, nextTetrominoKey);
    tetromino->activate();
    nextTetrominoKey = realRandom(0, 6);
}
