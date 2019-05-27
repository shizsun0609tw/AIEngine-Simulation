#include "Scene.h"

Scene::Scene()
{
}


Scene::~Scene()
{
}

void Scene::init() {
	srand(time(NULL));

	t = chrono::steady_clock::now();

	myShader = shader("shader.vert", "shader.frag");
	myLight = Light();

	initObstacle();
	initCave();
	initBlueBall();
	initRedBall();
	initGreenBall();


	glUseProgram(myShader.shaderProgram);
}

void Scene::initRedBall() {
	for (int i = 0; i < 5; ++i) {
		int label = 0;
		RedBall temp = RedBall(glm::vec3(rand() % ((int)terrainHeight * 2 - 50) - (terrainHeight - 20), 20.f, rand() % ((int)terrainWidth * 2 - 50) - (terrainWidth - 20)),
			glm::vec3(10.f));
		for (int j = 0; j < myObstacle.size(); ++j) {
			if (glm::distance(temp.getPos(), myObstacle[j].getPos()) < temp.getSize().x + myObstacle[j].getSize().x ||
				glm::distance(temp.getPos(), myObstacle[j].getPos()) < temp.getSize().z + myObstacle[j].getSize().z) {
				label = 1;
				--i;
				break;
			}
		}
		if (label == 0)	myRedBall.push_back(temp);
	}
}

void Scene::initBlueBall() {
	for (int i = 0; i < 20; ++i) {
		int label = 0;
		BlueBall temp = BlueBall(glm::vec3(rand() % ((int)terrainHeight * 2 - 50) - (terrainHeight - 20), 20.f, rand() % ((int)terrainWidth * 2 - 50) - (terrainWidth - 20)),
			glm::vec3(5.f));
		for (int j = 0; j < myObstacle.size(); ++j) {
			if (glm::distance(temp.getPos(), myObstacle[j].getPos()) + 10 < temp.getSize().x + myObstacle[j].getSize().x ||
				glm::distance(temp.getPos(), myObstacle[j].getPos()) + 10 < temp.getSize().z + myObstacle[j].getSize().z) {
				label = 1;
				--i;
				break;
			}
		}
		if (label == 0) myBlueBall.push_back(temp);
	}
}

void Scene::initGreenBall() {
	for (int i = 0; i < 5; ++i) {
		int label = 0;
		GreenBall temp = GreenBall(glm::vec3(rand() % ((int)terrainHeight * 2 - 50) - (terrainHeight - 20), 20.f, rand() % ((int)terrainWidth * 2 - 50) - (terrainWidth - 20)),
			glm::vec3(10.f));
		for (int j = 0; j < myObstacle.size(); ++j) {
			if (glm::distance(temp.getPos(), myObstacle[j].getPos()) < temp.getSize().x + myObstacle[j].getSize().x ||
				glm::distance(temp.getPos(), myObstacle[j].getPos()) < temp.getSize().z + myObstacle[j].getSize().z) {
				label = 1;
				--i;
				break;
			}
		}
		if (label == 0)	myGreenBall.push_back(temp);
	}
}

void Scene::initObstacle() {
	for (int i = 0; i < 10; ++i) {
		int label = 0;
		Obstacle temp = Obstacle(glm::vec3(rand() % ((int)terrainHeight * 2 - 100) - (terrainHeight - 70), terrainDepth / 2, rand() % ((int)terrainWidth * 2 - 100) - (terrainWidth - 70)),
			glm::vec3(rand() % 100 + 100, terrainDepth, rand() % 100 + 100));
		for (int j = 0; j < myObstacle.size(); ++j) {
			if (glm::distance(temp.getPos(), myObstacle[j].getPos()) < temp.getSize().x + myObstacle[j].getSize().x ||
				glm::distance(temp.getPos(), myObstacle[j].getPos()) < temp.getSize().z + myObstacle[j].getSize().z) {
				label = 1;
				--i;
				break;
			}
		}
		if (label == 0)	myObstacle.push_back(temp);
	}
}

void Scene::initCave() {
	for (int i = 0; i < 10; ++i) {
		int label = 0;
		Cave temp = Cave(glm::vec3(rand() % ((int)terrainHeight * 2 - 50) - (terrainHeight - 20), 20.f, rand() % ((int)terrainWidth * 2 - 50) - (terrainWidth - 20)),
			glm::vec3(20.f, 70.f, 20.f));
		for (int j = 0; j < myObstacle.size(); ++j) {
			if (glm::distance(temp.getPos(), myObstacle[j].getPos()) < temp.getSize().x + myObstacle[j].getSize().x ||
				glm::distance(temp.getPos(), myObstacle[j].getPos()) < temp.getSize().z + myObstacle[j].getSize().z) {
				label = 1;
				--i;
				break;
			}
		}
		if (label == 0)	myCave.push_back(temp);
	}
}

