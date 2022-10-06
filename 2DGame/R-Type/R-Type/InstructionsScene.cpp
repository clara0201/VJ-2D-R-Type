#include "InstructionsScene.h"

InstructionsScene::InstructionsScene()
{
}

InstructionsScene::~InstructionsScene()
{
}

void InstructionsScene::init()
{
	//placeholder
	glClearColor(0.0f, 0.9f, 0.0f, 1.0f);

	state = "ON";

	currentTime = 0.f;
	//initShaders();
}

void InstructionsScene::update(int deltaTime)
{
	currentTime += deltaTime;
	//detectar input de l'usuari i canviar variable 'state'
	if (Game::instance().getKey('1')) {
		state = "MENU";
	}
}

void InstructionsScene::render()
{
}

Scene* InstructionsScene::changeState()
{
	if (state == "MENU") {
		Scene* scene = new MenuScene();
		scene->init();
		return scene;
	}

	return this;
}

void InstructionsScene::initShaders()
{
}
