//
//  Renderer.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/12.
//

#include "Renderer.hpp"
#include "utils.hpp"

Renderer::Renderer(Color _color): color(_color) {}

Renderer::~Renderer() {}

void Renderer::render ( IBody* body, SDL_Renderer* renderer ) {
    std::vector<SDL_Vertex> vertices;
    
    auto points = body->getPoints();
    Position pos;
    for (auto idx : polygonIdx) {
        pos = points.at(idx)->getPosition();
        vertices.push_back({
            {(float)pos.x, (float)pos.y},
            {color.R, color.G, color.B, color.A },
            {0}
        });
    }
    SDL_RenderGeometry( renderer, nullptr, vertices.data(), (int)vertices.size(), nullptr, 0 );
}
