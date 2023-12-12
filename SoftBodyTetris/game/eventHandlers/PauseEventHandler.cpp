//
//  PauseEventHandler.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/12.
//

#include "PauseEventHandler.hpp"

PauseEventHandler::PauseEventHandler() {
    isPaused = false;
}

void PauseEventHandler::handleFunction (SDL_Event& event) {
    if (event.key.keysym.sym == SDLK_SPACE) {
        if (isPaused) {
            Engine::restartUpdate();
        } else {
            Engine::pauseUpdate();
        }
        isPaused = !isPaused;
    }
}
