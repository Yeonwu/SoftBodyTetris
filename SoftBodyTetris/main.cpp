#include <SDL2/SDL_timer.h>
#include <vector>

#include "utils.hpp"
#include "graphics.hpp"
#include "physics.hpp"
#include "IEntity.hpp"

const int SCREEN_WIDTH = 400;
const int SCREEN_HEIGHT = 800;

SoftBody* getSoftTetromino(Position pos, double size=25) {
    SoftBody* softBody;
    switch (rand() % 2) {
        // ###
        // #
        case 0:
            softBody = new SoftBody({pos.x + size*0.3, pos.y - size*0.2}, 5000);
            softBody->
             addPoint(new MassPoint({pos.x - size  , pos.y - size  }, 5))
            .addPoint(new MassPoint({pos.x         , pos.y - size  }, 5))
            .addPoint(new MassPoint({pos.x + size  , pos.y - size  }, 5))
            .addPoint(new MassPoint({pos.x + size*2, pos.y - size  }, 5))
            .addPoint(new MassPoint({pos.x - size  , pos.y         }, 5))
            .addPoint(new MassPoint({pos.x         , pos.y         }, 5))
            .addPoint(new MassPoint({pos.x + size  , pos.y         }, 5))
            .addPoint(new MassPoint({pos.x + size*2, pos.y         }, 5))
            .addPoint(new MassPoint({pos.x - size  , pos.y + size  }, 5))
            .addPoint(new MassPoint({pos.x         , pos.y + size  }, 5))
            
            .connectPoints(0, 1)
            .connectPoints(1, 2)
            .connectPoints(2, 3)
            .connectPoints(3, 7)
            .connectPoints(7, 6)
            .connectPoints(6, 5)
            .connectPoints(5, 9)
            .connectPoints(9, 8)
            .connectPoints(8, 4)
            .connectPoints(4, 0);
            return softBody;
        
        // ####
        case 1:
            softBody = new SoftBody({pos.x, pos.y - size*0.5}, 5000);
            softBody->
             addPoint(new MassPoint({pos.x - size*2, pos.y - size  }, 5))
            .addPoint(new MassPoint({pos.x - size  , pos.y - size  }, 5))
            .addPoint(new MassPoint({pos.x         , pos.y - size  }, 5))
            .addPoint(new MassPoint({pos.x + size  , pos.y - size  }, 5))
            .addPoint(new MassPoint({pos.x + size*2, pos.y - size  }, 5))
            .addPoint(new MassPoint({pos.x + size*2, pos.y         }, 5))
            .addPoint(new MassPoint({pos.x + size  , pos.y         }, 5))
            .addPoint(new MassPoint({pos.x         , pos.y         }, 5))
            .addPoint(new MassPoint({pos.x - size  , pos.y         }, 5))
            .addPoint(new MassPoint({pos.x - size*2, pos.y         }, 5))
            
            .connectPoints(0, 1)
            .connectPoints(1, 2)
            .connectPoints(2, 3)
            .connectPoints(3, 4)
            .connectPoints(4, 5)
            .connectPoints(5, 6)
            .connectPoints(6, 7)
            .connectPoints(7, 8)
            .connectPoints(8, 9)
            .connectPoints(9, 0);
            return softBody;
    }
    
    return NULL;
}

