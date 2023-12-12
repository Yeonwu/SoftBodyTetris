//
//  ControlEventHandler.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/12.
//

#include "ControlEventHandler.hpp"

ControlEventHandler::ControlEventHandler(Entity* tetromino) {
    targetTetromino = tetromino;
}

void ControlEventHandler::handleFunction(SDL_Event &event) {
    if (event.key.keysym.sym == SDLK_w) {
        targetTetromino->getBody()->addForce({ -10000, 0 });
    } else if (event.key.keysym.sym == SDLK_s) {
        targetTetromino->getBody()->addForce({ 10000, 0 });
    } else if (event.key.keysym.sym == SDLK_a) {
        targetTetromino->getBody()->addForce({ 0, 10000 });
    } else if (event.key.keysym.sym == SDLK_d) {
        targetTetromino->getBody()->addForce({ 0, -10000 });
    }
}
