#pragma once
#include "Definition.h"
#include "_var.h"
#include <glm/glm.hpp>

class Obstacle
{
public:
	Obstacle();
	Obstacle(glm::vec3 pos, glm::vec3 size);
	~Obstacle();
	glm::vec3 getPos();
	glm::vec3 getSize();
private:
	glm::vec3 pos;
	glm::vec3 size;
};

