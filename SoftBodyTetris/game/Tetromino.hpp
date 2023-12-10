//
//  Tetromino.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/10.
//

#ifndef Tetromino_hpp
#define Tetromino_hpp

#include "engine.hpp"

SoftBody* getSoftTetromino(Position pos, double size=25);
void softTetrominoRenderFunction(IBody* body, SDL_Renderer* renderer);
Entity* createTetrominoEntity(Position pos);

#endif /* Tetromino_hpp */
