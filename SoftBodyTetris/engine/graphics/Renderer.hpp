//
//  Renderer.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/12.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <SDL2/SDL.h>
#include "IBody.hpp"

class Renderer {
protected:
    std::vector<int> polygonIdx;
    Color color;
public:
    Renderer(Color _color);
    Renderer();
    ~Renderer();
    void render ( IBody* body, SDL_Renderer* renderer );
    std::vector<SDL_Vertex> pointsToVertices (const std::vector<IPoint*>& points);
};

#endif /* Renderer_hpp */
