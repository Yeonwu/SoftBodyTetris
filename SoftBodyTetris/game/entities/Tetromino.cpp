//
//  Tetromino.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/10.
//

#include "Tetromino.hpp"
#include <random>

Entity* createTetrominoEntity(Position pos, int key) {
    IBody* tetromino = getSoftTetromino(pos, 40, key);
    TetrominoRenderer* renderer = new TetrominoRenderer(key, HSVtoRGB(rand()%360, 100, 100));
    
    return new Entity( tetromino, ENTITY_COLLIDABLE | ENTITY_GRAVITY | ENTITY_DAMPING, renderer );
}

SoftBody* getSoftTetromino(Position pos, double size, int key) {
    SoftBody* softBody;
    switch (key) {
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
        //  #
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

TetrominoRenderer::TetrominoRenderer( int key, Color color ): Renderer(color) {
    switch (key) {
        case 0:
            polygonIdx = {0, 1, 4, 1, 4, 5, 1, 2, 5, 2, 5, 6, 3, 2, 6, 3, 6, 7, 4, 5, 8, 5, 8, 9};
            break;
        case 1:
            polygonIdx = {0, 4, 5, 5, 9, 0};
            break;
        case 2:
            polygonIdx = {0, 1, 4, 1, 4, 5, 1, 2, 5, 2, 5, 6, 3, 2, 6, 3, 6, 7, 5, 6, 9, 5, 8, 9};
            break;
        case 3:
            polygonIdx = {0, 1, 4, 1, 4, 5, 1, 2, 5, 2, 5, 6, 3, 4, 8, 3, 7, 8, 4, 5, 9, 4, 8, 9};
            break;
        case 4:
            polygonIdx = {0, 1, 4, 0, 3, 4, 1, 2, 5, 1, 4, 5, 4, 5, 8, 4, 7, 8, 5, 6, 9, 5, 8, 9};
            break;
        case 5:
            polygonIdx = {0, 2, 7, 0, 5, 7};
            break;
        case 6:
            polygonIdx = {0, 1, 4, 1, 4, 5, 1, 2, 5, 2, 5, 6, 3, 2, 6, 3, 6, 7, 6, 7, 9, 6, 8, 9};
            break;
        default:
            break;
    }
}
