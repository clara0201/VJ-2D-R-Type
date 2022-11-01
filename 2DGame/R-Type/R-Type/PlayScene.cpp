#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include "PlayScene.h"
#include "Game.h"
#include "Enemy.h"


#define SCREEN_X 0
#define SCREEN_Y 0
#define FLOWER 0


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
}

PlayScene::~PlayScene()
{	
	if(map != NULL)
		delete map;
	if(player != NULL)
		delete player;
	for (int i = 0; i < enemyList.size(); ++i)		
		enemyList[i] = NULL;
	cooldown = 5;
	directionCooldown = 60;
	movingUp = true;
	enemyIterator = 0;
}


void PlayScene::init()
{
	state = "ON";

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
}
void PlayScene::initEnemies() {
	
	int number_of_enemies = 12; //cuantos enemigos hay en el nivel
	for (int i = 0; i < number_of_enemies; ++i) {
		int enemy_x;
		int enemy_y;
		int typeofEnemy;
		switch (i + 1) { //enemy_list
		case 1:
			enemy_x = 16; enemy_y = 6; typeofEnemy = FLOWER;//primera
			break;
		case 2:
			enemy_x = 15; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 3:
			enemy_x = 14; enemy_y = 6; typeofEnemy = FLOWER;
			break;
		case 4:
			enemy_x = 24; enemy_y = 8; typeofEnemy = FLOWER; //segunda
			break;
		case 5:
			enemy_x = 23; enemy_y = 8; typeofEnemy = FLOWER;
			break;
		case 6:
			enemy_x = 22; enemy_y = 8; typeofEnemy = FLOWER; 
			break;
		case 7:
			enemy_x = 32; enemy_y = 4; typeofEnemy = FLOWER; //tercera
			break;
		case 8:
			enemy_x = 31; enemy_y = 4; typeofEnemy = FLOWER;
			break;
		case 9:
			enemy_x = 30; enemy_y = 4; typeofEnemy = FLOWER;
			break;
		case 10:
			enemy_x = 43; enemy_y = 4; typeofEnemy = FLOWER;
			break;
		case 11:
			enemy_x = 42; enemy_y = 4; typeofEnemy = FLOWER;
			break;
		case 12:
			enemy_x = 41; enemy_y = 4; typeofEnemy = FLOWER;
			break;
	
		}
		Enemy* enemy_aux;
		enemy_aux = new Enemy();
		enemy_aux->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, player, typeofEnemy, &bulletManager);
		enemy_aux->setTileMap(map);
		enemy_aux->setPosition(glm::vec2(enemy_x * map->getTileSize(), enemy_y * map->getTileSize()));
		enemyList.push_back(enemy_aux);
	}
}
void PlayScene::checkHits() {
	vector<Bullet*> activeBullets = bulletManager.ret_actBullets();
	for (int j = 0; j < int(enemyList.size()-1); ++j) {
		for (int i = 0; i < int(activeBullets.size()-1); ++i) {
			if (true) {
				//colision en las X
				//glm::ivec2(bulletPosition.x + tileMapDispl + 35.0f, bulletPosition.y)
				Enemy* enemy = enemyList[j];
 				Bullet* bullet = activeBullets[i];
				glm::vec2 enemyPos = enemy->ret_pos();
				glm::vec2 enemySize = enemy->ret_size();			
				glm::vec2 bulletPos = bullet->ret_pos();
				glm::vec2 bulletSize = bullet->ret_size();

 				bool collisionX = (((enemyList[j]->ret_pos().x + enemyList[j]->ret_size().x) >= activeBullets[i]->ret_pos().x + tileMapDispl+ 30.0f) &&
					((activeBullets[i]->ret_pos().x + activeBullets[i]->ret_size().x+ tileMapDispl+ 30.0f) >= enemyList[j]->ret_pos().x));
				//colision en las Y
				bool collisionY = (((enemyList[j]->ret_pos().y + enemyList[j]->ret_size().y) >= activeBullets[i]->ret_pos().y) &&
 					((activeBullets[i]->ret_pos().y + activeBullets[i]->ret_size().y) >= enemyList[j]->ret_pos().y));

				if (collisionX && collisionY) {
 					activeBullets[i]->~Bullet();
					activeBullets.erase(activeBullets.begin() + i);
					bulletManager.set_actBullets(activeBullets);
					enemyList[j]->hit();					
 					if (enemyList[j]->health_remaining() <= 0) {						 						
  						enemyList[j] = NULL;
  						enemyList.erase(enemyList.begin() + j);

					}
				}
			}
			//else {
			//	bool collisionX = (((activeBullets[i]->ret_pos().x + activeBullets[i]->ret_size().x) >= player->ret_pos().x) &&
			//		((player->ret_pos().x + player->ret_size().x) >= activeBullets[i]->ret_pos().x));
			//	//bool collisionY = (((activeBullets[i]->ret_pos().y + activeBullets[i]->ret_size().y) >= player->ret_pos().y) &&
			//	//	((player->ret_pos().y + player->ret_size().y) >= enemyList[j]->ret_pos().y));
			//	bool collisionY = (((activeBullets[i]->ret_pos().y + activeBullets[i]->ret_size().y) >= (player->ret_pos().y)) &&
			//		(((player->ret_pos().y) + player->ret_size().y) >= activeBullets[i]->ret_pos().y));

			//	if (collisionX && collisionY && !player->ret_hurt()) {
			//		player->hit();
			//		activeBullets[i]->~Bullet();
			//		activeBullets.erase(activeBullets.begin() + i);
			//	}
			//}
		}
	}
	//if (boss != NULL) {
	//	for (int i = 0; i < int(activeBullets.size()); ++i) {
	//		if (activeBullets[i]->ret_player_bullet()) {
	//			//colision en las X
	//			bool collisionX = (((boss->ret_pos().x + boss->ret_size().x) >= activeBullets[i]->ret_pos().x) &&
	//				((activeBullets[i]->ret_pos().x + activeBullets[i]->ret_size().x) >= boss->ret_pos().x));
	//			//colision en las Y
	//			bool collisionY = (((boss->ret_pos().y + boss->ret_size().y) >= activeBullets[i]->ret_pos().y) &&
	//				((activeBullets[i]->ret_pos().y + activeBullets[i]->ret_size().y) >= boss->ret_pos().y));

	//			if (collisionX && collisionY) {
	//				boss->hit();
	//				activeBullets[i]->~Bullet();
	//				activeBullets.erase(activeBullets.begin() + i);
	//			}
	//		}
	//		else {
	//			bool collisionX = (((activeBullets[i]->ret_pos().x + activeBullets[i]->ret_size().x) >= player->ret_pos().x) &&
	//				((player->ret_pos().x + player->ret_size().x) >= activeBullets[i]->ret_pos().x));
	//			bool collisionY = (((activeBullets[i]->ret_pos().y + activeBullets[i]->ret_size().y) >= (player->ret_pos().y)) &&
	//				(((player->ret_pos().y) + player->ret_size().y) >= activeBullets[i]->ret_pos().y));

	//			if (collisionX && collisionY && !player->ret_hurt()) {
	//				player->hit();
	//				activeBullets[i]->~Bullet();
	//				activeBullets.erase(activeBullets.begin() + i);
	//			}
	//		}
	//	}
	//}
}
void PlayScene:: moveEnemies() {
	
	if (cooldown <= 0) {
		cooldown = 5;
		enemyIterator++;
	}
	if (directionCooldown <= 0) {
		directionCooldown = 60;		
		movingUp = !movingUp;
	}
		Enemy* enemy = enemyList[enemyIterator % enemyList.size()];
		glm::ivec2 position = enemy->ret_pos();
		if (movingUp)  position = glm::vec2(position.x, position.y - 1);
		else position = glm::vec2(position.x, position.y + 1);
		enemy->setPosition(position);
	

}
void PlayScene::update(int deltaTime)
{
	currentTime += deltaTime;
	player->update(deltaTime);
	cooldown--;
	directionCooldown--;
	bulletManager.update(deltaTime);
	checkBullets();
	checkHits();
	moveEnemies();
	render();
	glm::vec2 animationAndKeyframe = player->getAnimationAndKeyframe();
	if(animationAndKeyframe[0] != EXPLOSION)
		tileMapDispl += 1;	
	else {
		if (animationAndKeyframe[1] == 4) state = "MENU";
	}
	for (int i = 0; i < int(enemyList.size()); ++i)
		enemyList[i]->update(deltaTime);

	//canviar condicio 
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
	for (int i = 0; i < enemyList.size(); ++i)
		enemyList[i]->render();
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



