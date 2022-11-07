#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"
#include "Player.h"

#define FLOWER 0
#define BUTTERFLY 1
#define FLY 2
#define BOSS 3
#define MOVE_UP 4
#define MOVE_DOWN 5

void Enemy::init(const glm::vec2& tileMapPos, ShaderProgram& shaderProgram, Player* target, int typeOf, BulletManager* bulletManager)
{
	typeofEnemy = typeOf;
	movingUp = rand() % 2 == 0;
	deathCooldown = 10000;
	directionCooldown = 20;
	stopScrolling = false;
	
	if (typeOf == FLOWER) {
		health = 1;
		size.x = 20;
		size.y = 20;

		spritesheet.loadFromFile("images/enemyFlower.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(8, 8), glm::vec2(1.0f, 1.0f), &spritesheet, &shaderProgram);
	}
	else if (typeOf == BUTTERFLY) {
		health = 1;
		size.x = 15;
		size.y = 16;

		spritesheet.loadFromFile("images/mariposaSprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(15, 16), glm::vec2(0.5f, 1.0f), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(3);

		sprite->setAnimationSpeed(FLY, 14);
		sprite->addKeyframe(FLY, glm::vec2(0.0f, 0.f));
		sprite->addKeyframe(FLY, glm::vec2(0.5f, 0.f));
		sprite->changeAnimation(FLY);


	}
	else if (typeOf == BOSS) {
		health = 20;
		size.x =  70;
		size.y = 150;
		spritesheet.loadFromFile("images/tailSprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
		sprite = Sprite::createSprite(glm::ivec2(120, 100), glm::vec2(0.25f, 1.0f), &spritesheet, &shaderProgram);
		sprite->setNumberAnimations(6);

		sprite->setAnimationSpeed(MOVE_UP, 4);
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.0f, 0.f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.25f, 0.f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.5f, 0.f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.75f, 0.f));
		sprite->setAnimationSpeed(MOVE_DOWN, 4);
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.75f, 0.f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.5f, 0.f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.25f, 0.f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.0f, 0.f));
		sprite->changeAnimation(MOVE_DOWN);
		sprite->setPosition(glm::vec2(float(posEnemy.x), float(posEnemy.y)));

		bossSpritesheet.loadFromFile("images/ocultarSprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
		blackSprite = Sprite::createSprite(glm::ivec2(300, 288), glm::vec2(0.5f, 1.0f), &bossSpritesheet, &shaderProgram);
		blackSprite->setNumberAnimations(10);
		int MUERTO = 7;
		int OCULTAR = 6;
		int VIVO = 8;

		blackSprite->setAnimationSpeed(OCULTAR, 3);
		blackSprite->addKeyframe(OCULTAR, glm::vec2(0.0f, 0.f));
		blackSprite->addKeyframe(OCULTAR, glm::vec2(0.5f, 0.f));
		blackSprite->setAnimationSpeed(MUERTO, 7);
		blackSprite->addKeyframe(MUERTO, glm::vec2(0.5f, 0.f));
		blackSprite->setAnimationSpeed(VIVO, 7);
		blackSprite->addKeyframe(VIVO, glm::vec2(0.0f, 0.f));

		blackSprite->changeAnimation(VIVO);
		blackSprite->setPosition(glm::vec2(float((183 * 16) - scrollDispl), float(0)));



	}
	cooldown = 50;
	timeToMove = 10;
	iterator = 0;	

	aux = &shaderProgram;
	//scrollDispl = tileMapPos.x;
	scrollDispl = 0;
	


	//sprite->addKeyframe(0, glm::vec2(0.0f, 0.0f));
	
	sprite->setPosition(glm::vec2(float(posEnemy.x - scrollDispl), float(posEnemy.y)));	
	player = target;
	bM = bulletManager;	
}

void Enemy::stopScrollingF() {
	stopScrolling = true;
}
void Enemy::update(int deltaTime)
{

	timeToMove--;
	if (deathCooldown <=0 && blackSprite != NULL && blackSprite->animation() == 6) blackSprite->changeAnimation(7);
	deathCooldown--;
	directionCooldown--;
	if (posEnemy.y <= 10) 
		movingUp = false;
	if (posEnemy.y <= 40 && rand() % 100 < 15)
		movingUp = false;
	if (directionCooldown <= 0) {
		if (rand() % 100 > 15) 
			movingUp = !movingUp;
		directionCooldown = 20;
	}
	if(!stopScrolling) scrollDispl +=1;
	if (timeToMove <= 0) {
		if(typeofEnemy != BOSS)posEnemy.x = posEnemy.x- 5.f;
		iterator++;
		timeToMove = 10;		
	}
	if (sprite != NULL && health > 0 ) {
		sprite->setPosition(glm::vec2(float(posEnemy.x - scrollDispl), float(posEnemy.y)));
		if(blackSprite!= NULL)blackSprite->setPosition(glm::vec2(float((183 * 16) - scrollDispl), float(0)));
		if (sprite->animation() == MOVE_UP && sprite->keyframe() == 3) 
			sprite->changeAnimation(MOVE_DOWN);
		if (sprite->animation() == MOVE_DOWN && sprite->keyframe() == 3) 
			sprite->changeAnimation(MOVE_UP);
		sprite->update(deltaTime);
	}
	if(blackSprite!= NULL) blackSprite->update(deltaTime);

}



void Enemy::render()
{
	if(health > 0)sprite->render();
	if(typeofEnemy == BOSS) blackSprite->render();
}

void Enemy::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Enemy::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	if (health > 0) sprite->setPosition(glm::vec2(float(posEnemy.x - scrollDispl), float(posEnemy.y)));
}


glm::vec2 Enemy::ret_pos() {
	if (this != NULL) {
		glm::vec2 posaux = posEnemy;		
		return posaux;
	}
	return glm::vec2(0.0f, 0.0f);
}

glm::vec2 Enemy::ret_size() {
	if (typeofEnemy == BOSS)
		int i = 0;
	if (this != NULL)
		return size;
	return glm::vec2(0.0f, 0.0f);
}

void Enemy::hit() {
	if (this != NULL) {		
		--health;
		if (health <= 0) {
			if (typeofEnemy == BOSS) {
       			sprite = NULL;
				blackSprite->changeAnimation(6);
				deathCooldown = 200;
			}
		}
	}
}


int Enemy::health_remaining() {
	if (this != NULL)
		return health;
	return 0;
}
int Enemy::ret_type() {
	if (this != NULL)
		return typeofEnemy;
	return 0;
}
bool Enemy::ret_direction() {
	if (this != NULL)
		return movingUp;
	return 0;
}
void Enemy::changeDirection() {
	if (this != NULL)
		movingUp = !movingUp;
	return ;
}