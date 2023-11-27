#include <SDL2/SDL_timer.h>
#include <vector>

#include "utils.hpp"
#include "graphics.hpp"
#include "physics.hpp"
#include "IEntity.hpp"

const int SCREEN_WIDTH = 720;
const int SCREEN_HEIGHT = 1280;

int main () {
    Window window( SCREEN_WIDTH, SCREEN_HEIGHT );
    
    IEntity::setSDLRenderer(window.renderer);
    
    FixedPoint* fp1 = new FixedPoint({360, 200});
    IEntity p1( fp1, new PointRenderer({0xFF, 0x00, 0x00, 0xFF}) );
    
    SoftBody sb1({200, 200}, 1000);
    MassPoint * sb1Right = new MassPoint({50, 0}, 10);
    
    BodyRenderer* sb1r = new BodyRenderer({0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF});
    IEntity sb1e(&sb1, sb1r);
    
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
    
    
    ElasticConnector ec1(fp1, sb1Right, 300);
    IEntity ec1e(&ec1, new ConnectorRenderer({0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0x00, 0x00, 0xFF}));
    
    
    
    SoftBody sb2({520, 200}, 1000);
    BodyRenderer* sb2r = new BodyRenderer({0xFF, 0xFF, 0xFF, 0xFF}, {0xFF, 0xFF, 0xFF, 0xFF});
    IEntity sb2e(&sb2, sb2r);
    
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
    
    ElasticConnector ec2(fp1, sbLeft, 300);
    
    
    SDL_Event e;
    bool quit = false;
    Time_millis last_render = SDL_GetTicks64();
    Time_millis last_update = SDL_GetTicks64();
    
    bool pause = true;
    
    while ( !quit ) {
        if (SDL_GetTicks() < last_render + 32) {
            // update
            while ( SDL_PollEvent( &e ) ) {
                if ( e.type == SDL_QUIT ) quit = true;
                
                if ( e.type == SDL_KEYDOWN ) pause = !pause;
            }
            
            if (!pause) {
                
                Time_sec dt = (double)(SDL_GetTicks64() - last_update) / 1000.0 / 2;
                
                p1.update( dt );
                
                ForceAdder::addGravity(sb1);
                ForceAdder::addDamping(sb1);
                
                ForceAdder::addGravity(sb2);
                ForceAdder::addDamping(sb2);
                
                ec1e.update( dt );
                ec2.update( dt );
                
                sb1e.update( dt );
                sb2e.update( dt );

                std::pair result = sb1.didColide(&sb2);
                
                for (int idx = 0; idx < sb1.getPoints().size(); idx++ ) {
                    if ( idx == result.first ) {
                        sb1r -> setPointRenderer( idx, PointRenderer({0x00, 0xFF, 0x00, 0xFF}) );
                    } else {
                        sb1r -> deletePointRenderer( idx );
                    }
                }
                
                for (int idx = 0; idx < 4; idx++ ) {
                    if ( idx == result.second ) {
                        sb2r -> setConnectorRenderer(
                                                     idx,
                                                     ConnectorRenderer({0x00, 0xFF, 0x00, 0xFF},{0x00, 0xFF, 0x00, 0xFF}));
                    } else {
                        sb2r -> deleteConnectorRenderer( idx );
                    }
                }
            }
            
            last_update = SDL_GetTicks64();
            
        } else {
            // render
            window.clear();
            
            p1.render();
            
            ec1e.render();
            window.renderConnector( ec2 );
            
            sb1e.render();
            sb2e.render();
            
            window.update();
            
            last_render = SDL_GetTicks64();
        }
    }
}
