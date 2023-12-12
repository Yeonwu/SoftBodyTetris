#include "engine.hpp"
#include "eventHandlers.hpp"
#include "Border.hpp"
#include "Tetromino.hpp"

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 800;

int main () {
    Engine::init();

    Engine::addEventHandler(SDL_KEYUP, new PauseEventHandler());

    auto createTetrominoEventHandler = new CreateTetrominoEventHandler();
    Engine::addEventHandler(SDL_MOUSEBUTTONUP, createTetrominoEventHandler);

    auto tetromino = createTetrominoEntity({200, 400}, 0);
    tetromino->activate();
    auto controlEventHandler = new ControlEventHandler(tetromino);
    Engine::addEventHandler(SDL_KEYDOWN, controlEventHandler);
    
    auto borderEntities = createBorderEntities(SCREEN_WIDTH, SCREEN_HEIGHT);
    for (auto borderEntity: borderEntities) {
        borderEntity->activate();
    }

    Engine::startLoop();

    return 0;
}
