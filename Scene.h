#pragma once

#include "Definition.h"
#include "shader.h"
#include "_var.h"
#include "draw.h"
#include "Light.h"
#include "Obstacle.h"
#include "RedBall.h"
#include "BlueBall.h"
#include "GreenBall.h"
#include "Cave.h"
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>

class Scene
{
public:
	Scene();
	~Scene();
	void init();
	void draw();
	void update();
private:
	stack<glm::mat4> modelMatrix;
	shader myShader;
	Light myLight;
	chrono::steady_clock::time_point t;
	void initRedBall();
	void initBlueBall();
	void initGreenBall();
	void initObstacle();
	void initCave();
	vector<Obstacle> myObstacle;
	vector<Cave> myCave;
	vector<RedBall> myRedBall;
	vector<BlueBall> myBlueBall;
	vector<GreenBall> myGreenBall;
};

