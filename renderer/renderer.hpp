#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "buffer.hpp"

class StingrayRenderer {
private:
    RenderBuffer &buffer;

public:
    StingrayRenderer(RenderBuffer &buffer) : buffer(buffer) { };

    // Renders a portion of the image (in a rectangle)
    void render(int startX, int startY, int endX, int endY); 
};

#endif