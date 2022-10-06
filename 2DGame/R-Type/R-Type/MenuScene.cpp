#include "MenuScene.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/freeglut_std.h>
#include "PlayScene.h"
#include "CreditsScene.h"
#include "InstructionsScene.h"

MenuScene::MenuScene()
{
}

MenuScene::~MenuScene()
{
}

void MenuScene::init()
{
	//placeholder
	glClearColor(0.9f, 0.3f, 0.3f, 1.0f);
	
	currentTime = 0.f;
	state = ON;
	//initShaders();

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
		Scene* scene = new PlayScene();
		scene->init();
		return scene;
	}
	
	case INSTRUCTIONS: {
		Scene* instructions = new InstructionsScene();
		instructions->init();
		return instructions;
	}
	case CREDITS: {
		Scene* credits = new CreditsScene();
		credits->init();
		return credits;
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




void MenuScene::initShaders()
{
	
}
