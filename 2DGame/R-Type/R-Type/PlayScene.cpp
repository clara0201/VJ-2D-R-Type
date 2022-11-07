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

	blastTex.loadFromFile("images/enemyExplosion.png", TEXTURE_PIXEL_FORMAT_RGBA);
}

void PlayScene::initEnemies() {
	
	int number_of_enemies = 135; //cuantos enemigos hay en el nivel

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
			//
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
			//
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
			//
		case 16:
			enemy_x = 50.f; enemy_y = 2; typeofEnemy = BUTTERFLY;
			break;
		case 17:
			enemy_x = 51.f; enemy_y = 2; typeofEnemy = BUTTERFLY;
			break;
		case 18:
			enemy_x = 52.f; enemy_y = 2; typeofEnemy = BUTTERFLY;
			break;
		case 19:
			enemy_x = 53.f; enemy_y = 2; typeofEnemy = BUTTERFLY;
			break;
		case 20:
			enemy_x = 54.f; enemy_y = 2; typeofEnemy = BUTTERFLY;
			break;
		case 21:
			enemy_x = 58.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 22:
			enemy_x = 59.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 23:
			enemy_x = 50.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 24:
			enemy_x = 51.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 25:
			enemy_x = 52.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 26:
			enemy_x = 58.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 27:
			enemy_x = 59.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
			//
		case 28:
			enemy_x = 110.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 29:
			enemy_x = 111.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 30:
			enemy_x = 112.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 31:
			enemy_x = 113.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 32:
			enemy_x = 114.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 33:
			enemy_x = 115.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 34:
			enemy_x = 116.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 35:
			enemy_x = 117.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
			//
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
			enemy_x = 190.f; enemy_y = 6; typeofEnemy = FLOWER;
			break;
			//original above
		case 58:
			enemy_x = 125.f - 50; enemy_y = 4; typeofEnemy = FLOWER;
			break;
		case 59:
			enemy_x = 125.5f - 50; enemy_y = 4; typeofEnemy = FLOWER;
			break;
		case 60:
			enemy_x = 126.f - 50; enemy_y = 4; typeofEnemy = FLOWER;
			break;
		case 61:
			enemy_x = 140.f - 50; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 62:
			enemy_x = 140.5f - 50; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 63:
			enemy_x = 141.f - 50; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 64:
			enemy_x = 141.5f - 50; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 65:
			enemy_x = 142.f - 50; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 66:
			enemy_x = 130.f - 20; enemy_y = 3; typeofEnemy = BUTTERFLY;
			break;
		case 67:
			enemy_x = 131.f - 20; enemy_y = 3; typeofEnemy = BUTTERFLY;
			break;
		case 68:
			enemy_x = 132.f - 20; enemy_y = 3; typeofEnemy = BUTTERFLY;
			break;
		case 69:
			enemy_x = 133.f - 20; enemy_y = 3; typeofEnemy = BUTTERFLY;
			break;
		case 70:
			enemy_x = 134.f - 20; enemy_y = 3; typeofEnemy = BUTTERFLY;
			break;
		case 71:
			enemy_x = 138.f - 20; enemy_y = 3; typeofEnemy = BUTTERFLY;
			break;
		case 72:
			enemy_x = 139.f - 20; enemy_y = 3; typeofEnemy = BUTTERFLY;
			break;
		case 73:
			enemy_x = 140.f - 20; enemy_y = 3; typeofEnemy = BUTTERFLY;
			break;
		case 74:
			enemy_x = 141.f - 20; enemy_y = 3; typeofEnemy = BUTTERFLY;
			break;
		case 75:
			enemy_x = 142.f - 20; enemy_y = 3; typeofEnemy = BUTTERFLY;
			break;
		case 76:
			enemy_x = 118.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 77:
			enemy_x = 119.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 78:
			enemy_x = 120.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 79:
			enemy_x = 121.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 80:
			enemy_x = 122.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 81:
			enemy_x = 143.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 82:
			enemy_x = 144.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 83:
			enemy_x = 145.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 84:
			enemy_x = 146.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 85:
			enemy_x = 147.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 86:
			enemy_x = 150.5f; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 87:
			enemy_x = 150.5f; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 88:
			enemy_x = 151.f; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 89:
			enemy_x = 151.5f; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 90:
			enemy_x = 152.f; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 91:
			enemy_x = 164.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 92:
			enemy_x = 165.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 93:
			enemy_x = 167.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 94:
			enemy_x = 168.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 95:
			enemy_x = 160.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 96:
			enemy_x = 161.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 97:
			enemy_x = 162.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 98:
			enemy_x = 163.f; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 99:
			enemy_x = 167.f; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 100:
			enemy_x = 167.5f; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 101:
			enemy_x = 143.f + 40; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 102:
			enemy_x = 144.f + 40; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 103:
			enemy_x = 145.f + 40; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 104:
			enemy_x = 146.f + 40; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 105:
			enemy_x = 147.f + 40; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 106:
			enemy_x = 150.5f + 40; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 107:
			enemy_x = 150.5f + 40; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 108:
			enemy_x = 151.f + 40; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 109:
			enemy_x = 151.5f + 40; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 110:
			enemy_x = 152.f + 40; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 111:
			enemy_x = 164.f + 25; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 112:
			enemy_x = 165.f + 25; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 113:
			enemy_x = 167.f + 25; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 114:
			enemy_x = 168.f + 25; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 115:
			enemy_x = 160.f + 25; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 116:
			enemy_x = 161.f + 25; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 117:
			enemy_x = 162.f + 25; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 118:
			enemy_x = 163.f + 25; enemy_y = 4; typeofEnemy = BUTTERFLY;
			break;
		case 119:
			enemy_x = 180.f; enemy_y = 8; typeofEnemy = BUTTERFLY;
			break;
		case 120:
			enemy_x = 181.f; enemy_y = 8; typeofEnemy = BUTTERFLY;
			break;
		case 121:
			enemy_x = 200.f; enemy_y = 6; typeofEnemy = BUTTERFLY;
			break;
		case 122:
			enemy_x = 202.f; enemy_y = 6; typeofEnemy = BUTTERFLY;
			break;
		case 123:
			enemy_x = 204.f; enemy_y = 6; typeofEnemy = BUTTERFLY;
			break;
		case 124:
			enemy_x = 206.f; enemy_y = 6; typeofEnemy = BUTTERFLY;
			break;
		case 125:
			enemy_x = 208.f; enemy_y = 6; typeofEnemy = BUTTERFLY;
			break;
		case 126:
			enemy_x = 210.f; enemy_y = 6; typeofEnemy = BUTTERFLY;
			break;
		case 127:
			enemy_x = 212.f; enemy_y = 6; typeofEnemy = BUTTERFLY;
			break;
		case 128:
			enemy_x = 214.f; enemy_y = 6; typeofEnemy = BUTTERFLY;
			break;
		case 129:
			enemy_x = 216.f; enemy_y = 6; typeofEnemy = BUTTERFLY;
			break;
		case 130:
			enemy_x = 222.f; enemy_y = 4; typeofEnemy = FLOWER;
			break;
		case 131:
			enemy_x = 223.f; enemy_y = 4; typeofEnemy = FLOWER;
			break;
		case 132:
			enemy_x = 224.f; enemy_y = 4; typeofEnemy = FLOWER;
			break;
		case 133:
			enemy_x = 225.f; enemy_y = 4; typeofEnemy = FLOWER;
			break;
		case 134:
			enemy_x = 126.f; enemy_y = 4; typeofEnemy = FLOWER;
			break;
		case 135:
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
					blast = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.0f, 1.0f), &blastTex, &texProgram);
					blast->setPosition(glm::vec2(enemyPos.x - tileMapDispl, enemyPos.y));
					blastList.insert({ blast, 5 });

  					enemyList[j] = NULL;
  					enemyList.erase(enemyList.begin() + j);
				}
			}
		}
	}

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
					blast = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.0f, 1.0f), &blastTex, &texProgram);
					blast->setPosition(glm::vec2(enemyPos.x - tileMapDispl, enemyPos.y));
					blastList.insert({ blast, 5 });

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
	
	for (int i = 0; i < int(enemyList.size()); ++i)
		enemyList[i]->update(deltaTime);	
	for (int i = 0; i < int(flowerList.size()); ++i)
		flowerList[i]->update(deltaTime);
	
	for (auto it = blastList.begin(); it != blastList.end();) {
		if (it->second <= 0) it = blastList.erase(it);
		else {
			it->second = it->second--;
			it++;
		}
	}

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

	if (Game::instance().getKey('g') || Game::instance().getKey('G') && invCooldown>20) {
		player->invulnerable = !(player->invulnerable);
		invCooldown = 0;
	}
	invCooldown++;

	//change location
	int newScroll = tileMapDispl;
	bool changedScroll = false;
	if (Game::instance().getKey('1')) {
		newScroll = 0;
		changedScroll = true;
	}
	if (Game::instance().getKey('2')) {
		newScroll = 1000;
		changedScroll = true;
	}
	if (Game::instance().getKey('3')) {
		newScroll = 2500;
		changedScroll = true;
	}
	if (changedScroll) {
		tileMapDispl = newScroll;
		for (int i = 0; i < int(enemyList.size()); ++i)
			enemyList[i]->changeScrollDispl(newScroll);
		for (int i = 0; i < int(flowerList.size()); ++i)
			flowerList[i]->changeScrollDispl(newScroll);
	}
	

	if (animationAndKeyframe[0] != EXPLOSION)
		tileMapDispl += 1;
	else if (animationAndKeyframe[1] == 4) state = "MENU";
	//else if (animationAndKeyframe[1] == 4 && player->num_lives > 0) state = "RETRY";


	render();
}

