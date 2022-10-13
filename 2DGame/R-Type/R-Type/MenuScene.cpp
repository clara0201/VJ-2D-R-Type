#include "MenuScene.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/freeglut_std.h>
#include "PlayScene.h"
#include "CreditsScene.h"
#include "InstructionsScene.h"

MenuScene::MenuScene()
{
	playS = new PlayScene(this);
	instructionsS = new InstructionsScene(this);
	creditsS = new CreditsScene(this);
}

MenuScene::~MenuScene()
{
}

void MenuScene::init()
{
	//placeholder
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	currentTime = 0.f;
	state = ON;
	

	
	//initShaders();
	
	//fontText.loadFromFile("images/font.bmp", TEXTURE_PIXEL_FORMAT_RGB);

	
}

void MenuScene::update(int deltaTime)
{
	currentTime += deltaTime;
	//detectar input de l'usuari i canviar variable 'state'
	if (Game::instance().getKey('2')) {
		state = PLAY;
	}
	else if (Game::instance().getKey('3')) {
		state = INSTRUCTIONS;
	}
	else if (Game::instance().getKey('4')) {
		state = CREDITS;
	}
}

void MenuScene::render()
{
}

Scene* MenuScene::changeState()
{
	switch (state) {
	case PLAY: {
		playS->init();
		return playS;
	}
	
	case INSTRUCTIONS: {
		instructionsS->init();
		return instructionsS;
	}

	case CREDITS: {
		creditsS->init();
		return creditsS;
	}
	/*
	case EXIT:
		//per implementar
		break;
	*/

	default:
		break;
	}
	return this;
}




void MenuScene::initShaders() {
	
}
