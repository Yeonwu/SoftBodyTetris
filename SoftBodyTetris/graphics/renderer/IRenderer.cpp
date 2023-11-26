//
//  IRenderer.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/20.
//

#include "physics.hpp"
#include "IRenderer.hpp"
#include <stdio.h>


IRenderer::IRenderer( Color _color ):
    color(_color)
{}

void IRenderer::render( Renderable * target, SDL_Renderer* SDLRenderer ) {
    printf("IRenderer::render\n");
}

