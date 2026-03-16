#define WIN32_LEAN_AND_MEAN
#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <GL/glut.h>
#include <thread>
#include "Visualizer.h"
#include "Sender.h"

Visualizer* gVis = nullptr;
Sender* gSender = nullptr;

void displayCallback() {
    if (gVis) {
        gVis->display();

        // После отрисовки захватываем кадр и отправляем
        if (gSender) {
            // Здесь нужно захватить пиксели из OpenGL
            int width = 800, height = 600;
            std::vector<char> pixels(width * height * 3);
            glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

            gSender->prepareBuffers(pixels, pixels.size());
            gSender->send();
        }
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

    // Создаем отправитель и подключаемся к клиенту
    Sender sender;
    gSender = &sender;
    sender.connectToServer("127.0.0.1", "8888");
    gSender->startStream();

    glutDisplayFunc(displayCallback);
    glutMainLoop();
    return 0;
}