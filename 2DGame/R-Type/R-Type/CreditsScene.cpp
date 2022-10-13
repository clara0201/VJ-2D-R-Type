#include "CreditsScene.h"

CreditsScene::CreditsScene(MenuScene* menuS)
{
	menu = menuS;
}

CreditsScene::~CreditsScene()
{
}

void CreditsScene::init()
{
	//placeholder
	glClearColor(0.3f, 0.9f, 0.9f, 1.0f);

	state = "ON";

	currentTime = 0.f;
	//initShaders();
}

void CreditsScene::update(int deltaTime)
{
	currentTime += deltaTime;
	//detectar input de l'usuari i canviar variable 'state'
	if (Game::instance().getKey('1')) {
		state = "MENU";
	}
}

void CreditsScene::render()
{
}

Scene* CreditsScene::changeState()
{
	if (state == "MENU") {
		menu->init();
		return menu;
	}

	return this;
}

void CreditsScene::initShaders()
{
}
