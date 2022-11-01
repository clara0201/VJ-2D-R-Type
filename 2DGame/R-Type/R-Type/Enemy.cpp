#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Enemy.h"
#include "Game.h"
#include "Player.h"

#define FLOWER 0

void Enemy::init(const glm::vec2& tileMapPos, ShaderProgram& shaderProgram, Player* target, int typeOf, BulletManager* bulletManager)
{
	typeofEnemy = typeOf;
	if (typeOf == FLOWER) {
		health = 1;
		size.x = 16;
		size.y = 16;
	}
	cooldown = 50;
	timeToMove = 10;
	iterator = 0;	

	aux = &shaderProgram;
	scrollDispl = tileMapPos.x;
	
	spritesheet.loadFromFile("images/enemyFlower.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(8, 8), glm::vec2(1.0f, 1.0f), &spritesheet, &shaderProgram);	
	sprite->setPosition(glm::vec2(0.0f, 0.0f));

	//sprite->addKeyframe(0, glm::vec2(0.0f, 0.0f));
	
	sprite->setPosition(glm::vec2(float(posEnemy.x - scrollDispl), float(posEnemy.y)));	
	player = target;
	bM = bulletManager;	
}


void Enemy::update(int deltaTime)
{
	timeToMove--;
	scrollDispl += 1;
	if (timeToMove <= 0) {
		if(typeofEnemy == FLOWER) posEnemy.x = posEnemy.x- 5.f;
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