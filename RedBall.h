#pragma once
#include "Definition.h"
#include "_var.h"
#include <glm/glm.hpp>
#include <chrono>

class Obstacle;

class RedBall
{
public:
	RedBall();
	RedBall(glm::vec3 pos, glm::vec3 size);
	~RedBall(); 
	enum State { Search, Attack, Forage};
	glm::vec3 getPos();
	glm::vec3 getSize();
	glm::vec3 getMove();
	float getLookRadius();
	void update();
	void addSize(float s);
	void resetHungryTime();
	void CollisionDetection(Obstacle object);
	void changeState(State s, glm::vec3 target);
private:
	glm::vec3 pos;
	glm::vec3 size;
	glm::vec3 move;
	float speed = 30.f;
	float lookRadius = 100.f;
	chrono::steady_clock::time_point t;
	chrono::steady_clock::time_point hungryTime;
	State myState = Search;
};

