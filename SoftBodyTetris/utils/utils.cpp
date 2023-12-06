//
//  utils.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/27.
//

#include "utils.hpp"
#include "Types.hpp"

Color HSVtoRGB(float H, float S,float V) {
    if(H>360 || H<0 || S>100 || S<0 || V>100 || V<0){
        throw "HSV out of range.";
    }
    
    float s = S/100;
    float v = V/100;
    float C = s*v;
    float X = C*(1-abs(fmod(H/60.0, 2)-1));
    float m = v-C;
    float r, g, b;
    if(H >= 0 && H < 60){
        r = C;
        g = X;
        b = 0;
    }
    else if(H >= 60 && H < 120){
        r = X;
        g = C;
        b = 0;
    }
    else if(H >= 120 && H < 180){
        r = 0;
        g = C;
        b = X;
    }
    else if(H >= 180 && H < 240){
        r = 0;
        g = X;
        b = C;
    }
    else if(H >= 240 && H < 300){
        r = X;
        g = 0;
        b = C;
    }
    else{
        r = C;
        g = 0;
        b = X;
    }
    Color color = {
        (u_int8_t) ((r+m)*255),
        (u_int8_t) ((g+m)*255),
        (u_int8_t) ((b+m)*255),
        0xFF
    };
    return color;
}

Position rotate(Position pos, double angle) {
    return {
        pos.x * cos(angle) - pos.y * sin(angle),
        pos.x * sin(angle) + pos.y * cos(angle)
    };
}

