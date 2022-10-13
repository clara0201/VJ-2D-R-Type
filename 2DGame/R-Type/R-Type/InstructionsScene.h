#pragma once
#include "Scene.h"
#include "ShaderProgram.h"
#include "Game.h"

class InstructionsScene : public Scene
{
public:
	InstructionsScene(MenuScene* menuS);
	~InstructionsScene();

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
	MenuScene* menu;
};

