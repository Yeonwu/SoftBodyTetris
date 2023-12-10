//
//  Border.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/10.
//

#ifndef Border_hpp
#define Border_hpp

#include "engine.hpp"

void borderRendererFunction(IBody* body, SDL_Renderer* renderer);
std::vector<Entity*> createBorderEntities(double SCREEN_WIDTH, double SCREEN_HEIGHT);



#endif /* Border_hpp */
