//
//  Color.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/30.
//

#ifndef Color_hpp
#define Color_hpp

#include <stdint.h>

typedef struct _Color {
    u_int8_t R;
    u_int8_t G;
    u_int8_t B;
    
    u_int8_t A;
    
    _Color(u_int8_t _R, u_int8_t _G, u_int8_t _B, u_int8_t _A);
    _Color(u_int8_t _R, u_int8_t _G, u_int8_t _B);
    
} Color;

#endif /* Color_hpp */
