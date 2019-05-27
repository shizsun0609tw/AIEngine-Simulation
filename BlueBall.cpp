#include "BlueBall.h"



BlueBall::BlueBall()
{
}

BlueBall::BlueBall(glm::vec3 pos, glm::vec3 size) {
	this->pos = pos;
	this->size = size;
}

BlueBall::~BlueBall()
{
}

glm::vec3 BlueBall::getPos() { return pos; }
glm::vec3 BlueBall::getSize() { return size; }
