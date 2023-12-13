//
//  ControlEventHandler.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/12.
//

#include "ControlEventHandler.hpp"

ControlEventHandler::ControlEventHandler() {}

void ControlEventHandler::setTargetTetromino(Tetromino* _targetTetromino) {
    targetTetromino = _targetTetromino;
}

void ControlEventHandler::handleFunction(SDL_Event &event) {
    if (targetTetromino == NULL) return;
    if (event.key.keysym.sym == SDLK_w) {
        targetTetromino->turnCCW();
    } else if (event.key.keysym.sym == SDLK_s) {
        targetTetromino->turnCW();
    } else if (event.key.keysym.sym == SDLK_a) {
        targetTetromino->getBody()->addForce({ -20000, 0 });
    } else if (event.key.keysym.sym == SDLK_d) {
        targetTetromino->getBody()->addForce({ 20000, 0 });
    }
}
