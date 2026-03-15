#pragma once
#include <windows.h>
//#include <glm/glm.hpp>
//#include <GL/gl.h>
class Primitive
{
public:
	Primitive() = default;
	~Primitive() = default;
	//virtual void setColor(glm::vec4 c) { color = c; };
private:
	//glm::vec4 color{ 1.0f, 0.0f, 0.0f, 1.0f };
	bool isVisible;
};

class Square : Primitive
{

private:

};