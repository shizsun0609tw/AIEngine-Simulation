#include "Obstacle.h"



Obstacle::Obstacle()
{
}

Obstacle::Obstacle(glm::vec3 pos, glm::vec3 size) {
	this->pos = pos;
	this->size = size;
}

Obstacle::~Obstacle()
{
}

glm::vec3 Obstacle::getPos() { return pos; }

glm::vec3 Obstacle::getSize() { return size; }