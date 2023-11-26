//
//  ConnectorRenderer.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/26.
//

#include "ConnectorRenderer.hpp"
#include "IConnector.hpp"

ConnectorRenderer::ConnectorRenderer( Color _color, Color _highlightColor ):
    IRenderer(_color),
    highlightColor(_highlightColor)
{}

void ConnectorRenderer::render( Renderable * target, SDL_Renderer* SDLRenderer ) {
    IConnector* ec = dynamic_cast<IConnector *>(target);
    Position pos0 = ec -> getPoint(0) -> getPosition();
    Position pos1 = ec -> getPoint(1) -> getPosition();
    
    double l = ec -> getLength();
    double d = (pos0 - pos1).size();
    Position m = (pos0 + pos1) / 2;
    
    
    Position pos2 = m + (pos0 - pos1)/d * l/2;
    Position pos3 = m + (pos1 - pos0)/d * l/2;
    
    SDL_SetRenderDrawColor( SDLRenderer, color.R, color.G, color.B, color.A );
    SDL_RenderDrawLine( SDLRenderer, pos2.x, pos2.y, pos3.x, pos3.y);
    
    SDL_SetRenderDrawColor( SDLRenderer, highlightColor.R, highlightColor.G, highlightColor.B, highlightColor.A );
    SDL_RenderDrawLine( SDLRenderer, pos0.x, pos0.y, pos3.x, pos3.y);

    SDL_SetRenderDrawColor( SDLRenderer, highlightColor.R, highlightColor.G, highlightColor.B, highlightColor.A );
    SDL_RenderDrawLine( SDLRenderer, pos2.x, pos2.y, pos1.x, pos1.y);
}
