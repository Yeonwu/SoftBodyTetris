//
//  IRenderer.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/20.
//

#include "IRenderer.hpp"

template <typename Renderable>
IRenderer<Renderable>::IRenderer(Renderable * _target, Color _color):
    target(_target),
    color(_color)
{}

template <typename Renderable>
void IRenderer<Renderable>::setWindow(Window * _window) {
    IRenderer<Renderable>::window = _window;
}
