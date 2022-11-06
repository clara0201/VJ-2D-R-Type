#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "PlayScene.h"
#include "Game.h"
#include "Enemy.h"

#define SCREEN_X 0
#define SCREEN_Y 0
#define FLOWER 0
#define BUTTERFLY 1
#define BOSS 3



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
	for (int i = 0; i < enemyList.size(); ++i)		
		enemyList[i] = NULL;
	for (int i = 0; i < flowerList.size(); ++i)
		enemyList[i] = NULL;
	cooldown = 5;
	directionCooldown = 300;
	butterflyShootCooldown = 50;
	movingUp = true;
	flowerIterator = 0;
	invCooldown = 0;
}


void PlayScene::init()
{
	state = "ON";
	forceHit = false;
	invCooldown = 0;

	initShaders();
	map = TileMap::createTileMap("levels/level01RTYPE.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	backgroundSpritesheet.loadFromFile("images/nivel1.png", TEXTURE_PIXEL_FORMAT_RGBA);
	background = Sprite::createSprite(glm::ivec2(3070, 192), glm::vec2(1.0f, 1.0f), &backgroundSpritesheet, &texProgram);
	background->setPosition(glm::vec2(0.0f, 0.0f));
	player = new Player();
	initEnemies();
	bulletManager.setTileMap(map);

	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, &bulletManager);
	player->setPosition(glm::vec2(INIT_PLAYER_X_TILES * map->getTileSize(), INIT_PLAYER_Y_TILES * map->getTileSize()));
	player->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;

	forceUnitTex.loadFromFile("images/forceUnit.png", TEXTURE_PIXEL_FORMAT_RGBA);
	forceUnit = Sprite::createSprite(glm::ivec2(9, 9), glm::vec2(1.0f, 1.0f), &forceUnitTex, &texProgram);
	
	force = new Force();
	force->init(texProgram, player);
}

void PlayScene::initEnemies() {
	
	int number_of_enemies = 57; //cuantos enemigos hay en el nivel
	for (int i = 0; i < number_of_enemies; ++i) {
		float enemy_x;
		int enemy_y;
		int typeofEnemy;
		switch (i + 1) { //enemy_list
		case 1:
			enemy_x = 16; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 2:
			enemy_x = 16.5f; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 3:
			enemy_x = 17; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 4:
			enemy_x = 17.5f; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 5:
			enemy_x = 18.f; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 6:
			enemy_x = 24.f; enemy_y = 4; typeofEnemy = FLOWER; 
			break;
		case 7:
			enemy_x = 24.5f; enemy_y = 4; typeofEnemy = FLOWER; 
			break;
		case 8:
			enemy_x = 25.f; enemy_y = 4; typeofEnemy = FLOWER; 
			break;
		case 9:
			enemy_x = 25.5f; enemy_y = 4; typeofEnemy = FLOWER; 
			break;
		case 10:
			enemy_x = 26.f; enemy_y = 4; typeofEnemy = FLOWER; 
			break;
		case 11:
			enemy_x = 40.f; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 12:
			enemy_x = 40.5f; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 13:
			enemy_x = 41.f; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 14:
			enemy_x = 41.5f; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 15:
			enemy_x = 42.f; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 16:
			enemy_x = 30.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 17:
			enemy_x = 31.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 18:
			enemy_x = 32.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 19:
			enemy_x = 33.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 20:
			enemy_x = 34.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 21:
			enemy_x = 38.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 22:
			enemy_x = 39.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 23:
			enemy_x = 40.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 24:
			enemy_x = 41.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 25:
			enemy_x = 42.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 26:
			enemy_x = 18.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 27:
			enemy_x = 19.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 28:
			enemy_x = 20.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 29:
			enemy_x = 21.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 30:
			enemy_x = 22.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 31:
			enemy_x = 43.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 32:
			enemy_x = 44.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 33:
			enemy_x = 45.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 34:
			enemy_x = 46.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 35:
			enemy_x = 47.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 36:
			enemy_x = 50.5f; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 37:
			enemy_x = 50.5f; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 38:
			enemy_x = 51.f; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 39:
			enemy_x = 51.5f; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 40:
			enemy_x = 52.f; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 41:
			enemy_x = 64.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 42:
			enemy_x = 65.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 43:
			enemy_x = 67.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 44:
			enemy_x = 68.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 45:
			enemy_x = 60.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 46:
			enemy_x = 61.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 47:
			enemy_x = 62.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 48:
			enemy_x = 63.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 49:
			enemy_x = 67.f; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 50:
			enemy_x = 67.5f; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 51:
			enemy_x = 68.f; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 52:
			enemy_x = 68.5f; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 53:
			enemy_x = 69.f; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 54:
			enemy_x = 69.5f; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 55:
			enemy_x = 70.f; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 56:
			enemy_x = 70.5f; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 57:
			enemy_x = 190.f; enemy_y = 6; typeofEnemy = BOSS;
			break;
	
		}
		Enemy* enemy_aux;
		enemy_aux = new Enemy();
		enemy_aux->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, player, typeofEnemy, &bulletManager);
		enemy_aux->setTileMap(map);
		enemy_aux->setPosition(glm::vec2(enemy_x * map->getTileSize(), enemy_y * map->getTileSize()));
		if (typeofEnemy == FLOWER) flowerList.push_back(enemy_aux);
		else enemyList.push_back(enemy_aux);
	}
}

