#include <SDL2/SDL_timer.h>
#include <vector>

#include "graphics.hpp"
#include "physics.hpp"

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 1280;

int main () {
    Window window( SCREEN_WIDTH, SCREEN_HEIGHT );
    
    FixedPoint p1({360, 200});
    
    SoftBody sb1({200, 200}, 1000);
    MassPoint * sb1Right = new MassPoint({50, 0}, 10);
    
    sb1.addPoint(new MassPoint({0, 50}, 10))
    .addPoint(sb1Right)
    .addPoint(new MassPoint({0, -50}, 10))
    .addPoint(new MassPoint({-50, 0}, 10))
    .connectPoints(0, 1)
    .connectPoints(1, 2)
    .connectPoints(2, 3)
    .connectPoints(3, 0)
    
    .connectPoints(0, 2, false, 1000.0)
    .connectPoints(1, 3, false, 1000.0);
    
    ElasticConnector ec1(&p1, sb1Right, 300);
    
    
    SoftBody sb2({520, 200}, 1000);
    MassPoint * sbLeft = new MassPoint({-50, 0}, 10);
    
    sb2.addPoint(new MassPoint({0, 50}, 10))
    .addPoint(new MassPoint({50, 0}, 10))
    .addPoint(new MassPoint({0, -50}, 10))
    .addPoint(sbLeft)
    .connectPoints(0, 1)
    .connectPoints(1, 2)
    .connectPoints(2, 3)
    .connectPoints(3, 0)
    
    .connectPoints(0, 2, false, 1000.0)
    .connectPoints(1, 3, false, 1000.0);
    
    ElasticConnector ec2(&p1, sbLeft, 300);
    
    
    SDL_Event e;
    bool quit = false;
    Time_millis last_render = SDL_GetTicks64();
    Time_millis last_update = SDL_GetTicks64();
    
    bool pause = false;
    
    while ( !quit ) {
        if (SDL_GetTicks() < last_render + 32) {
            // update
            while ( SDL_PollEvent( &e ) ) {
                if ( e.type == SDL_QUIT ) quit = true;
                
                if ( e.type == SDL_KEYDOWN ) pause = true;
    
                if (e.type == SDL_KEYUP ) pause = false;
            }
            
            if (!pause) {
                
                Time_sec dt = (double)(SDL_GetTicks64() - last_update) / 1000.0;
                
                ForceAdder::addGravity(sb1);
                ForceAdder::addDamping(sb1);
                
                ForceAdder::addGravity(sb2);
                ForceAdder::addDamping(sb2);
                
                ec1.update( dt );
                ec2.update( dt );
                
                sb1.update( dt );
                sb2.update( dt );
            }
            
            last_update = SDL_GetTicks64();
            
        } else {
            // render
            window.clear();
            
            window.renderPoint( p1 );
            window.renderConnector( ec1 );
            
            if (sb1.didColide( &sb2 )) {
                window.renderBody( sb1, 1 );
            } else {
                window.renderBody( sb1 );
            }
            
            window.renderConnector( ec2 );
            window.renderBody( sb2 );
            
            window.update();
            
            last_render = SDL_GetTicks64();
        }
    }
}
