#pragma once

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Scene.h"
#include "Texture.h"
#include "Sprite.h"



// MenuScene contains the entities leading to all the states of the game


class MenuScene : public Scene
{

public:
	MenuScene();
	~MenuScene();

	void init();
	void update(int deltaTime);
	void render();
	virtual Scene* changeState();

private:
	void initShaders();

private:
	//other stuff
	ShaderProgram texProgram;
	enum MenuState {
		ON,
		PLAY,
		EXIT,
		INSTRUCTIONS,
		CREDITS,
	};
	MenuState state;
	float currentTime;
	Scene* playS, * instructionsS, * creditsS;
	Texture backgroundTex, blastTex;
	Sprite* background,  * arrow; 
	glm::mat4 projection;

	int option;
};

