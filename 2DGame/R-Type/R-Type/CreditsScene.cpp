#include "CreditsScene.h"
#include <iostream>

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
	initShaders();
}

void CreditsScene::update(int deltaTime)
{
	currentTime += deltaTime;
	//detectar input de l'usuari i canviar variable 'state'
	if (Game::instance().getKey(32)) {
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
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}
