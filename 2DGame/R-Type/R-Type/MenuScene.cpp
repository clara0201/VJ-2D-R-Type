#include "MenuScene.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/freeglut_std.h>
#include "PlayScene.h"
#include "CreditsScene.h"
#include "InstructionsScene.h"

MenuScene::MenuScene()
{
	//playS = new PlayScene(this);
	instructionsS = new InstructionsScene(this);
	creditsS = new CreditsScene(this);
}

MenuScene::~MenuScene()
{
}

void MenuScene::init()
{
	
	
	currentTime = 0.f;
	state = ON;
	
	//Background
	backgroundTex.loadFromFile("images/titleScreen.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = Sprite::createSprite(glm::ivec2(512,256), glm::vec2(1.0f,1.0f), &backgroundTex, &texProgram);
	background->setPosition(glm::vec2(0.0f, 0.0f));

	blastTex.loadFromFile("images/blast.png", TEXTURE_PIXEL_FORMAT_RGBA);
	arrow = Sprite::createSprite(glm::ivec2(28, 8), glm::vec2(1.0f, 1.0f), &blastTex, &texProgram);
	arrow->setPosition(glm::vec2(100.0f, 50.0f));


	initShaders();
	
}

void MenuScene::update(int deltaTime)
{
	currentTime += deltaTime;
	background->update(deltaTime);
	arrow->update(deltaTime);

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
	
	background->render();
	arrow->render();
	
}

Scene* MenuScene::changeState()
{
	switch (state) {
	case PLAY: {
		playS = new PlayScene(this);
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




void MenuScene::initShaders() 
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
