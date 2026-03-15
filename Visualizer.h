#pragma once
#include "Renderer.h"
class Visualizer
{
public:
    void display() {
        renderer.clear();
        renderer.setColor(1.0f, 0.5f, 1.0f); // белый
        renderer.drawQuad(0.0f, 0.0f, 1.0f);
        renderer.swapBuffers();
    }
private:
	Renderer renderer;
};

