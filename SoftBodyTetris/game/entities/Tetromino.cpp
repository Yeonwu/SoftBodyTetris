//
//  Tetromino.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/10.
//

#include "Tetromino.hpp"
#include <random>

Tetromino::Tetromino(Position pos, TetrominoKey key) {
    buildTetromino(pos, 40, key);
    setRenderer(new TetrominoRenderer(key, HSVtoRGB(rand()%360, 78, 92)));
    setFlag(ENTITY_COLLIDABLE | ENTITY_GRAVITY | ENTITY_DAMPING);
}

void Tetromino::turnCW() {
    for (auto thruster: CWThrusters) {
        thruster.thrust();
    }
}

void Tetromino::turnCCW() {
    for (auto thruster: CCWThrusters) {
        thruster.thrust();
    }
}

void Tetromino::buildTetromino(Position pos, double size, TetrominoKey key) {
    SoftBody* softBody = NULL;
    if (key == TetrominoKey_L ) {
        // ###
        // #
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
        auto points = softBody->getPoints();
        CWThrusters = {
            TetrominoThruster {points.at(8), points.at(4)},
            TetrominoThruster {points.at(9), points.at(5)},
            TetrominoThruster {points.at(2), points.at(6)},
            TetrominoThruster {points.at(3), points.at(9)},
        };
        
        CCWThrusters = {
            TetrominoThruster {points.at(0), points.at(4)},
            TetrominoThruster {points.at(1), points.at(5)},
            TetrominoThruster {points.at(6), points.at(2)},
            TetrominoThruster {points.at(9), points.at(3)},
        };
    } else if (key == TetrominoKey_I) {
        // ####
        
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
        auto points = softBody->getPoints();
        CWThrusters = {
            TetrominoThruster {points.at(9), points.at(0)},
            TetrominoThruster {points.at(8), points.at(1)},
            TetrominoThruster {points.at(3), points.at(6)},
            TetrominoThruster {points.at(4), points.at(5)},
        };
        
        CCWThrusters = {
            TetrominoThruster {points.at(0), points.at(9)},
            TetrominoThruster {points.at(1), points.at(8)},
            TetrominoThruster {points.at(6), points.at(3)},
            TetrominoThruster {points.at(5), points.at(4)},
        };
    } else if (key == TetrominoKey_T) {
        // ###
        //  #
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
        
        auto points = softBody->getPoints();
        CWThrusters = {
            TetrominoThruster {points.at(4), points.at(0)},
            TetrominoThruster {points.at(5), points.at(1)},
            TetrominoThruster {points.at(2), points.at(3)},
            TetrominoThruster {points.at(3), points.at(7)},
        };
        
        CCWThrusters = {
            TetrominoThruster {points.at(0), points.at(4)},
            TetrominoThruster {points.at(1), points.at(5)},
            TetrominoThruster {points.at(3), points.at(2)},
            TetrominoThruster {points.at(7), points.at(3)},
        };
    } else if (key == TetrominoKey_S) {
        //  ##
        // ##
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
        auto points = softBody->getPoints();
        CWThrusters = {
            TetrominoThruster {points.at(7), points.at(3)},
            TetrominoThruster {points.at(8), points.at(4)},
            TetrominoThruster {points.at(1), points.at(5)},
            TetrominoThruster {points.at(2), points.at(6)},
            
        };
        
        CCWThrusters = {
            TetrominoThruster {points.at(3), points.at(7)},
            TetrominoThruster {points.at(4), points.at(8)},
            TetrominoThruster {points.at(5), points.at(1)},
            TetrominoThruster {points.at(6), points.at(2)},
        };
    } else if (key == TetrominoKey_Z) {
        // ##
        //  ##
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
        auto points = softBody->getPoints();
        CWThrusters = {
            TetrominoThruster {points.at(3), points.at(0)},
            TetrominoThruster {points.at(4), points.at(1)},
            TetrominoThruster {points.at(5), points.at(8)},
            TetrominoThruster {points.at(6), points.at(9)},
        };
        
        CCWThrusters = {
            TetrominoThruster {points.at(0), points.at(3)},
            TetrominoThruster {points.at(1), points.at(4)},
            TetrominoThruster {points.at(8), points.at(5)},
            TetrominoThruster {points.at(9), points.at(6)},
        };
    } else if (key == TetrominoKey_O) {
        // ##
        // ##
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
        auto points = softBody->getPoints();
        CWThrusters = {
            TetrominoThruster {points.at(5), points.at(0)},
            TetrominoThruster {points.at(6), points.at(1)},
            TetrominoThruster {points.at(1), points.at(6)},
            TetrominoThruster {points.at(2), points.at(7)},
        };
        
        CCWThrusters = {
            TetrominoThruster {points.at(0), points.at(5)},
            TetrominoThruster {points.at(1), points.at(6)},
            TetrominoThruster {points.at(6), points.at(1)},
            TetrominoThruster {points.at(7), points.at(2)},
        };
    } else if (key == TetrominoKey_J) {
        // ###
        //   #
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
        auto points = softBody->getPoints();
        CWThrusters = {
            TetrominoThruster {points.at(4), points.at(0)},
            TetrominoThruster {points.at(5), points.at(1)},
            TetrominoThruster {points.at(2), points.at(6)},
            TetrominoThruster {points.at(3), points.at(7)},
        };
        
        CCWThrusters = {
            TetrominoThruster {points.at(0), points.at(4)},
            TetrominoThruster {points.at(1), points.at(5)},
            TetrominoThruster {points.at(6), points.at(2)},
            TetrominoThruster {points.at(7), points.at(3)},
        };
    }
    
    setBody(softBody);
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


TetrominoThruster::TetrominoThruster(IPoint* _pushPoint, IPoint* _dirPoint): pushPoint(_pushPoint), dirPoint(_dirPoint) {}
void TetrominoThruster::thrust() {
    pushPoint->addForce( (dirPoint->getPosition() - pushPoint->getPosition()).norm() * 100000 );
}
