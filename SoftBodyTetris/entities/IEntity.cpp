//
//  IEntity.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/20.
//

#include "IEntity.hpp"

SDL_Renderer* IEntity::SDLRenderer = NULL;

void IEntity::setSDLRenderer(SDL_Renderer* _SDLRenderer){
    IEntity::SDLRenderer = _SDLRenderer;
}

IEntity::IEntity( Renderable * _physicsEntity, IRenderer* _renderer ):
    physicsEntity( _physicsEntity ),
    renderer( _renderer )
{}


IEntity& IEntity::setPhysicsEntity( Renderable* _phsicsEntity ) {
    physicsEntity = _phsicsEntity;
    return *this;
}

IEntity& IEntity::setRenderer( IRenderer* _renderer ) {
    renderer = _renderer;
    return *this;
}

void IEntity::render() {
    renderer -> render( physicsEntity, IEntity::SDLRenderer );
}

void IEntity::update() {
    physicsEntity -> update();
}
