//
//  entity.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/10.
//

#ifndef entity_hpp
#define entity_hpp

#include <SDL2/SDL.h>
#include "graphics.hpp"
#include "SoftBody.hpp"
#include <vector>

#define ENTITY_NOFLAG     0b00000000
#define ENTITY_COLLIDABLE 0b00000001
#define ENTITY_GRAVITY    0b00000010
#define ENTITY_DAMPING    0b00000100

class Entity {
private:
    static std::vector<Entity*> allEntities;
    static std::vector<int> collidableEntitiesIdx;
    
    IBody* body;
    Renderer* renderer;
    
    int idx;
    int collideIdx;
    
    static void update();
    static void render();
public:
    static Window* window;
    bool gravity;
    bool damping;
    bool isCollidable;
    bool isActivated;
    
    Entity(IBody* _body=NULL, int flag=0, Renderer* _renderer=NULL);
    int activate();
    IBody* getBody();
    void setBody(IBody* _body);
    ~Entity();
    
    friend class Engine;
};

#endif /* entity_hpp */
