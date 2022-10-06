#pragma once
#include "Scene.h"
#include "ShaderProgram.h"
#include "Game.h"
class CreditsScene : public Scene
{

public:
    CreditsScene();
    ~CreditsScene();

	void init();
	void update(int deltaTime);
	void render();
	virtual Scene* changeState();

private:
	void initShaders();

private:
	ShaderProgram texProgram;
	float currentTime;
	string state;
};

