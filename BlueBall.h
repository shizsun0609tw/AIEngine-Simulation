#pragma once
#include "Definition.h"
#include "_var.h"
#include <glm/glm.hpp>
#include <cstdlib>

class BlueBall
{
public:
	BlueBall();
	BlueBall(glm::vec3 pos, glm::vec3 size);
	~BlueBall();
	glm::vec3 getPos();
	glm::vec3 getSize();
private:
	glm::vec3 pos;
	glm::vec3 size;
};

