#pragma once
#include "Renderer.h"
#include <vector>
struct Point {
    float x, y;
};

class DrawingManager {
public:
    void addPoint(float x, float y) {
        points.push_back({ x, y });
    }

    void clear() {
        points.clear();
    }

    void draw() {
        if (points.size() < 2) return;

        glColor3f(1.0f, 1.0f, 1.0f);
        glBegin(GL_LINE_STRIP);
        for (const auto& p : points) {
            glVertex2f(p.x, p.y);
        }
        glEnd();
    }

    bool isEmpty() const {
        return points.empty();
    }

private:
    std::vector<Point> points;
};

class Visualizer {
public:
    Visualizer() : drawing(false) {}

    void display() {
        renderer.clear();


        if (!drawingManager.isEmpty()) {
            drawingManager.draw();
        }
        if (drawing && !tempPoints.empty()) {
            glColor3f(1.0f, 1.0f, 0.0f);
            glBegin(GL_LINE_STRIP);
            for (const auto& p : tempPoints) {
                glVertex2f(p.x, p.y);
            }
            glEnd();
        }

        renderer.swapBuffers();
    }

    void startDrawing(float x, float y) {
        drawing = true;
        tempPoints.clear();
        tempPoints.push_back({ x, y });
    }

    void continueDrawing(float x, float y) {
        if (drawing) {
            tempPoints.push_back({ x, y });
        }
    }

    void finishDrawing() {
        if (drawing && !tempPoints.empty()) {
            for (const auto& p : tempPoints) {
                drawingManager.addPoint(p.x, p.y);
            }
        }
        drawing = false;
        tempPoints.clear();
    }

private:
    Renderer renderer;
    DrawingManager drawingManager;
    std::vector<Point> tempPoints;
    bool drawing;
};