#include "engine.hpp"
#include "Border.hpp"
#include "Tetromino.hpp"

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 800;

int main () {
    Engine::init();
    
    createBorderEntities(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    Engine::addEventHandler(SDL_KEYDOWN, [](SDL_Event& event)->void {
        Engine::pauseUpdate();
    });
    
    Engine::addEventHandler(SDL_KEYUP, [](SDL_Event& event)->void {
        Engine::restartUpdate();
    });
    
    Engine::addEventHandler(SDL_MOUSEBUTTONUP, [](SDL_Event& event)->void {
        createTetrominoEntity({(double)event.button.x, (double)event.button.y});
    });
    
    Engine::startLoop();
    
    return 0;
}
