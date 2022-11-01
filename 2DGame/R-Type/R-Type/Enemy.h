#pragma once
#include "ShaderProgram.h"
class Enemy
{

public:
	void init();
	void update(int deltaTime);
	void render();

private:
	int typeOfEnemy, health;
	ShaderProgram* shaderProgram;

};

