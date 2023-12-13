#include "engine.hpp"
#include "eventHandlers.hpp"
#include "entities.hpp"

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 800;

int main () {
    Engine::init();

    auto controlEventHandler = new ControlEventHandler();
    auto createTetrominoEventHandler = new CreateTetrominoEventHandler(controlEventHandler);
    
    Engine::addEventHandler(SDL_KEYUP, new PauseEventHandler());
    Engine::addEventHandler(SDL_MOUSEBUTTONUP, createTetrominoEventHandler);
    Engine::addEventHandler(SDL_KEYDOWN, controlEventHandler);
    
    auto borderEntities = createBorderEntities(SCREEN_WIDTH, SCREEN_HEIGHT);
    for (auto borderEntity: borderEntities) {
        borderEntity->activate();
    }

    Engine::startLoop();

    return 0;
}
