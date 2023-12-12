//
//  Tetromino.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/10.
//

#ifndef Tetromino_hpp
#define Tetromino_hpp

#include "engine.hpp"

Entity* createTetrominoEntity(Position pos, int key);
SoftBody* getSoftTetromino(Position pos, double size=25, int key=0);

class TetrominoRenderer : public Renderer {
public:
    TetrominoRenderer( int key, Color color );
    ~TetrominoRenderer() = default;
};

#endif /* Tetromino_hpp */