//check player bullets impacting enemies
void PlayScene::checkHits() {
	vector<Bullet*> activeBullets = bulletManager.ret_actBullets();

	for (int j = 0; j < int(enemyList.size()-1); ++j) {
		for (int i = 0; i < int(activeBullets.size()-1); ++i) {			
			//glm::ivec2(bulletPosition.x + tileMapDispl + 35.0f, bulletPosition.y)
			Enemy* enemy = enemyList[j];
 			Bullet* bullet = activeBullets[i];
			glm::vec2 enemyPos = enemy->ret_pos();
			glm::vec2 enemySize = enemy->ret_size();			
			glm::vec2 bulletPos = bullet->ret_pos();
			glm::vec2 bulletSize = bullet->ret_size();

			//colision en las X
 			bool collisionX = (((enemyList[j]->ret_pos().x + enemyList[j]->ret_size().x+ 1.5f) >= activeBullets[i]->ret_pos().x + tileMapDispl+ 38.0f) &&
				((activeBullets[i]->ret_pos().x + activeBullets[i]->ret_size().x+ tileMapDispl+ 38.0f) >= enemyList[j]->ret_pos().x));
			//colision en las Y
			bool collisionY = (((enemyList[j]->ret_pos().y + enemyList[j]->ret_size().y+ 3.f) >= activeBullets[i]->ret_pos().y) &&
 				((activeBullets[i]->ret_pos().y + activeBullets[i]->ret_size().y + 3.f) >= enemyList[j]->ret_pos().y));

			if (collisionX && collisionY) {	
				if (!activeBullets[i]->isPowerShot) {
					activeBullets[i]->~Bullet();
					activeBullets.erase(activeBullets.begin() + i);
					bulletManager.set_actBullets(activeBullets);
				}
				enemyList[j]->hit();					
 				if (enemyList[j]->health_remaining() <= 0) {						 						
  					enemyList[j] = NULL;
  					enemyList.erase(enemyList.begin() + j);

				}
			}

		}
	}

	//vector<Bullet*> activeBullets = bulletManager.ret_actBullets();
	for (int j = 0; j < int(flowerList.size() - 1); ++j) {
		for (int i = 0; i < int(activeBullets.size() - 1); ++i) {
			//glm::ivec2(bulletPosition.x + tileMapDispl + 35.0f, bulletPosition.y)
			Enemy* enemy = flowerList[j];
			Bullet* bullet = activeBullets[i];
			glm::vec2 enemyPos = enemy->ret_pos();
			glm::vec2 enemySize = enemy->ret_size();
			glm::vec2 bulletPos = bullet->ret_pos();
			glm::vec2 bulletSize = bullet->ret_size();

			//colision en las X
			bool collisionX = (((flowerList[j]->ret_pos().x + flowerList[j]->ret_size().x + 1.5f) >= activeBullets[i]->ret_pos().x + tileMapDispl + 38.0f) &&
				((activeBullets[i]->ret_pos().x + activeBullets[i]->ret_size().x + tileMapDispl + 38.0f) >= flowerList[j]->ret_pos().x));
			//colision en las Y
			bool collisionY = (((flowerList[j]->ret_pos().y + flowerList[j]->ret_size().y + 1.5f) >= activeBullets[i]->ret_pos().y) &&
				((activeBullets[i]->ret_pos().y + activeBullets[i]->ret_size().y + 1.5f) >= flowerList[j]->ret_pos().y));

			if (collisionX && collisionY) {	
				if (!activeBullets[i]->isPowerShot) {
					activeBullets[i]->~Bullet();
					activeBullets.erase(activeBullets.begin() + i);
					bulletManager.set_actBullets(activeBullets);
				}
				flowerList[j]->hit();
				if (flowerList[j]->health_remaining() <= 0) {
					flowerList[j] = NULL;
					flowerList.erase(flowerList.begin() + j);

				}
			}

		}
	}
}

