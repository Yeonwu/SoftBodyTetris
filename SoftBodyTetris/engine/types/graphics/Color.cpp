//
//  Color.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/30.
//

#include "Color.hpp"

_Color::_Color(u_int8_t _R, u_int8_t _G, u_int8_t _B, u_int8_t _A):
R(_R),
G(_G),
B(_B),
A(_A) {}

_Color::_Color(u_int8_t _R, u_int8_t _G, u_int8_t _B):
R(_R),
G(_G),
B(_B),
A(0xFF) {}