int main () {
    Window window( SCREEN_WIDTH, SCREEN_HEIGHT );
    
    IEntity::setSDLRenderer(window.renderer);
    
    SoftBody* floor = new SoftBody({SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100}, 1000);
    floor->addPoint(new FixedPoint({-100, SCREEN_HEIGHT + 50}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 100, SCREEN_HEIGHT + 50}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 100, SCREEN_HEIGHT}, 10))
        .addPoint(new FixedPoint({-100, SCREEN_HEIGHT}, 10))
        .connectPoints(0, 1)
        .connectPoints(1, 2)
        .connectPoints(2, 3)
        .connectPoints(3, 0);
    
    SoftBody* ceiling = new SoftBody({SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50}, 1000);
    ceiling->addPoint(new FixedPoint({-100, -50}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 100, -50}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 100, 0}, 10))
        .addPoint(new FixedPoint({-100, 0}, 10))
        .connectPoints(0, 1)
        .connectPoints(1, 2)
        .connectPoints(2, 3)
        .connectPoints(3, 0);
    
    SoftBody* rightWall = new SoftBody({SCREEN_WIDTH, SCREEN_HEIGHT / 2}, 1000);
    rightWall->addPoint(new FixedPoint({SCREEN_WIDTH + 50, 0}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 50, SCREEN_HEIGHT}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH, SCREEN_HEIGHT}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH, 0}, 10))
        .connectPoints(0, 1)
        .connectPoints(1, 2)
        .connectPoints(2, 3)
        .connectPoints(3, 0);
    
    SoftBody* leftWall = new SoftBody({0, SCREEN_HEIGHT / 2}, 1000);
    leftWall->addPoint(new FixedPoint({0, 0}, 10))
        .addPoint(new FixedPoint({0, SCREEN_HEIGHT}, 10))
        .addPoint(new FixedPoint({-50, SCREEN_HEIGHT}, 10))
        .addPoint(new FixedPoint({-50, 0}, 10))
        .connectPoints(0, 1)
        .connectPoints(1, 2)
        .connectPoints(2, 3)
        .connectPoints(3, 0);
    
    floor->update();
    ceiling->update();
    rightWall->update();
    leftWall->update();
    
    std::vector<SoftBody*> rectList;
    
    MassPoint* fp1 = new MassPoint({100, 545}, 10);
    IEntity p1( fp1, new PointRenderer({0xFF, 0x00, 0x00}) );
    
    SDL_Event e;
    bool quit = false;
    
    Time_millis lastTimeAcc = SDL_GetTicks64();
    Time_millis curTime = SDL_GetTicks64();
    
    Time_millis lastRender = 0;
    const Time_millis msPerFrame = 32;
    
    Time_millis acc = 0;
    Time_millis total_t = 0;
    long long frame = 0;
    
    bool pause = true;
    bool isMouseDown = false;
    
    while ( !quit ) {
        // input
        while ( SDL_PollEvent( &e ) ) {
            if ( e.type == SDL_QUIT ) {
                quit = true;
            } else if ( e.type == SDL_KEYDOWN ) {
                pause = !pause;
            } else if ( e.type == SDL_MOUSEBUTTONDOWN && !isMouseDown ) {
                isMouseDown = true;
            } else if ( e.type == SDL_MOUSEBUTTONUP && isMouseDown ) {
                isMouseDown = false;
                rectList.push_back(getSoftTetromino(fp1->getPosition(), 20));
            } else if ( e.type == SDL_MOUSEMOTION && isMouseDown) {
                fp1->setPosition({(double)e.button.x, (double)e.button.y});
            }
        }
        
        curTime = SDL_GetTicks64();
        acc += curTime - lastTimeAcc;
        lastTimeAcc = curTime;
        
        if (acc >= updateTimeGap) {
            printf("%lf\n", acc);
        }
        // update
        while ( acc >= updateTimeGap || lastRender + msPerFrame > SDL_GetTicks()) {
            acc -= updateTimeGap;
            total_t += updateTimeGap;
            frame++;
            if (!pause) {
                for (auto& rect: rectList) {
                    rect->update();
                    
                    ForceAdder::addGravity(*rect);
                    ForceAdder::addDamping(*rect);
                    
                    rect->calcColide( floor );
                    rect->calcColide( ceiling );
                    rect->calcColide( leftWall );
                    rect->calcColide( rightWall );
                    
                    for (auto& otherRect: rectList) {
                        if (rect == otherRect) continue;
                        rect->calcColide( otherRect );
                    }
                }
            }
        }
            
        // render
        window.clear();
        
        p1.render();
        
        for (auto& rect: rectList) {
            window.renderBody(*rect);
        }
        
        window.update();
    }
    
    printf("Total Times(millisec): %lf\n", total_t);
    printf("Total Frmae: %lld\n", frame);
    
    delete floor;
    delete leftWall;
    delete rightWall;
    
    for (auto& rectEntity: rectList) {
        delete rectEntity;
    }
    
    return 0;
}
