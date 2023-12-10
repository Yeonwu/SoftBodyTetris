//
//  ConnectorRenderer.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/26.
//

#ifndef ConnectorRenderer_hpp
#define ConnectorRenderer_hpp

#include "Types.hpp"
#include "IRenderer.hpp"

class ConnectorRenderer: public IRenderer {
    Color highlightColor;
public:
    ConnectorRenderer( Color _color, Color _highlightColor );
    void render( Renderable * target, SDL_Renderer* SDLRenderer ) override;
};

#endif /* ConnectorRenderer_hpp */
