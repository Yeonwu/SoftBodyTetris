//
//  IRenderer.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/20.
//

#ifndef IRenderer_hpp
#define IRenderer_hpp

#include <SDL2/SDL.h>
#include "Types.hpp"

class IRenderer {
protected:
    Color color;
    
public:
    
    IRenderer( Color _color );
    virtual void render( Renderable * target, SDL_Renderer* SDLRenderer );
    
    void setColor(Color _color);
};

#endif /* IRenderer_hpp */
