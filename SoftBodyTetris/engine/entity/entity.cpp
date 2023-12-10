//
//  entity.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/10.
//

#include "entity.hpp"

std::vector<Entity*> Entity::allEntities;
std::vector<int> Entity::collidableEntitiesIdx;
Window* Entity::window = NULL;

void Entity::update() {
    for (auto entity: allEntities) {
        entity->body->update();
    }
    
    for (auto entity: allEntities) {
        ForceAdder::addGravity(*(entity->body));
        ForceAdder::addDamping(*(entity->body));
    }
    
    for (auto idx = collidableEntitiesIdx.begin(); idx < collidableEntitiesIdx.end(); idx++) {
        for (auto otherIdx = idx + 1; otherIdx < collidableEntitiesIdx.end(); otherIdx++) {
            allEntities.at(*idx)->body->calcColide( allEntities.at(*otherIdx)->body );
            allEntities.at(*otherIdx)->body->calcColide( allEntities.at(*idx)->body );
        }
    }
}

void Entity::render() {
    window->clear();
    for (auto entity: allEntities) {
        entity->renderFunction(entity->body, Entity::window->renderer);
    }
    window->update();
}


Entity::Entity(IBody* _body, int flag, RenderFunction _renderFunction): body(_body), renderFunction(_renderFunction) {
    gravity = flag & ENTITY_GRAVITY;
    damping = flag & ENTITY_DAMPING;
    
    Entity::allEntities.push_back(this);
    idx = (int)Entity::allEntities.size() - 1;
    if (flag & ENTITY_COLLIDABLE) {
        Entity::collidableEntitiesIdx.push_back(idx);
        collideIdx = (int)Entity::collidableEntitiesIdx.size() - 1;
    } else {
        collideIdx = -1;
    }
}

IBody* Entity::getBody() {
    return body;
}

void Entity::setBody(IBody* _body) {
    delete body;
    body = _body;
}

Entity::~Entity() {
    delete body;
    
    Entity::allEntities.erase(Entity::allEntities.begin() + idx);
    Entity::collidableEntitiesIdx.erase(Entity::collidableEntitiesIdx.begin() + collideIdx);
}
