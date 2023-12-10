//
//  PointRenderer.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/26.
//

#ifndef PointRenderer_hpp
#define PointRenderer_hpp

#include "IRenderer.hpp"

class PointRenderer: public IRenderer {
public:
    PointRenderer( Color _color );
    void render( Renderable * target, SDL_Renderer* SDLRenderer ) override;
};

#endif /* PointRenderer_hpp */
