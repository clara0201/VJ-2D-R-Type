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
	NORMAL, SPREAD
};


void Bullet::createBullet(float posx, float posy, bool player, ShaderProgram& shaderProgram, float speedy) {	
	posBullet = glm::vec2(float(posx), float(posy));
	isPlayer = player;	
	speed = speedy;
	scrollDispl = posx;
	size.x = 8;
	size.y = 8;

	spritesheet.loadFromFile("images/bala.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(14, 8), glm::vec2(1.f, 1.f), &spritesheet, &shaderProgram);

	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(NORMAL, 3); sprite->addKeyframe(NORMAL, glm::vec2(0.0f, 0.0f));	
	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(posBullet.x), float(posBullet.y)));
}

void Bullet::update(int deltaTime) {
		
	posBullet.x += 5 * speed;	
	scrollDispl += 1;
	sprite->update(deltaTime);
}

void Bullet::setTileMap(TileMap* tileMap)
{
	map = tileMap;
}

void Bullet::render() {
	sprite->setPosition(glm::vec2(float(posBullet.x + scrollDispl), float(posBullet.y)));
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