void PlayScene:: moveEnemies() {
	
	if (cooldown <= 0) {
		cooldown = 5;
		flowerIterator++;
	}
	if (directionCooldown <= 0) {
		directionCooldown = 300;		
		movingUp = !movingUp;
	}
	if (butterflyShootCooldown <= 0) {
		butterflyShootCooldown = 50;
		Enemy* butterfly = enemyList[rand() % enemyList.size()];
		bulletManager.createEnemyBullet(butterfly->ret_pos().x - tileMapDispl, butterfly->ret_pos().y, player->getPosition().x, player->getPosition().y, texProgram);
	}
		Enemy* flower = flowerList[flowerIterator % flowerList.size()];
		glm::ivec2 position = flower->ret_pos();
		if (movingUp)  position = glm::vec2(position.x, position.y - 2.5f);
		else position = glm::vec2(position.x, position.y + 2.f);
			
		flower->setPosition(position);
		for (int i = 0; i < enemyList.size(); i++) {
			Enemy* enemy = enemyList[i];
			glm::ivec2 position = enemy->ret_pos();
			if(enemy->ret_type() == BUTTERFLY) {
				if (enemy->ret_direction()) {
					position = glm::vec2(position.x, position.y - 1.5f);
					enemy->setPosition(position);
				}
				else {
					position = glm::vec2(position.x, position.y + 1.5f);
					enemy->setPosition(position);
				}
			}

		}		
}

void PlayScene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	cooldown--;
	directionCooldown--;
	butterflyShootCooldown--;

	bulletManager.update(deltaTime);
	forceUnit->update(deltaTime);
	force->update(deltaTime);

	checkBullets();
	moveEnemies();

	if(forceHit)checkForceHits();
	checkHits();
	checkEnemiesHits();
	
	glm::vec2 animationAndKeyframe = player->getAnimationAndKeyframe();
	if(animationAndKeyframe[0] != EXPLOSION)
		tileMapDispl += 1;	
	else {
		if (animationAndKeyframe[1] == 4) state = "MENU";
	}

	for (int i = 0; i < int(enemyList.size()); ++i)
		enemyList[i]->update(deltaTime);	
	for (int i = 0; i < int(flowerList.size()); ++i)
		flowerList[i]->update(deltaTime);

	forceUnit->setPosition(glm::vec2(500 - tileMapDispl, 100));
	
	if(!forceHit) checkCollisionForceUnit();
	else {
		force->update(deltaTime);
	}


	//special keys
	if (Game::instance().getKey('m') || Game::instance().getKey('M')) state = "MENU";

	if (Game::instance().getKey('f') || Game::instance().getKey('F')) {
		force->enable();
		forceHit = true;

		//per desactivar:
		/*if (forceHit) {
			force->disable();
			forceHit = false;
		}
		else {
			force->enable();
			forceHit = true;
		}*/
	}

	if (Game::instance().getKey('g') || Game::instance().getKey('g') && invCooldown>10) {
		player->invulnerable = !player->invulnerable;
		invCooldown = 0;
	}
	invCooldown++;

	render();
}

