//
//  Entity.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/20.
//

#include "physics.hpp"
#include "Entity.hpp"

template<typename PhysicsEntity>
Entity<PhysicsEntity>::Entity( PhysicsEntity * _physicsEntity, IRenderer<PhysicsEntity>* _renderer ):
    physicsEntity( _physicsEntity ),
    renderer( _renderer )
{}

template<typename PhysicsEntity>
Entity<PhysicsEntity>&  Entity<PhysicsEntity>::setPhysicsEntity( PhysicsEntity* _phsicsEntity ) {
    physicsEntity = _phsicsEntity;
    return *this;
}

template<typename PhysicsEntity>
Entity<PhysicsEntity>& Entity<PhysicsEntity>::setRenderer( IRenderer<PhysicsEntity>* _renderer ) {
    renderer = _renderer;
    return *this;
}

template<typename PhysicsEntity>
void Entity<PhysicsEntity>::render( SDL_Renderer* SDLRenderer ) {
    renderer -> render( physicsEntity, SDLRenderer );
}

template<typename PhysicsEntity>
void Entity<PhysicsEntity>::update( Time_sec dt ) {
    physicsEntity -> update( dt );
}

template class Entity<IPoint>;
