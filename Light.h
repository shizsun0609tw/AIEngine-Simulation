#pragma once

#include "Definition.h"
#include "_var.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shader.h"

struct light {
	glm::vec3 position;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	bool mode;
	float exponent;
	float cutoff;
	float outerCutoff;

	glm::vec3 direction;
	float light_theta;
	float light_fi;
};

class Light
{
public:
	Light();
	~Light();
	void paint(shader s);
private:
	static light myLight[3];
};

