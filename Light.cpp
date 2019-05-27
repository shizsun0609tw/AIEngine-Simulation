#include "Light.h"



Light::Light()
{
	myLight[DIRECTIONAL_LIGHT].ambient = glm::vec3(0.75f, 0.75f, 0.75f);
	myLight[DIRECTIONAL_LIGHT].diffuse = glm::vec3(0.75f, 0.75f, 0.75f);
	myLight[DIRECTIONAL_LIGHT].specular = glm::vec3(0.f, 0.f, 0.f);
	myLight[DIRECTIONAL_LIGHT].direction = glm::vec3(0.f, -1.f, 0.f);
	myLight[DIRECTIONAL_LIGHT].light_theta = 0.f;
	myLight[DIRECTIONAL_LIGHT].light_fi = 0.f;
	myLight[DIRECTIONAL_LIGHT].exponent = 8.f;
	myLight[DIRECTIONAL_LIGHT].cutoff = 180.f;
	myLight[DIRECTIONAL_LIGHT].mode = LIGHT_ON;
}


Light::~Light()
{
}

light Light::myLight[3];

void Light::paint(shader s) {
	glUniform3fv(glGetUniformLocation(s.shaderProgram, "myDirectionalLight.ambient"), 1, glm::value_ptr(myLight[DIRECTIONAL_LIGHT].ambient));
	glUniform3fv(glGetUniformLocation(s.shaderProgram, "myDirectionalLight.diffuse"), 1, glm::value_ptr(myLight[DIRECTIONAL_LIGHT].diffuse));
	glUniform3fv(glGetUniformLocation(s.shaderProgram, "myDirectionalLight.specular"), 1, glm::value_ptr(myLight[DIRECTIONAL_LIGHT].specular));
	glUniform3fv(glGetUniformLocation(s.shaderProgram, "myDirectionalLight.direction"), 1, glm::value_ptr(myLight[DIRECTIONAL_LIGHT].direction));

	glUniform3fv(glGetUniformLocation(s.shaderProgram, "eyePos"), 1, glm::value_ptr(_var::myEye.pos));
}