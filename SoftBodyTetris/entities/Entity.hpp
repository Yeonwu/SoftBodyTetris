//
//  Entity.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/20.
//

#ifndef Entity_hpp
#define Entity_hpp

#include "Types.hpp"
#include "IRenderer.hpp"

template<class PhysicsEntity>
class Entity {
public:
    PhysicsEntity* physicsEntity;
    IRenderer<PhysicsEntity>* renderer;
    
    Entity();
    Entity( PhysicsEntity * _physicsEntity, IRenderer<PhysicsEntity>* _renderer );
    
    Entity<PhysicsEntity>& setPhysicsEntity( PhysicsEntity* _phsicsEntity );
    Entity<PhysicsEntity>& setRenderer( IRenderer<PhysicsEntity>* _renderer );
    
    void render( SDL_Renderer* SDLRenderer );
    void update( Time_sec dt );
};

#endif /* Entity_hpp */