void PlayScene::checkCollisionForceUnit() {
	//check collision with force unit(28, 16 is player size)
	glm::ivec2 posPlayer = player->getPosition();
	glm::ivec2 posForceUnit = forceUnit->getPosition();

	bool collisionX = ((posForceUnit.x >= posPlayer.x) &&
		((posPlayer.x + 28) >= posForceUnit.x));

	bool collisionY = ((posForceUnit.x + 9 >= posPlayer.y) &&
		(posPlayer.y + 16) >= posForceUnit.y);
	if (collisionX && collisionY)
	{
		forceHit = true;
		force->enable();
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

	for (int i = 0; i < enemyList.size(); ++i)
		enemyList[i]->render();
	for (int i = 0; i < flowerList.size(); ++i)
		flowerList[i]->render();
	if(!forceHit) forceUnit->render();
	force->render();
}

void PlayScene::checkBullets() {
	vector<Bullet*> activeBullets = bulletManager.ret_actBullets();
	for (int i = 0; i < int(activeBullets.size()); ++i) {
		Bullet* b = activeBullets[i];

		glm::vec2 bulletPosition = b->ret_pos();
		if (bulletPosition != glm::vec2(0.0f, 0.0f) && map->collisionMoveRight(glm::ivec2(bulletPosition.x+tileMapDispl+35.0f, bulletPosition.y), glm::ivec2(8, 8))) {
			b->~Bullet();
			activeBullets.erase(activeBullets.begin() + i);
			bulletManager.set_actBullets(activeBullets);
		}

		//erase power shots once they've gone too far
		if (b->isPowerShot && (b->ret_pos().x - b->initial_pos.x > 200)) {
			activeBullets[i]->~Bullet();
			activeBullets.erase(activeBullets.begin() + i);
			bulletManager.set_actBullets(activeBullets);
		}
	}
}

//checks if force hits any enemies or bullets
void PlayScene::checkForceHits() {
	glm::vec2 force_pos = glm::vec2(player->getPosition().x + 28, player->getPosition().y);

	for (int j = 0; j < int(enemyList.size()); ++j) 
	{
		glm::vec2 enemy_pos = enemyList[j]->ret_pos();
		glm::vec2 enemy_size = enemyList[j]->ret_size();

		bool collisionX = (((enemy_pos.x + enemy_size.x + 1.5f) >= force_pos.x + tileMapDispl) &&
			((force_pos.x + 16 + tileMapDispl) >= enemy_pos.x));
		bool collisionY = (((enemy_pos.y + enemy_size.y + 1.5f) >= force_pos.y) &&
			((force_pos.y + 16 + 1.5f) >= enemy_pos.y));

		if (collisionX && collisionY) {
			enemyList[j]->hit();
			if (enemyList[j]->health_remaining() <= 0) {
				enemyList[j] = NULL;
				enemyList.erase(enemyList.begin() + j);
			}
		}
	}

	for (int j = 0; j < int(flowerList.size() - 1); ++j) 
	{
		glm::vec2 enemy_pos = flowerList[j]->ret_pos();
		glm::vec2 enemy_size = flowerList[j]->ret_size();

		bool collisionX = (((enemy_pos.x + enemy_size.x + 1.5f) >= force_pos.x + tileMapDispl) &&
			((force_pos.x + 16 + tileMapDispl) >= enemy_pos.x));
		bool collisionY = (((enemy_pos.y + enemy_size.y + 1.5f) >= force_pos.y) &&
			((force_pos.y + 16 + 1.5f) >= enemy_pos.y));

		if (collisionX && collisionY)
		{
			flowerList[j]->hit();
			if (flowerList[j]->health_remaining() <= 0) {
				flowerList[j] = NULL;
				flowerList.erase(flowerList.begin() + j);
			}
		}
	}
}


//check enemies impacting player
void PlayScene::checkEnemiesHits() {
	glm::vec2 player_pos = player->getPosition();

	for (int j = 0; j < int(enemyList.size()); ++j) {
		glm::vec2 enemy_pos = enemyList[j]->ret_pos();
		glm::vec2 enemy_size = enemyList[j]->ret_size();

		bool collisionX = (((enemy_pos.x + enemy_size.x + 1.5f) >= player_pos.x + tileMapDispl) &&
			((player_pos.x + 28 + tileMapDispl) >= enemy_pos.x));
		bool collisionY = (((enemy_pos.y + enemy_size.y + 1.5f) >= player_pos.y) &&
			((player_pos.y + 16 + 1.5f) >= enemy_pos.y));
		
		if (collisionX && collisionY)
		{
			player->hit();
		}
	}

	for (int j = 0; j < int(flowerList.size() - 1); ++j) {
		glm::vec2 enemy_pos = flowerList[j]->ret_pos();
		glm::vec2 enemy_size = flowerList[j]->ret_size();

		bool collisionX = (((enemy_pos.x + enemy_size.x + 1.5f) >= player_pos.x + tileMapDispl) &&
			((player_pos.x + 28 + tileMapDispl) >= enemy_pos.x));
		bool collisionY = (((enemy_pos.y + enemy_size.y + 1.5f) >= player_pos.y) &&
			((player_pos.y + 16 + 1.5f) >= enemy_pos.y));
		
		if (collisionX && collisionY)
		{
			player->hit();
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



