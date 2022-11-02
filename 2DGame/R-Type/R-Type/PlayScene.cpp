#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "PlayScene.h"
#include "Game.h"


#define SCREEN_X 0
#define SCREEN_Y 0

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 2

enum PlayerAnims
{
	STAND_UP, STAND_DOWN, STAND_RIGHT, MOVE_UP, MOVE_DOWN, EXPLOSION
};



PlayScene::PlayScene(MenuScene* menuS)
{
	map = NULL;
	player = NULL;	
	tileMapDispl = 0;
	menu = menuS;
	force = NULL;
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
	state = "ON";
	forceHit = false;

	initShaders();
	map = TileMap::createTileMap("levels/level01RTYPE.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	backgroundSpritesheet.loadFromFile("images/nivel1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = Sprite::createSprite(glm::ivec2(3070, 192), glm::vec2(1.0f, 1.0f), &backgroundSpritesheet, &texProgram);
	background->setPosition(glm::vec2(0.0f, 0.0f));
	player = new Player();
	bulletManager.setTileMap(map);

	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, &bulletManager);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

	forceUnitTex.loadFromFile("images/forceUnit.png", TEXTURE_PIXEL_FORMAT_RGBA);
	forceUnit = Sprite::createSprite(glm::ivec2(9, 9), glm::vec2(1.0f, 1.0f), &forceUnitTex, &texProgram);
	
	force = new Force();
	force->init(texProgram);
}



void PlayScene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	bulletManager.update(deltaTime);
	forceUnit->update(deltaTime);
	force->update(deltaTime);

	checkBullets();

	glm::vec2 animationAndKeyframe = player->getAnimationAndKeyframe();
	if(animationAndKeyframe[0] != EXPLOSION)
		tileMapDispl += 1;	
	else {
		if (animationAndKeyframe[1] == 4) state = "MENU";
	}

	forceUnit->setPosition(glm::vec2(500 - tileMapDispl, 100));
	
	//check collision with force unit (28,16 is player size)
	bool forceColX = player->getPosition().x + 28 >= forceUnit->getPosition().x;
	bool forceColY = player->getPosition().y + 16 >= forceUnit->getPosition().y;
	if (forceColX && forceColY && !forceHit) {
		forceHit = true;
		force->enable();
	}

	if (Game::instance().getKey('m') || Game::instance().getKey('M')) {
		state = "MENU";
	}
}

void PlayScene::render()
{
	texProgram.use();	
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	glm::mat4 modelview = glm::translate(glm::mat4(1.0f), glm::vec3(-tileMapDispl, 0.f, 0.f));
	background->setPosition(glm::vec2(35.0f-tileMapDispl, 0.0f));
	background->render();
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);
	map->render();
	player->render();
	bulletManager.render();
	if(!forceHit) forceUnit->render();
	force->render();
}

void PlayScene::checkBullets() {
	vector<Bullet*> activeBullets = bulletManager.ret_actBullets();
	for (int i = 0; i < int(activeBullets.size()); ++i) {
		/*bool collisionX = ((activeBullets[i]->ret_pos().x < (tileMapDispl)) || (activeBullets[i]->ret_pos().x > (SCREEN_WIDTH + tileMapDispl)));
		bool collisionY = (((activeBullets[i]->ret_pos().y < 0) || (activeBullets[i]->ret_pos().y > SCREEN_HEIGHT)));*/

		glm::vec2 bulletPosition = activeBullets[i]->ret_pos();
		if (bulletPosition != glm::vec2(0.0f, 0.0f) && map->collisionMoveRight(glm::ivec2(bulletPosition.x+tileMapDispl+35.0f, bulletPosition.y), glm::ivec2(8, 8))) {
			activeBullets[i]->~Bullet();
			activeBullets.erase(activeBullets.begin() + i);
			bulletManager.set_actBullets(activeBullets);
		}
	}
}
Scene* PlayScene::changeState()
{
	if (state == "MENU") {
		
		menu->init();
		return menu;
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