void Scene::draw() {
	glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(_var::myViewMatrix));
	glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(_var::myProjectionMatrix));

	// paint light
	myLight.paint(myShader);
	
	// ground
	draw::changeMaterial(whitePlastic, myShader);
	modelMatrix.push(glm::mat4(1.f));
	modelMatrix.top() = glm::translate(modelMatrix.top(), glm::vec3(0.f, 0.f, 0.f));
	modelMatrix.top() = glm::scale(modelMatrix.top(), glm::vec3(terrainHeight * 2, 1.f, terrainWidth * 2));
	glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
	glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(yellow));
	draw::drawCube();
	modelMatrix.pop();
	modelMatrix.empty();

	// obstacle 
	for (int i = 0; i < myObstacle.size(); ++i) {
		modelMatrix.push(glm::mat4(1.f));
		modelMatrix.top() = glm::translate(modelMatrix.top(), myObstacle[i].getPos());
		modelMatrix.top() = glm::scale(modelMatrix.top(), myObstacle[i].getSize());
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(rock));
		draw::drawCube();
		modelMatrix.pop();
	}
	modelMatrix.empty();

	// cave
	for (int i = 0; i < myCave.size(); ++i) {
		modelMatrix.push(glm::mat4(1.f));
		modelMatrix.top() = glm::translate(modelMatrix.top(), myCave[i].getPos());
		modelMatrix.top() = glm::scale(modelMatrix.top(), myCave[i].getSize());
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(darkGreen));
		draw::drawSphere();
		modelMatrix.pop();
	}
	modelMatrix.empty();

	// RedBall 
	for (int i = 0; i < myRedBall.size(); ++i) {
		modelMatrix.push(glm::mat4(1.f));
		modelMatrix.top() = glm::translate(modelMatrix.top(), myRedBall[i].getPos());
		modelMatrix.top() = glm::scale(modelMatrix.top(), myRedBall[i].getSize());
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(red));
		draw::drawSphere();
		modelMatrix.pop();
	}

	// BlueBall 
	for (int i = 0; i < myBlueBall.size(); ++i) {
		modelMatrix.push(glm::mat4(1.f));
		modelMatrix.top() = glm::translate(modelMatrix.top(), myBlueBall[i].getPos());
		modelMatrix.top() = glm::scale(modelMatrix.top(), myBlueBall[i].getSize());
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(blue));
		draw::drawSphere();
		modelMatrix.pop();
	}

	// GreenBall 
	for (int i = 0; i < myGreenBall.size(); ++i) {
		modelMatrix.push(glm::mat4(1.f));
		modelMatrix.top() = glm::translate(modelMatrix.top(), myGreenBall[i].getPos());
		modelMatrix.top() = glm::scale(modelMatrix.top(), myGreenBall[i].getSize());
		glUniformMatrix4fv(glGetUniformLocation(myShader.shaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(modelMatrix.top()));
		glUniform4fv(glGetUniformLocation(myShader.shaderProgram, "color"), 1, glm::value_ptr(green));
		draw::drawSphere();
		modelMatrix.pop();
	}

	modelMatrix.empty();
}

