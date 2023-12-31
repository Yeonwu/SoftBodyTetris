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
public:
    SDL_Window *window;
    SDL_Renderer *renderer;
    
    Window( int screen_width, int screen_height );
    ~Window();
    
    void update();
    void clear();
    
    void renderPoint ( const IPoint& p );
    void renderPoint ( const IPoint& p, Color c );
    
    void renderPoint ( const MassPoint& p );
    
    void renderPoint ( const FixedPoint& p );
    void renderPoint ( const FixedPoint& p, Color c );
    
    void renderConnector ( IConnector& c, int flag=0 );
    void renderConnector ( ElasticConnector& ec );
    
    void renderBody ( const IBody& b, int flag=0 );
};


#endif /* Window_hpp */
