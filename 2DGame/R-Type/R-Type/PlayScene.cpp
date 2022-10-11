#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "PlayScene.h"
#include "Game.h"


#define SCREEN_X 16
#define SCREEN_Y 128

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 2


PlayScene::PlayScene()
{
	map = NULL;
	player = NULL;	
	tileMapDispl = 0;
}

PlayScene::~PlayScene()
{
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
}


void PlayScene::init()
{
	//placeholder
	glClearColor(0.3f, 0.3f, 0.9f, 1.0f);

	state = "ON";

	initShaders();
	map = TileMap::createTileMap("levels/level01RTYPE.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);

	player = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}
void PlayScene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	tileMapDispl += 2;
	//canviar condicio 
	if (Game::instance().getKey('1')) {
		state = "MENU";
	}
}

void PlayScene::render()
{
	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(-tileMapDispl, 0.f, 0.f));
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	player->render();
}

Scene* PlayScene::changeState()
{
	if (state == "MENU") {
		Scene* scene = new MenuScene();
		scene->init();
		return scene;
	}
		
	return this;
}

void PlayScene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if(!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if(!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if(!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}



