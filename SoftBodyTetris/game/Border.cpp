//
//  Border.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/10.
//

#include "Border.hpp"

void borderRendererFunction(IBody* body, SDL_Renderer* renderer) {}

std::vector<Entity*> createBorderEntities(double SCREEN_WIDTH, double SCREEN_HEIGHT) {
    
    Entity* floor = new Entity(new SoftBody({SCREEN_WIDTH / 2, SCREEN_HEIGHT - 100}, 1000), ENTITY_COLLIDABLE, &borderRendererFunction);
    floor->getBody()->addPoint(new FixedPoint({-100, SCREEN_HEIGHT + 50}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 100, SCREEN_HEIGHT + 50}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 100, SCREEN_HEIGHT}, 10))
        .addPoint(new FixedPoint({-100, SCREEN_HEIGHT}, 10))
        .connectPoints(0, 1)
        .connectPoints(1, 2)
        .connectPoints(2, 3)
        .connectPoints(3, 0);

    Entity* ceiling = new Entity(new SoftBody({SCREEN_WIDTH / 2, SCREEN_HEIGHT - 50}, 1000), ENTITY_COLLIDABLE, &borderRendererFunction);
    ceiling->getBody()->addPoint(new FixedPoint({-100, -50}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 100, -50}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 100, 0}, 10))
        .addPoint(new FixedPoint({-100, 0}, 10))
        .connectPoints(0, 1)
        .connectPoints(1, 2)
        .connectPoints(2, 3)
        .connectPoints(3, 0);

    Entity* rightWall = new Entity(new SoftBody({SCREEN_WIDTH, SCREEN_HEIGHT / 2}, 1000), ENTITY_COLLIDABLE, &borderRendererFunction);
    rightWall->getBody()->addPoint(new FixedPoint({SCREEN_WIDTH + 50, 0}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH + 50, SCREEN_HEIGHT}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH, SCREEN_HEIGHT}, 10))
        .addPoint(new FixedPoint({SCREEN_WIDTH, 0}, 10))
        .connectPoints(0, 1)
        .connectPoints(1, 2)
        .connectPoints(2, 3)
        .connectPoints(3, 0);

    Entity* leftWall = new Entity(new SoftBody({0, SCREEN_HEIGHT / 2}, 1000), ENTITY_COLLIDABLE, &borderRendererFunction);
    leftWall->getBody()->addPoint(new FixedPoint({0, 0}, 10))
        .addPoint(new FixedPoint({0, SCREEN_HEIGHT}, 10))
        .addPoint(new FixedPoint({-50, SCREEN_HEIGHT}, 10))
        .addPoint(new FixedPoint({-50, 0}, 10))
        .connectPoints(0, 1)
        .connectPoints(1, 2)
        .connectPoints(2, 3)
        .connectPoints(3, 0);
    
    std::vector<Entity*> borderEntities = {floor, ceiling, rightWall, leftWall};
    return borderEntities;
}
