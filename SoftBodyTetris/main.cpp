#include <SDL2/SDL_timer.h>
#include <vector>

#include "graphics/graphics.hpp"
#include "physics/physics.hpp"

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 1280;

const double G = 9800;

void addGravity(IPoint &p) {
    Force gravity(0, G);
    p.addForce(gravity);
}

int main () {
    Window window( SCREEN_WIDTH, SCREEN_HEIGHT );
    
    FixedPoint p1{{200, 200}};
    MassPoint p2{20, {500, 400}, {0, 0}, {0, 0}};
    MassPoint p3{40, {600, 700}, {0, 0}, {0, 0}};
    ElasticConnector s(&p1, &p2, 200, 50);
    ElasticConnector s2(&p2, &p3, 300, 50);
    
    
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
            
            addGravity(p1);
            addGravity(p2);
        
            s.update();
            s2.update();
            
            p1.update( dt );
            p2.update( dt );
            p3.update( dt );
            
            last_update = SDL_GetTicks64();
            
        } else {
            // render
            window.clear();
            
            window.renderFixedPoint(p1);
            window.renderMassPoint(p2);
            window.renderMassPoint(p3);
            
            window.renderElasticConnector(s);
            window.renderElasticConnector(s2);
            
            window.update();
            
            last_render = SDL_GetTicks64();
        }
    }
}
