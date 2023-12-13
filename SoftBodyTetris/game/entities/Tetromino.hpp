//
//  Tetromino.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/10.
//

#ifndef Tetromino_hpp
#define Tetromino_hpp

#include "engine.hpp"

enum TetrominoKey {
    TetrominoKey_L,
    TetrominoKey_I,
    TetrominoKey_T,
    TetrominoKey_S,
    TetrominoKey_Z,
    TetrominoKey_O,
    TetrominoKey_J,
};

class TetrominoThruster {
private:
    IPoint* pushPoint;
    IPoint* dirPoint;
public:
    TetrominoThruster(IPoint* _pushPoint, IPoint* _dirPoint);
    void thrust();
};

class Tetromino: public Entity {
private:
    void buildTetromino(Position _pos, double size, TetrominoKey key);
    std::vector<TetrominoThruster> CWThrusters;
    std::vector<TetrominoThruster> CCWThrusters;
public:
    Tetromino (Position _pos, TetrominoKey key);
    void turnCW();
    void turnCCW();
};

class TetrominoRenderer : public Renderer {
public:
    TetrominoRenderer( int key, Color color );
    ~TetrominoRenderer() = default;
};

#endif /* Tetromino_hpp */
