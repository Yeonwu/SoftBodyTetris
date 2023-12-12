//
//  engine.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/10.
//

#include "engine.hpp"

Window Engine::window(400, 800);

bool Engine::quit = false;
bool Engine::pause = false;
    
Time_millis Engine::lastTimeAcc;
Time_millis Engine::curTime;
    
Time_millis Engine::lastRender;
const Time_millis Engine::msPerFrame = 32;
    
Time_millis Engine::acc = 0;
Time_millis Engine::total_t = 0;

std::vector<std::pair<SDL_EventType, std::vector<EventHandler*>>> Engine::eventHandlers;

void Engine::init() {
    SDL_Init( SDL_INIT_EVERYTHING );
    
    Entity::window = &Engine::window;
    Engine::addEventHandler(SDL_QUIT, new DefaultQuitEventHandler());
}

void Engine::startLoop() {
    Engine::lastTimeAcc = SDL_GetTicks64();
    Engine::curTime = SDL_GetTicks64();
    SDL_Event event;
    
    while ( !Engine::quit ) {
        // input
        while ( SDL_PollEvent(&event) ) {
            handleEvent(event);
        }
        
        Engine::curTime = SDL_GetTicks64();
        Engine::acc += Engine::curTime - Engine::lastTimeAcc;
        Engine::lastTimeAcc = Engine::curTime;
        
        // update
        while ( Engine::acc >= updateTimeGap || Engine::lastRender + Engine::msPerFrame > SDL_GetTicks()) {
            Engine::acc -= updateTimeGap;
            Engine::total_t += updateTimeGap;
            
            if (!pause) {
                Entity::update();
            }
        }
            
        // render
        Entity::render();
    }
}

void Engine::escapeLoop() {
    Engine::quit = true;
}

void Engine::handleEvent(SDL_Event &event) {
    for (auto handlers: Engine::eventHandlers) {
        if (handlers.first == event.type) {
            for (auto handler: handlers.second) {
                handler->handleFunction(event);
            }
            break;
        }
    }
}

void Engine::addEventHandler(SDL_EventType eventType, EventHandler* handler) {
    for (auto handlers: Engine::eventHandlers) {
        if (handlers.first == eventType) {
            handlers.second.push_back(handler);
            break;
        }
    }
    std::vector<EventHandler*> newHandlerList = {handler};
    std::pair newEventHandler(eventType, newHandlerList);
    Engine::eventHandlers.push_back(newEventHandler);
}

void Engine::pauseUpdate() {
    Engine::pause = true;
}

void Engine::restartUpdate() {
    Engine::pause = false;
}


void DefaultQuitEventHandler::handleFunction(SDL_Event &event) {
    Engine::escapeLoop();
}
