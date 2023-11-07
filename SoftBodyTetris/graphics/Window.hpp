//
//  Window.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/10/26.
//

#ifndef Window_hpp
#define Window_hpp

#include <SDL2/SDL.h>

#include "physics.hpp"

class Window {
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
public:
    Window( int screen_width, int screen_height );
    ~Window();
    
    void update();
    void clear();
    
    void renderMassPoint ( const MassPoint& p );
    void renderFixedPoint ( const FixedPoint& p );
    
    void renderElasticConnector ( const ElasticConnector& ec );
};


#endif /* Window_hpp */
