#include <SDL2/SDL_timer.h>
#include <vector>

#include "graphics/graphics.hpp"
#include "physics/physics.hpp"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

int main () {
    Window window( SCREEN_WIDTH, SCREEN_HEIGHT );
    
    MassPoint p1{10, {200, 200}, {0, 0}, {0, 0}};
    MassPoint p2{20, {500, 400}, {0, 0}, {0, 0}};
    Spring s(&p1, &p2, 200, 50);
    
    
    SDL_Event e;
    bool quit = false;
    Time_millis last_render = SDL_GetTicks64();
    Time_millis last_update = SDL_GetTicks64();
    
    while ( !quit ) {
        if (SDL_GetTicks() < last_render + 32) {
            // update
            while ( SDL_PollEvent( &e ) ) {
                if (e.type == SDL_QUIT) quit = true;
            }
            
            Time_sec dt = (double)(SDL_GetTicks64() - last_update) / 1000.0;            
        
            s.update();
            p1.update( dt );
            p2.update( dt );
            
            last_update = SDL_GetTicks64();
            
        } else {
            // render
            window.clear();
            
            window.renderMassPoint(p1);
            window.renderMassPoint(p2);
            window.renderSpring(s);
            
            window.update();
            
            last_render = SDL_GetTicks64();
        }
    }
}
