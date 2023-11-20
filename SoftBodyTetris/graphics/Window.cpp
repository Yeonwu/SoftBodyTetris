//
//  Window.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/10/26.
//

#include "Window.hpp"

#include <SDL2/SDL.h>
#include <stdio.h>

Window::Window( int screen_width, int screen_height ) {
    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        printf( "Couldn't initialize! SDL Error: %s\n", SDL_GetError() );
        throw 0;
    }
    
    window = SDL_CreateWindow(
        "Tetris",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        screen_width,
        screen_height,
        SDL_WINDOW_SHOWN
    );
    
    if ( window == NULL ) {
        printf( "Couldn't create window! SDL Error: %s\n", SDL_GetError() );
        throw 0;
    }
    
    renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
    
    if ( renderer == NULL ) {
        printf( "Couldn't create renderer! SDL Error: %s\n", SDL_GetError() );
    }
}

Window::~Window() {
    SDL_DestroyWindow( window );
    SDL_DestroyRenderer ( renderer );
    SDL_Quit();
}

void Window::update() {
    SDL_RenderPresent( renderer );
}

void Window::clear() {
    SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00 );
    SDL_RenderClear( renderer );
}

void Window::renderPoint ( const IPoint& p ) {
    Position pos = p.getPosition();
    SDL_FRect rect = {(float)pos.x - 3, (float)pos.y - 3, 6, 6};
    
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderDrawRectF(renderer, &rect);
}

void Window::renderPoint ( const MassPoint& p ) {
    Position pos = p.getPosition();
    SDL_FRect rect = {(float)pos.x - 3, (float)pos.y - 3, 6, 6};
    
    SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );
    SDL_RenderDrawRectF(renderer, &rect);
}

void Window::renderPoint ( const FixedPoint& p ) {
    Position pos = p.getPosition();
    SDL_FRect rect = {(float)pos.x - 3, (float)pos.y - 3, 6, 6};
    
    SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderDrawRectF(renderer, &rect);
}

void Window::renderConnector ( const IConnector& c, int flag ) {
    Position pos0 = c.getPoint(0) -> getPosition();
    Position pos1 = c.getPoint(1) -> getPosition();
    
    if (flag) {
        SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
    } else {
        SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    }
    SDL_RenderDrawLine( renderer, pos0.x, pos0.y, pos1.x, pos1.y);
}

void Window::renderConnector ( const ElasticConnector& ec ) {
    Position pos0 = ec.getPoint(0) -> getPosition();
    Position pos1 = ec.getPoint(1) -> getPosition();
    
    double l = ec.getLength();
    double d = (pos0 - pos1).size();
    Position m = (pos0 + pos1) / 2;
    
    
    Position pos2 = m + (pos0 - pos1)/d * l/2;
    Position pos3 = m + (pos1 - pos0)/d * l/2;
    
    SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
    SDL_RenderDrawLine( renderer, pos2.x, pos2.y, pos3.x, pos3.y);
    
    SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderDrawLine( renderer, pos0.x, pos0.y, pos3.x, pos3.y);

    SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderDrawLine( renderer, pos2.x, pos2.y, pos1.x, pos1.y);
}


void Window::renderConnector ( const NonElasticConnector & nec) {
    Position pos0 = nec.getPoint(0) -> getPosition();
    Position pos1 = nec.getPoint(1) -> getPosition();
    
    if ( (pos0 - pos1).size() < nec.getLength() ) {
        SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0x00);
    } else {
        SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0x00, 0x00);
    }
    
    SDL_RenderDrawLine( renderer, pos0.x, pos1.y, pos0.x, pos1.y);
}

void Window::renderBody( const IBody & b, int flag ) {
    for ( const IPoint* p: b.getPoints() ) {
        renderPoint(*p);
    }
    
    for ( const IConnector* c: b.getConnectors() ) {
        renderConnector(*c, flag);
    }
}
