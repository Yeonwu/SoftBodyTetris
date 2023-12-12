//
//  Pointer.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/11.
//

#ifndef Pointer_hpp
#define Pointer_hpp

#include "engine.hpp"

Entity* createPointerEntity();
void pointerRenderFunction(IBody* body, SDL_Renderer* renderer);

#endif /* Pointer_hpp */
