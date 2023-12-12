//
//  Pointer.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/11.
//

#include "Pointer.hpp"

void pointerRenderFunction(IBody* body, SDL_Renderer* renderer);

Entity* createPointerEntity() {
    Engine::addEventHandler(SDL_MOUSEMOTION, [](SDL_Event& event) -> void {});
    
    Entity* pointerEntity = new Entity( new SoftBody({0, 0}, 10), ENTITY_NOFLAG, pointerRenderFunction);
    
    
    
    return pointerEntity;
}
