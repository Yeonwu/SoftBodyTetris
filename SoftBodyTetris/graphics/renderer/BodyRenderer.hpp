//
//  BodyRenderer.hpp
//  SoftBodyTetris
//
//  Created by 오연우 on 2023/11/26.
//

#ifndef BodyRenderer_hpp
#define BodyRenderer_hpp

#include <vector>
#include "Types.hpp"
#include "IRenderer.hpp"
#include "PointRenderer.hpp"
#include "ConnectorRenderer.hpp"

struct SpecifiedPointRenderer {
    PointRenderer renderer;
    int idx;
    
    bool operator < (const SpecifiedPointRenderer a) const {
        return this -> idx < a.idx;
    }
};

struct SpecifiedConnectorRenderer {
    ConnectorRenderer renderer;
    int idx;
    
    bool operator < (const SpecifiedConnectorRenderer a) const {
        return this -> idx < a.idx;
    }
};

class BodyRenderer: public IRenderer {
    PointRenderer defaultPointRenderer;
    ConnectorRenderer defaultConnectorRenderer;
    
    std::vector<SpecifiedPointRenderer> specifiedPointRendererList;
    std::vector<SpecifiedConnectorRenderer> specifiedConnectorRendererList;
    
public:
    BodyRenderer ( Color _color, Color _highlightColor );

    void render( Renderable * target, SDL_Renderer* SDLRenderer ) override;
    
    void setPointRenderer(int idx, PointRenderer renderer);
    void setConnectorRenderer(int idx, ConnectorRenderer renderer);
    
    void deletePointRenderer(int idx);
    void deleteConnectorRenderer(int idx);
};

#endif /* BodyRenderer_hpp */
