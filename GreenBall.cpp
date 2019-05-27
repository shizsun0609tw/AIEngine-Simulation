#include "GreenBall.h"
#include "Obstacle.h"


GreenBall::GreenBall()
{
}

GreenBall::GreenBall(glm::vec3 pos, glm::vec3 size) {
	this->pos = pos;
	this->size = size;
	this->move = glm::normalize(glm::vec3(rand() % 100 - rand() % 100, 0.f, rand() % 100 - rand() % 100));
	this->t = chrono::steady_clock::now();
	this->hungryTime = chrono::steady_clock::now();
}

GreenBall::~GreenBall()
{
}

void GreenBall::setPos(glm::vec3 pos) { this->pos = pos; }
glm::vec3 GreenBall::getPos() { return pos; }
glm::vec3 GreenBall::getSize() { return size; }
glm::vec3 GreenBall::getMove() { return move; }
GreenBall::State GreenBall::getState() { return myState;}
float GreenBall::getLookRadius() { return lookRadius; }

void GreenBall::update() {
	float passTime = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - t).count() / 1000.f;
	float hungryPassTime = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - hungryTime).count() / 1000.f;
	t = chrono::steady_clock::now();
	pos += move * passTime * speed;

	while (pos.x + size.x > terrainHeight || pos.x - size.x < -terrainHeight || pos.x + size.x > terrainWidth || pos.x - size.x < -terrainWidth
		|| pos.z + size.z > terrainHeight || pos.z - size.z < -terrainHeight || pos.z + size.z > terrainWidth || pos.z - size.z < -terrainWidth) {
		pos -= move * passTime * speed;
		move = glm::normalize(glm::vec3(rand() % 100 - rand() % 100, 0.f, rand() % 100 - rand() % 100));
		pos += move * passTime * speed;
	}

	if (hungryPassTime > 10.f) {
		hungryTime = chrono::steady_clock::now();
		size -= 2.f;
	}
}

void GreenBall::addSize(float s) {
	size += s;
}

void GreenBall::resetHungryTime() {
	hungryTime = chrono::steady_clock::now();
}

void GreenBall::CollisionDetection(Obstacle object) {
	glm::vec3 temp = pos + move;
	int times = 0;

	while (times < 10
		&& (temp.x - object.getPos().x) * (temp.x - object.getPos().x) < (size.x + object.getSize().x / 2) * (size.x + object.getSize().x / 2)
		&& (temp.y - object.getPos().y) * (temp.y - object.getPos().y) < (size.y + object.getSize().y / 2) * (size.y + object.getSize().y / 2)
		&& (temp.z - object.getPos().z) * (temp.z - object.getPos().z) < (size.z + object.getSize().z / 2) * (size.z + object.getSize().z / 2)) {
		if (times == 0) pos -= move;

		move = glm::vec3(glm::rotate(glm::mat4(1.f), glm::radians((rand() % 360 - rand() % 360) * 1.f), glm::vec3(0.f, 1.f, 0.f)) * glm::vec4(move, 1.f));
		temp = pos + move;
		times++;
	}
	if (times == 10) move *= -1;
}

void GreenBall::changeState(State s, glm::vec3 target) {
	switch (s)
	{
	case Search:
		speed = 30.f;
		myState = Search;
		break;
	case Attack:
		speed = 60.f;
		move = glm::normalize(target - pos);
		myState = Attack;
		break;
	case Forage:
		speed = 60.f;
		move = glm::normalize(target - pos);
		myState = Forage;
		break;
	case Escape:
		speed = 50.f;
		move = glm::normalize(pos - target);
		myState = Escape;
		break;
	case Hide:
		speed = 0.f;
		myState = Hide;
		break;
	case ToHide:
		speed = 50.f;
		move = glm::normalize(target - pos);
		myState = ToHide;
	default:
		break;
	}
}