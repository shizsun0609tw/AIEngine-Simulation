#pragma once
#include "Definition.h"
#include "_var.h"
#include <glm/glm.hpp>
class Cave
{
public:
	Cave();
	Cave(glm::vec3 pos, glm::vec3 size);
	~Cave();
	glm::vec3 getPos();
	glm::vec3 getSize();
	bool isFull();
	void setOccupy(bool in);
private:
	glm::vec3 pos;
	glm::vec3 size;
	bool occupy = false;
};

