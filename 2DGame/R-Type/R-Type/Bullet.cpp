#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Bullet.h"

enum directions //0, 1, 2, 3
{
	LEFT, RIGHT, UP, DOWN, UR, DR, UL, DL
};

enum anim
{
	NORMAL, HITWALL
};


void Bullet::createBullet(float posx, float posy, bool player, ShaderProgram& shaderProgram, float speedy) {	
	posBullet = glm::vec2(float(posx), float(posy));
	isPlayer = player;	
	speed = speedy;
	scrollDispl = posx;
	size.x = 14;
	size.y = 8;
	alive = true;

	spritesheet.loadFromFile("images/bulletSpritesheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(16, 8), glm::vec2(0.5f, 1.f), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(2);

		sprite->setAnimationSpeed(NORMAL, 3); 
		sprite->addKeyframe(NORMAL, glm::vec2(0.0f, 0.0f));

		sprite->setAnimationSpeed(HITWALL, 3);
		sprite->addKeyframe(HITWALL, glm::vec2(0.5f, 0.0f));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(posBullet.x), float(posBullet.y)));
}

void Bullet::update(int deltaTime) {
		
	posBullet.x += 1 * speed;	
	scrollDispl += 1;
	sprite->update(deltaTime);
	/*int posBulletY = float(posBullet.y);
	
	//check collisions with walls
	if (map->collisionMoveLeft(glm::ivec2(posBullet.x + scrollDispl + 1, posBullet.y), glm::ivec2(8, 8)) ||
		map->collisionMoveRight(glm::ivec2(posBullet.x + scrollDispl + 1, posBullet.y), glm::ivec2(8, 8)) ||
		map->collisionMoveDown(glm::ivec2(posBullet.x + scrollDispl + 1, posBullet.y), glm::ivec2(8, 8), &posBulletY) ||
		map->collisionMoveUp(glm::ivec2(posBullet.x + scrollDispl + 1, posBullet.y), glm::ivec2(8, 8), &posBulletY))
	{
	sprite->changeAnimation(HITWALL);
	alive = false;
	}

	
	else if (map->collisionMoveRight(glm::ivec2(posBullet.x + scrollDispl + 1, posBullet.y), glm::ivec2(8, 8)))
	{
	sprite->changeAnimation(HITWALL);
	alive = false;
	
	}
	else if (map->collisionMoveDown(glm::ivec2(posBullet.x + scrollDispl + 1, posBullet.y), glm::ivec2(8, 8), &posBulletY))
	{
	sprite->changeAnimation(HITWALL);
	alive = false;
	
	}
	else if (map->collisionMoveUp(glm::ivec2(posBullet.x + scrollDispl + 1, posBullet.y), glm::ivec2(8, 8), &posBulletY))
	{
	sprite->changeAnimation(HITWALL);
	alive = false;
	
	}*/
}

void Bullet::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Bullet::render() {
	sprite->setPosition(glm::vec2(float(posBullet.x + 25), float(posBullet.y + 5)));
	sprite->render();
}

Bullet::~Bullet() {
}

glm::vec2 Bullet::ret_pos() {
	if (this != NULL)
		return posBullet;
	return glm::vec2(0.0f, 0.0f);
}

glm::vec2 Bullet::ret_size() {
	if (this != NULL)
		return size;
	return glm::vec2(0.0f, 0.0f);
}

bool Bullet::ret_player_bullet() {
	if (this != NULL)
		return isPlayer;
	return false;
}