#include <Windows.h>
#include <gl/GL.h>

class Renderer {
public:
    void clear() {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void setColor(float r, float g, float b) {
        glColor3f(r, g, b);
    }

    void drawQuad(float x, float y, float size) {
        glBegin(GL_QUADS);
        glVertex2f(x - size / 2, y - size / 2);
        glVertex2f(x + size / 2, y - size / 2);
        glVertex2f(x + size / 2, y + size / 2);
        glVertex2f(x - size / 2, y + size / 2);
        glEnd();
    }

    void swapBuffers() {
        glFlush(); // или glutSwapBuffers() для двойной буферизации
    }
};

