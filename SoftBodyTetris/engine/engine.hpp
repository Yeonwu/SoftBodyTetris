//
//  engine.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/12/10.
//

#ifndef engine_hpp
#define engine_hpp

#include "graphics.hpp"
#include "physics.hpp"
#include "Types.hpp"
#include "entity.hpp"
#include <vector>

using EventHandler = void (*) (SDL_Event&);

class Engine {
private:
    static Window window;
    
    static bool quit;
    static bool pause;
    
    static Time_millis lastTimeAcc;
    static Time_millis curTime;
    
    static Time_millis lastRender;
    static const Time_millis msPerFrame;
    
    static Time_millis acc;
    static Time_millis total_t;
    
    
    static std::vector<std::pair<SDL_EventType, std::vector<EventHandler>>> eventHandlers;
    static void handleEvent(SDL_Event& event);
    
public:
    static void init();
    static void startLoop();
    static void pauseUpdate();
    static void restartUpdate();
    static void addEventHandler(SDL_EventType eventType, EventHandler handler);
};

#endif /* engine_hpp */
