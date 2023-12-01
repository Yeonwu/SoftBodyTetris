#include <SDL2/SDL_timer.h>
#include <vector>

#include "utils.hpp"
#include "graphics.hpp"
#include "physics.hpp"
#include "IEntity.hpp"

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 720;

SoftBody* getSoftRect(Position pos) {
    SoftBody* softBody = new SoftBody(pos, 1000);
    softBody->addPoint(new MassPoint({pos.x + 50, pos.y + 50}, 10))
        .addPoint(new MassPoint({pos.x + 50, pos.y - 50}, 10))
        .addPoint(new MassPoint({pos.x - 50, pos.y + 50}, 10))
        .addPoint(new MassPoint({pos.x - 50, pos.y - 50}, 10))
        .connectPoints(0, 1)
        .connectPoints(1, 2)
        .connectPoints(2, 3)
        .connectPoints(3, 0)
    
        .connectPoints(0, 2, false, 1000.0)
        .connectPoints(1, 3, false, 1000.0);
    
    return softBody;
}

int main () {
    Window window( SCREEN_WIDTH, SCREEN_HEIGHT );
    
    IEntity::setSDLRenderer(window.renderer);
    
    FixedPoint* fp1 = new FixedPoint({360, 200});
    IEntity p1( fp1, new PointRenderer({0xFF, 0x00, 0x00}) );
    
    SoftBody* floor = new SoftBody({SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100}, 1000);
    floor->addPoint(new FixedPoint({-100, SCREEN_HEIGHT - 100}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 100, SCREEN_HEIGHT - 100}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 100, SCREEN_HEIGHT}, 10))
        .addPoint(new FixedPoint({-100, SCREEN_HEIGHT}, 10))
        .connectPoints(0, 1)
        .connectPoints(1, 2)
        .connectPoints(2, 3)
        .connectPoints(3, 0);
    
    std::vector<IBody*> rectList;
    rectList.push_back(getSoftRect({400, 200}));
    rectList.push_back(getSoftRect({400, 0}));
    rectList.push_back(getSoftRect({100, 200}));
    rectList.push_back(getSoftRect({200, 0}));
    
    SDL_Event e;
    bool quit = false;
    Time_millis last_update = SDL_GetTicks64();
    
    bool pause = false;
    
    while ( !quit ) {
        if (SDL_GetTicks() < last_update + 64) {
            // update
            while ( SDL_PollEvent( &e ) ) {
                if ( e.type == SDL_QUIT ) quit = true;
                
                if ( e.type == SDL_KEYDOWN ) pause = !pause;
            }
            
            if (!pause) {
                
                Time_sec dt = (double)(SDL_GetTicks64() - last_update) / 1000.0;
                
                p1.update( dt );
                
                for (auto& rect: rectList) {
                    ForceAdder::addGravity(*rect);
                    rect->update( dt );
                    rect->calcColide( floor );

                    for (auto& otherRect: rectList) {
                        if (rect == otherRect) continue;
                        rect->calcColide(otherRect);
                    }
                }
            }
            
            last_update = SDL_GetTicks64();
            
            // render
            window.clear();
            
            p1.render();
            
            for (auto& rect: rectList) {
                window.renderBody(*rect);
            }
            window.renderBody(*floor);
            
            window.update();
        }
    }
}
