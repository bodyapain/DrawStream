#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <GL/glut.h>
#include <thread>
#include "Visualizer.h"
#include "Sender.h"
#include <vector>
Visualizer* gVis = nullptr;
Sender* gSender = nullptr;

void displayCallback() {
    if (gVis) {
        gVis->display();
        if (gSender) {
            int width = 800, height = 600;
            std::vector<char> pixels(width * height * 3);
            glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

            gSender->prepareBuffers(pixels, pixels.size());
            gSender->send();
        }
    }
}void convertMouseCoords(int mouseX, int mouseY, float& outX, float& outY) {
    int width = 800, height = 600;
    outX = (2.0f * mouseX / width) - 1.0f;
    outY = 1.0f - (2.0f * mouseY / height);
}

void mouseCallback(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        float glX, glY;
        convertMouseCoords(x, y, glX, glY);
        if (gVis) {
            gVis->startDrawing(glX, glY);
        }
    }
    else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        if (gVis) {
            gVis->finishDrawing();
        }
    }
}


void motionCallback(int x, int y) {
    float glX, glY;
    convertMouseCoords(x, y, glX, glY);
    if (gVis) {
        gVis->continueDrawing(glX, glY);
        glutPostRedisplay(); 
    }
}


int main() {
    int argc = 1;
    char* argv[1] = { (char*)"dummy" };

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Streamer - Sending Window");

    Visualizer vis;
    gVis = &vis;
    Sender sender;
    gSender = &sender;
    sender.connectToServer("127.0.0.1", "8888");
    gSender->startStream();
    glutDisplayFunc(displayCallback);
    glutMouseFunc(mouseCallback);
    glutMotionFunc(motionCallback);
    glutMainLoop();
    return 0;
}