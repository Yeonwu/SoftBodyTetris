//
//  BodyRenderer.cpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/26.
//

#include <algorithm>
#include "BodyRenderer.hpp"
#include "IBody.hpp"

BodyRenderer::BodyRenderer ( Color _color, Color _highlightColor ):
IRenderer( _color ),
defaultPointRenderer( _color ),
defaultConnectorRenderer( _color, _highlightColor )
{}

void BodyRenderer::render( Renderable * target, SDL_Renderer* SDLRenderer ) {
    IBody* body = dynamic_cast<IBody*>(target);
    
    std::vector<IPoint*> points = body -> getPoints();
    
    for ( int idx = 0, rendererIt = 0; idx < points.size(); idx++ ) {
        if ( !specifiedPointRendererList.empty() && specifiedPointRendererList.size() > rendererIt) {
            auto specifiedRenderer = specifiedPointRendererList.at(rendererIt);
            
            if ( specifiedRenderer.idx == idx ) {
                specifiedPointRendererList.at(rendererIt).renderer.render( points[idx], SDLRenderer );
                rendererIt ++;
                continue;
            }
        }
        
        defaultPointRenderer.render( points[idx], SDLRenderer );
    }
    
    std::vector<IConnector*> connectors = body -> getConnectors();
    
    for ( int idx = 0, rendererIt = 0; idx < connectors.size(); idx++ ) {
        if ( !specifiedConnectorRendererList.empty() && specifiedConnectorRendererList.size() > rendererIt) {
            auto specifiedRenderer = specifiedConnectorRendererList.at(rendererIt);
            
            if ( specifiedRenderer.idx == idx ) {
                specifiedConnectorRendererList.at(rendererIt).renderer.render( connectors[idx], SDLRenderer );
                rendererIt ++;
                continue;
            }
        }
        
        defaultConnectorRenderer.render( connectors[idx], SDLRenderer );
    }
}

template<class T>
void insert_sorted(std::vector<T>& v, const T& item) {
    const auto insert_pos(std::lower_bound(begin(v), end(v), item));
    v.insert(insert_pos, item);
}

template<class T>
void delete_sorted(std::vector<T>& v, const T& item) {
    if (v.size() == 0) return;
    auto targetIt = std::lower_bound( v.begin(), v.end(), item );
    if ( targetIt != v.end() ) {
        v.erase(targetIt);
    }
}

void BodyRenderer::setPointRenderer(int idx, PointRenderer renderer) {
    deletePointRenderer( idx );
    
    struct SpecifiedPointRenderer newPointRenderer{renderer, idx};
    insert_sorted(specifiedPointRendererList, newPointRenderer);
}

void BodyRenderer::setConnectorRenderer(int idx, ConnectorRenderer renderer) {
    deleteConnectorRenderer( idx );
    
    struct SpecifiedConnectorRenderer newConnectorRenderer{renderer, idx};
    insert_sorted(specifiedConnectorRendererList, newConnectorRenderer);
}

void BodyRenderer::deletePointRenderer(int idx) {
    struct SpecifiedPointRenderer target{defaultPointRenderer, idx};
    delete_sorted(specifiedPointRendererList, target);
}

void BodyRenderer::deleteConnectorRenderer(int idx) {
    struct SpecifiedConnectorRenderer target{defaultConnectorRenderer, idx};
    delete_sorted(specifiedConnectorRendererList, target);
}
