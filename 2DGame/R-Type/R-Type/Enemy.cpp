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

void Enemy::init(const glm::vec2& tileMapPos, ShaderProgram& shaderProgram, Player* target, int typeOf, BulletManager* bulletManager)
{
	typeofEnemy = typeOf;
	movingUp = rand() % 2 == 0;
	directionCooldown = 20;
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
	cooldown = 50;
	timeToMove = 10;
	iterator = 0;	

	aux = &shaderProgram;
	scrollDispl = tileMapPos.x;
	


	//sprite->addKeyframe(0, glm::vec2(0.0f, 0.0f));
	
	sprite->setPosition(glm::vec2(float(posEnemy.x - scrollDispl), float(posEnemy.y)));	
	player = target;
	bM = bulletManager;	
}


void Enemy::update(int deltaTime)
{

	timeToMove--;
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
	scrollDispl += 1;
	if (timeToMove <= 0) {
		posEnemy.x = posEnemy.x- 5.f;
		iterator++;
		timeToMove = 10;		
	}
	if (sprite != NULL) {
		sprite->update(deltaTime);
		sprite->setPosition(glm::vec2(float(posEnemy.x - scrollDispl), float(posEnemy.y)));
	}
}



void Enemy::render()
{
	sprite->render();
}

void Enemy::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Enemy::setPosition(const glm::vec2& pos)
{
	posEnemy = pos;
	sprite->setPosition(glm::vec2(float(posEnemy.x - scrollDispl), float(posEnemy.y)));
}


glm::vec2 Enemy::ret_pos() {
	if (this != NULL) {
		glm::vec2 posaux = posEnemy;		
		return posaux;
	}
	return glm::vec2(0.0f, 0.0f);
}

glm::vec2 Enemy::ret_size() {
	if (this != NULL)
		return size;
	return glm::vec2(0.0f, 0.0f);
}

void Enemy::hit() {
	if (this != NULL) {		
		--health;
		if (health == 0) {
			sprite = NULL;
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