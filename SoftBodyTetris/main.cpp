#include <SDL2/SDL_timer.h>
#include <vector>

#include "utils.hpp"
#include "graphics.hpp"
#include "physics.hpp"
#include "IEntity.hpp"

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 720;

SoftBody* getSoftRect(Position pos, double size=25) {
    SoftBody* softBody = new SoftBody(pos, 5000);
    softBody->addPoint(new MassPoint({pos.x + size, pos.y + size}, 5))
        .addPoint(new MassPoint({pos.x + size, pos.y - size}, 5))
        .addPoint(new MassPoint({pos.x - size, pos.y - size}, 5))
        .addPoint(new MassPoint({pos.x - size, pos.y + size}, 5))
        
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
    
    SoftBody* floor = new SoftBody({SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100}, 1000);
    floor->addPoint(new FixedPoint({-100, SCREEN_HEIGHT - 50}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 100, SCREEN_HEIGHT - 50}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 100, SCREEN_HEIGHT}, 10))
        .addPoint(new FixedPoint({-100, SCREEN_HEIGHT}, 10))
        .connectPoints(0, 1)
        .connectPoints(1, 2)
        .connectPoints(2, 3)
        .connectPoints(3, 0);
    
    SoftBody* ceiling = new SoftBody({SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50}, 1000);
    ceiling->addPoint(new FixedPoint({-100, 50}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 100, 50}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 100, 0}, 10))
        .addPoint(new FixedPoint({-100, 0}, 10))
        .connectPoints(0, 1)
        .connectPoints(1, 2)
        .connectPoints(2, 3)
        .connectPoints(3, 0);
    
    SoftBody* rightWall = new SoftBody({SCREEN_WIDTH, SCREEN_HEIGHT / 2}, 1000);
    rightWall->addPoint(new FixedPoint({SCREEN_WIDTH-50, 0}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH-50, SCREEN_HEIGHT}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 50, SCREEN_HEIGHT}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 50, 0}, 10))
        .connectPoints(0, 1)
        .connectPoints(1, 2)
        .connectPoints(2, 3)
        .connectPoints(3, 0);
    
    SoftBody* leftWall = new SoftBody({0, SCREEN_HEIGHT / 2}, 1000);
    leftWall->addPoint(new FixedPoint({50, 0}, 10))
        .addPoint(new FixedPoint({50, SCREEN_HEIGHT}, 10))
        .addPoint(new FixedPoint({-50, SCREEN_HEIGHT}, 10))
        .addPoint(new FixedPoint({-50, 0}, 10))
        .connectPoints(0, 1)
        .connectPoints(1, 2)
        .connectPoints(2, 3)
        .connectPoints(3, 0);
    
    std::vector<SoftBody*> rectList;
    rectList.push_back(getSoftRect({100, 545}, 50));
    rectList.push_back(getSoftRect({160, 545}));
//    rectList.push_back(getSoftRect({220, 545}, 30));
//    rectList.push_back(getSoftRect({280, 545}));
//    rectList.push_back(getSoftRect({340, 545}, 30));
//    rectList.push_back(getSoftRect({400, 545}));
//    rectList.push_back(getSoftRect({460, 545}, 30));
//    rectList.push_back(getSoftRect({520, 545}));
    
    FixedPoint* fp1 = new FixedPoint({100, 545});
    IEntity p1( fp1, new PointRenderer({0xFF, 0x00, 0x00}) );
    
    ElasticConnector handle(rectList.at(0)->getPoints().at(0), fp1, 1000);
    
    SDL_Event e;
    bool quit = false;
    
    Time_millis lastTimeAcc = SDL_GetTicks64();
    Time_millis acc = 0;
    const Time_millis updateTimeGap = 2;
    const Time_sec dt = (double)updateTimeGap / 1000;
    
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
            } else if ( e.type == SDL_MOUSEMOTION && isMouseDown) {
                fp1->setPosition({(double)e.button.x, (double)e.button.y});
            }
        }
        
        
        Time_millis curTime = SDL_GetTicks64();
        acc += curTime - lastTimeAcc;
        lastTimeAcc = curTime;
        
        // update
        while ( acc >= updateTimeGap ) {
            acc -= updateTimeGap;
            total_t += updateTimeGap;
            frame++;
            if (!pause) {
                p1.update( dt );
                handle.update( dt );
                floor->update( dt );
                ceiling->update( dt );
                rightWall->update( dt );
                leftWall->update( dt );
                
                for (auto& rect: rectList) {
                    ForceAdder::addGravity(*rect);
                    ForceAdder::addDamping(*rect);
                    
                    rect->update( dt );
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
        window.renderConnector(handle);
        
        for (auto& rect: rectList) {
            window.renderBody(*rect);
        }
        window.renderBody(*floor);
        window.renderBody(*ceiling);
        window.renderBody(*leftWall);
        window.renderBody(*rightWall);
        
        window.update();
    }
    
    printf("Total Times(millisec): %lld\n", total_t);
    printf("Total Frmae: %lld\n", frame);
    
    delete floor;
    delete leftWall;
    delete rightWall;
    
    for (auto& rectEntity: rectList) {
        delete rectEntity;
    }
    
    return 0;
}
