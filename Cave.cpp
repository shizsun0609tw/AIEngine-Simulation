#include "Cave.h"



Cave::Cave()
{
}

Cave::Cave(glm::vec3 pos, glm::vec3 size) {
	this->pos = pos;
	this->size = size;
}

Cave::~Cave()
{
}

glm::vec3 Cave::getPos() { return pos; }
glm::vec3 Cave::getSize() { return size; }
bool Cave::isFull() { return occupy; }
void Cave::setOccupy(bool in) { occupy = in; }