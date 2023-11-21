//
//  IRenderer.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/20.
//

#include "physics.hpp"
#include "IRenderer.hpp"
#include <stdio.h>


template <typename Renderable>
IRenderer<Renderable>::IRenderer( Color _color ):
    color(_color)
{}

template <typename Renderable>
void IRenderer<Renderable>::render( Renderable * target, SDL_Renderer* SDLRenderer ) {
    printf("IRenderer::render\n");
}

template <>
void IRenderer<IPoint>::render( IPoint * target, SDL_Renderer* SDLRenderer ) {
    Position pos = target -> getPosition();
    
    SDL_FRect rect = {(float)pos.x - 3, (float)pos.y - 3, 6, 6};
    
    SDL_SetRenderDrawColor( SDLRenderer, color.R, color.G, color.B, color.A );
    SDL_RenderDrawRectF( SDLRenderer, &rect );
}

template class IRenderer<IPoint>;
