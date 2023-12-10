#include <SDL2/SDL_timer.h>
#include <vector>

#include "utils.hpp"
#include "graphics.hpp"
#include "physics.hpp"
#include "entity.hpp"
#include "engine.hpp"

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

void softTetrominoRenderFunction(IBody* body, SDL_Renderer* renderer) {
    for ( const IPoint* p: body->getPoints() ) {
        Position pos = p->getPosition();
        SDL_FRect rect = {(float)pos.x - 3, (float)pos.y - 3, 6, 6};
        
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderDrawRectF(renderer, &rect);
    }
    
    for ( IConnector* c: body->getConnectors() ) {
        Position pos0 = c->getPoint(0)->getPosition();
        Position pos1 = c->getPoint(1)->getPosition();
        
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderDrawLine( renderer, pos0.x, pos0.y, pos1.x, pos1.y);
    }
}

int main () {
    Engine::init();
    
    Entity floor(new SoftBody({SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100}, 1000), ENTITY_COLLIDABLE | ENTITY_GRAVITY, &softTetrominoRenderFunction);
    floor.getBody()->addPoint(new FixedPoint({-100, SCREEN_HEIGHT + 50}, 10))
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
    
    new Entity(
               getSoftTetromino({100, 100}, 40),
               ENTITY_COLLIDABLE | ENTITY_GRAVITY | ENTITY_DAMPING,
               &softTetrominoRenderFunction
               );
    
    Engine::addEventHandler(SDL_KEYDOWN, [](SDL_Event& event)->void {
        Engine::pauseUpdate();
    });
    
    Engine::addEventHandler(SDL_KEYUP, [](SDL_Event& event)->void {
        Engine::restartUpdate();
    });
    
    Engine::addEventHandler(SDL_MOUSEBUTTONUP, [](SDL_Event& event)->void {
        new Entity(
                   getSoftTetromino({(double)event.button.x, (double)event.button.y}, 40),
                   ENTITY_COLLIDABLE | ENTITY_GRAVITY | ENTITY_DAMPING,
                   &softTetrominoRenderFunction
                   );
    });
    
    Engine::startLoop();
    
    return 0;
}