void Scene::update() {
	float passTime = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - t).count() / 1000.f;
	if (passTime / 10 > 1) {
		initBlueBall();
		t = chrono::steady_clock::now();
	}
	// red ball update
	for (int i = 0; i < myRedBall.size(); ++i) {
		if (myRedBall[i].getSize().x < 5.f) {
			myRedBall.erase(myRedBall.begin() + i);
			continue;
		}
		else if (myRedBall[i].getSize().x > 30.f) {
			myRedBall[i].addSize(-15.f);
			myRedBall.push_back(RedBall(myRedBall[i].getPos() - myRedBall[i].getMove() * 3.f, myRedBall[i].getSize()));
			continue;
		}

		float d_MAX = INT_MAX;
		for (int j = 0; j < myBlueBall.size(); ++j) {
			float d = glm::distance(myRedBall[i].getPos(), myBlueBall[j].getPos());
			if (d < myRedBall[i].getSize().x + myBlueBall[j].getSize().x) {
				myBlueBall.erase(myBlueBall.begin() + j);
				myRedBall[i].addSize(1.f);
				myRedBall[i].resetHungryTime();
				myRedBall[i].changeState(RedBall::Search, glm::vec3());
			}
			else if (d < d_MAX && d < myRedBall[i].getSize().x + myBlueBall[j].getSize().x + myRedBall[i].getLookRadius()) {
				d_MAX = d;
				myRedBall[i].changeState(RedBall::Forage, myBlueBall[j].getPos());
			}
		}
		if (d_MAX == INT_MAX) myRedBall[i].changeState(RedBall::Search, glm::vec3());

		for (int j = 0; j < myGreenBall.size(); ++j) {
			if (myGreenBall[j].getState() == GreenBall::Hide) {
				continue;
			}
			float d = glm::distance(myRedBall[i].getPos(), myGreenBall[j].getPos());
			if (myRedBall[i].getSize().x > myGreenBall[j].getSize().x
				&& d < myRedBall[i].getSize().x + myGreenBall[j].getSize().x) {
				myRedBall[i].addSize(myGreenBall[j].getSize().x / 5.f);
				myRedBall[i].resetHungryTime();
				myRedBall[i].changeState(RedBall::Search, glm::vec3());
				myGreenBall.erase(myGreenBall.begin() + j);
			}
			else if (myRedBall[i].getSize().x > myGreenBall[j].getSize().x
				&& d < myRedBall[i].getSize().x + myGreenBall[j].getSize().x + myRedBall[i].getLookRadius()){
				myRedBall[i].changeState(RedBall::Attack, myGreenBall[j].getPos());
			}
		}
		for (int j = 0; j < myObstacle.size(); ++j) {
			myRedBall[i].CollisionDetection(myObstacle[j]);
		}
		myRedBall[i].update();
	}
	// green ball update
	for (int i = 0; i < myGreenBall.size(); ++i) {
		if (myGreenBall[i].getSize().x < 5.f) {
			myGreenBall.erase(myGreenBall.begin() + i);
			continue;
		}
		else if (myGreenBall[i].getSize().x > 30.f) {
			myGreenBall[i].addSize(-15.f);
			myGreenBall.push_back(GreenBall(myGreenBall[i].getPos() - myGreenBall[i].getMove() * 3.f, myGreenBall[i].getSize()));
			continue;
		}

		float d_MAX = INT_MAX;
		for (int j = 0; j < myBlueBall.size(); ++j) {
			float d = glm::distance(myGreenBall[i].getPos(), myBlueBall[j].getPos());
			if (d < myGreenBall[i].getSize().x + myBlueBall[j].getSize().x) {
				myBlueBall.erase(myBlueBall.begin() + j);
				myGreenBall[i].addSize(1.f);
				myGreenBall[i].resetHungryTime();
				myGreenBall[i].changeState(GreenBall::Search, glm::vec3());
			}
			else if (d < d_MAX && d < myGreenBall[i].getSize().x + myBlueBall[j].getSize().x + myGreenBall[i].getLookRadius()) {
				d_MAX = d;
				myGreenBall[i].changeState(GreenBall::Forage, myBlueBall[j].getPos());
			}
		}
		if (d_MAX == INT_MAX) myGreenBall[i].changeState(GreenBall::Search, glm::vec3());
		
		for (int j = 0; j < myRedBall.size(); ++j) {
			float d = glm::distance(myGreenBall[i].getPos(), myRedBall[j].getPos());
			if (myGreenBall[i].getState() == GreenBall::Hide)continue;
			if (myGreenBall[i].getSize().x > myRedBall[j].getSize().x) {
				if (d < myGreenBall[i].getSize().x + myRedBall[j].getSize().x) {
					myGreenBall[i].addSize(myRedBall[j].getSize().x / 5.f);
					myGreenBall[i].resetHungryTime();
					myGreenBall[i].changeState(GreenBall::Search, glm::vec3());
					myRedBall.erase(myRedBall.begin() + j);
				}
				else if (d < myGreenBall[i].getSize().x + myRedBall[j].getSize().x + myGreenBall[i].getLookRadius()) {
					myGreenBall[i].changeState(GreenBall::Attack, myRedBall[j].getPos());
				}
			}
			else if (myGreenBall[i].getSize().x < myRedBall[j].getSize().x) {
				if (d < myGreenBall[i].getSize().x + myRedBall[j].getSize().x + myGreenBall[i].getLookRadius()) {
					myGreenBall[i].changeState(GreenBall::Escape, myRedBall[j].getPos());
					for (int k = 0; k < myCave.size(); ++k) {
						if (myCave[k].isFull() != true && myGreenBall[i].getSize().x < myCave[k].getSize().x) {
							if (fabs(myCave[k].getPos().x - myGreenBall[i].getPos().x) < myCave[k].getSize().x + myGreenBall[i].getSize().x
								&& fabs(myCave[k].getPos().z - myGreenBall[i].getPos().z) < myCave[k].getSize().z + myGreenBall[i].getSize().z) {
								myGreenBall[i].changeState(GreenBall::Hide, glm::vec3());
								myGreenBall[i].setPos(glm::vec3(myCave[k].getPos().x,  myCave[i].getPos().y, myCave[k].getPos().z));
								myCave[k].setOccupy(true);
								break;
							}
							else if (fabs(myCave[k].getPos().x - myGreenBall[i].getPos().x) < myCave[k].getSize().x + myGreenBall[i].getSize().x + myGreenBall[i].getLookRadius()
								&& fabs(myCave[k].getPos().z - myGreenBall[i].getPos().z) < myCave[k].getSize().z + myGreenBall[i].getSize().z + myGreenBall[i].getLookRadius()) {
								myGreenBall[i].changeState(GreenBall::ToHide, myCave[k].getPos());
							}
						}
					}
				}
			}
		}

		for (int j = 0; j < myObstacle.size(); ++j) {
			myGreenBall[i].CollisionDetection(myObstacle[j]);
		}
		myGreenBall[i].update();
	}

	for (int i = 0; i < myCave.size(); ++i) {
		myCave[i].setOccupy(false);
	}

}