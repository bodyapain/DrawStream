#include <Windows.h>
#include <iostream>
#include <GL/glut.h>

#include "Visualizer.h"
Visualizer* gVis = nullptr;

void displayCallback() {
    if (gVis) gVis->display();
}


int main()
{
    int argc = 1;
    char* argv[1] = { (char*)"dummy" };

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // 2. Режим отображения
    glutInitWindowSize(800, 600);           // 3. Размер окна
    glutCreateWindow("Square");              // 4. Создание окна
    Visualizer vis;
    gVis = &vis;
    glutDisplayFunc(displayCallback);
    glutMainLoop();
    return 0;
}