//check collision with force unit(28, 16 is player size)
void PlayScene::checkCollisionForceUnit() {
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
	
	std::map<Sprite*, int>::iterator it;
	for (it = blastList.begin(); it != blastList.end(); it++)
		it->first->render();

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

		//intento de checkear si les bullets dels enemics colisionen amb el player
		glm::vec2 bullet_pos = b->ret_pos();
		glm::vec2 bullet_size = b->ret_size();
		glm::vec2 player_pos = player->getPosition();

		bool collisionX = (((player_pos.x + 28) >= bullet_pos.x + tileMapDispl + 38.0f) &&
			((bullet_pos.x + bullet_size.x + tileMapDispl + 38.0f) >= player_pos.x));
		bool collisionY = (((bullet_pos.y + 6 + 1.5f) >= player_pos.y) &&
			((player_pos.y + 16 + 1.5f) >= bullet_pos.y));

		if (collisionX && collisionY) player->hit();
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
				blast = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.0f, 1.0f), &blastTex, &texProgram);
				blast->setPosition(glm::vec2(enemy_pos.x - tileMapDispl, enemy_pos.y));
				blastList.insert({ blast, 5 });

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
				blast = Sprite::createSprite(glm::ivec2(16, 16), glm::vec2(1.0f, 1.0f), &blastTex, &texProgram);
				blast->setPosition(glm::vec2(enemy_pos.x - tileMapDispl, enemy_pos.y));
				blastList.insert({ blast, 5 });

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
	if (state == "RETRY") {
		this->init();
		return this;
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



