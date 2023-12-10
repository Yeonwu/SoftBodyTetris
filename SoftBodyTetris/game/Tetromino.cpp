//
//  Tetromino.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/10.
//

#include "Tetromino.hpp"
#include <random>

SoftBody* getSoftTetromino(Position pos, double size) {
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 6);
    
    SoftBody* softBody;
    switch (dis(gen)) {
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
            softBody = new SoftBody({pos.x, pos.y - size*0.5}, 10000);
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
        // ###
        // #
        case 2:
            softBody = new SoftBody({pos.x, pos.y - size*0.2}, 10000);
            softBody->
             addPoint(new MassPoint({pos.x - size*1.5, pos.y - size  }, 5))
            .addPoint(new MassPoint({pos.x - size*0.5, pos.y - size  }, 5))
            .addPoint(new MassPoint({pos.x + size*0.5, pos.y - size  }, 5))
            .addPoint(new MassPoint({pos.x + size*1.5, pos.y - size  }, 5))
            
            .addPoint(new MassPoint({pos.x - size*1.5, pos.y         }, 5))
            .addPoint(new MassPoint({pos.x - size*0.5, pos.y         }, 5))
            .addPoint(new MassPoint({pos.x + size*0.5, pos.y         }, 5))
            .addPoint(new MassPoint({pos.x + size*1.5, pos.y         }, 5))
            
            .addPoint(new MassPoint({pos.x - size*0.5, pos.y + size  }, 5))
            .addPoint(new MassPoint({pos.x + size*0.5, pos.y + size  }, 5))
            
            .connectPoints(0, 1)
            .connectPoints(1, 2)
            .connectPoints(2, 3)
            .connectPoints(3, 7)
            .connectPoints(7, 6)
            .connectPoints(6, 9)
            .connectPoints(9, 8)
            .connectPoints(8, 5)
            .connectPoints(5, 4)
            .connectPoints(4, 0);
            return softBody;
        //  ##
        // ##
        case 3:
            softBody = new SoftBody({pos.x, pos.y}, 10000);
            softBody->
             addPoint(new MassPoint({pos.x - size*0.5, pos.y - size  }, 5))
            .addPoint(new MassPoint({pos.x + size*0.5, pos.y - size  }, 5))
            .addPoint(new MassPoint({pos.x + size*1.5, pos.y - size  }, 5))
            
            .addPoint(new MassPoint({pos.x - size*1.5, pos.y         }, 5))
            .addPoint(new MassPoint({pos.x - size*0.5, pos.y         }, 5))
            .addPoint(new MassPoint({pos.x + size*0.5, pos.y         }, 5))
            .addPoint(new MassPoint({pos.x + size*1.5, pos.y         }, 5))
            
            .addPoint(new MassPoint({pos.x - size*1.5, pos.y + size  }, 5))
            .addPoint(new MassPoint({pos.x - size*0.5, pos.y + size  }, 5))
            .addPoint(new MassPoint({pos.x + size*0.5, pos.y + size  }, 5))
            
            .connectPoints(0, 1)
            .connectPoints(1, 2)
            .connectPoints(2, 6)
            .connectPoints(6, 5)
            .connectPoints(5, 9)
            .connectPoints(9, 8)
            .connectPoints(8, 7)
            .connectPoints(7, 3)
            .connectPoints(3, 4)
            .connectPoints(4, 0);
            return softBody;
            
        // ##
        //  ##
        case 4:
            softBody = new SoftBody({pos.x, pos.y}, 10000);
            softBody->
             addPoint(new MassPoint({pos.x - size*1.5, pos.y - size  }, 5))
            .addPoint(new MassPoint({pos.x - size*0.5, pos.y - size  }, 5))
            .addPoint(new MassPoint({pos.x + size*0.5, pos.y - size  }, 5))
            
            .addPoint(new MassPoint({pos.x - size*1.5, pos.y         }, 5))
            .addPoint(new MassPoint({pos.x - size*0.5, pos.y         }, 5))
            .addPoint(new MassPoint({pos.x + size*0.5, pos.y         }, 5))
            .addPoint(new MassPoint({pos.x + size*1.5, pos.y         }, 5))
            
            .addPoint(new MassPoint({pos.x - size*0.5, pos.y + size  }, 5))
            .addPoint(new MassPoint({pos.x + size*0.5, pos.y + size  }, 5))
            .addPoint(new MassPoint({pos.x + size*1.5, pos.y + size  }, 5))
            
            
            .connectPoints(0, 1)
            .connectPoints(1, 2)
            .connectPoints(2, 5)
            .connectPoints(5, 6)
            .connectPoints(6, 9)
            .connectPoints(9, 8)
            .connectPoints(8, 7)
            .connectPoints(7, 4)
            .connectPoints(4, 3)
            .connectPoints(3, 0);
            return softBody;
            
            // ##
            // ##
            case 5:
                softBody = new SoftBody({pos.x, pos.y}, 10000);
                softBody->
                 addPoint(new MassPoint({pos.x - size, pos.y - size  }, 5))
                .addPoint(new MassPoint({pos.x       , pos.y - size  }, 5))
                .addPoint(new MassPoint({pos.x + size, pos.y - size  }, 5))
                
                .addPoint(new MassPoint({pos.x - size, pos.y         }, 5))
                .addPoint(new MassPoint({pos.x + size, pos.y         }, 5))
                
                .addPoint(new MassPoint({pos.x - size, pos.y + size  }, 5))
                .addPoint(new MassPoint({pos.x       , pos.y + size  }, 5))
                .addPoint(new MassPoint({pos.x + size, pos.y + size  }, 5))
                
                
                .connectPoints(0, 1)
                .connectPoints(1, 2)
                .connectPoints(2, 4)
                .connectPoints(4, 7)
                .connectPoints(7, 6)
                .connectPoints(6, 5)
                .connectPoints(5, 3)
                .connectPoints(3, 0);
                return softBody;
            
            // ###
            // #
            case 6:
                softBody = new SoftBody({pos.x + size*0.7, pos.y - size*0.2}, 10000);
                softBody->
                addPoint(new MassPoint({pos.x - size  , pos.y - size  }, 5))
               .addPoint(new MassPoint({pos.x         , pos.y - size  }, 5))
               .addPoint(new MassPoint({pos.x + size  , pos.y - size  }, 5))
               .addPoint(new MassPoint({pos.x + size*2, pos.y - size  }, 5))
               
               .addPoint(new MassPoint({pos.x - size  , pos.y         }, 5))
               .addPoint(new MassPoint({pos.x         , pos.y         }, 5))
               .addPoint(new MassPoint({pos.x + size  , pos.y         }, 5))
               .addPoint(new MassPoint({pos.x + size*2, pos.y         }, 5))
               
               .addPoint(new MassPoint({pos.x + size  , pos.y + size  }, 5))
               .addPoint(new MassPoint({pos.x + size*2, pos.y + size  }, 5))
                
                
                .connectPoints(0, 1)
                .connectPoints(1, 2)
                .connectPoints(2, 3)
                .connectPoints(3, 7)
                .connectPoints(7, 9)
                .connectPoints(9, 8)
                .connectPoints(8, 6)
                .connectPoints(6, 5)
                .connectPoints(5, 4)
                .connectPoints(4, 0);
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

Entity* createTetrominoEntity(Position pos) {
    return new Entity(getSoftTetromino(pos, 40), ENTITY_COLLIDABLE | ENTITY_GRAVITY | ENTITY_DAMPING, &softTetrominoRenderFunction);
}
