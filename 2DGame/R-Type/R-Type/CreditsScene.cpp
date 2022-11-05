#include "CreditsScene.h"
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

CreditsScene::CreditsScene(MenuScene* menuS)
{
	menu = menuS;
}

CreditsScene::~CreditsScene()
{
}

void CreditsScene::init()
{
	state = "ON";
	currentTime = 0.f;

	backgroundTex.loadFromFile("images/creditsScreen.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = Sprite::createSprite(glm::ivec2(512, 256), glm::vec2(1.0f, 1.0f), &backgroundTex, &texProgram);
	background->setPosition(glm::vec2(0.0f, 0.0f));

	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);

	initShaders();
}

void CreditsScene::update(int deltaTime)
{
	currentTime += deltaTime;
	background->update(deltaTime);

	//detectar input de l'usuari i canviar variable 'state'
	if (Game::instance().getKey('m') || Game::instance().getKey('M')) {
		state = "MENU";
	}
}

void CreditsScene::render()
{
	glm::mat4 modelview;
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);

	background->render();
}

Scene* CreditsScene::changeState()
{
	if (state == "MENU") {
		menu->init();
		return menu;
	}
	else if (state == "ON") {
		this->init();
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
