//
//  IEntity.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/20.
//

#ifndef IEntity_hpp
#define IEntity_hpp

#include <SDL2/SDL.h>
#include "Types.hpp"
#include "graphics.hpp"

class IEntity {
    static SDL_Renderer* SDLRenderer;

public:
    Renderable* physicsEntity;
    IRenderer* renderer;

    static void setSDLRenderer(SDL_Renderer* _SDLRenderer);

    IEntity();
    IEntity( Renderable * _physicsEntity, IRenderer* _renderer );

    IEntity& setPhysicsEntity( Renderable* _phsicsEntity );
    IEntity& setRenderer( IRenderer* _renderer );

    void render();
    void update( Time_sec dt );
};

#endif /* Entity_hpp */
