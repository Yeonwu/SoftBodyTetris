//
//  PointRenderer.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/26.
//

#include "PointRenderer.hpp"
#include "IPoint.hpp"

PointRenderer::PointRenderer( Color _color ): IRenderer(_color) {}

void PointRenderer::render( Renderable * target, SDL_Renderer* SDLRenderer ) {
    Position pos = dynamic_cast<IPoint *>(target) -> getPosition();
    
    SDL_FRect rect = {(float)pos.x - 3, (float)pos.y - 3, 6, 6};
    
    SDL_SetRenderDrawColor( SDLRenderer, color.R, color.G, color.B, color.A );
    SDL_RenderDrawRectF( SDLRenderer, &rect );
}
