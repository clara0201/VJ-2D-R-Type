#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"
#include "PlayScene.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4

ShaderProgram* aux;


enum PlayerAnims
{
	STAND_UP, STAND_DOWN, STAND_RIGHT, MOVE_UP, MOVE_DOWN, EXPLOSION
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, BulletManager* bulletManager)
{
	aux = &shaderProgram;
	bJumping = false;
	timeBetweenBullets = 0;
	spritesheet.loadFromFile("images/naveMasExplosion.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(28, 16), glm::vec2(0.1, 1), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);
	
		
		sprite->setAnimationSpeed(STAND_UP, 8);
		sprite->addKeyframe(STAND_UP, glm::vec2(0.4f, 0.f));

		sprite->setAnimationSpeed(STAND_RIGHT, 8);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.2f, 0.f));

		sprite->setAnimationSpeed(STAND_DOWN, 8);
		sprite->addKeyframe(STAND_DOWN, glm::vec2(0.f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_UP, 8);
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.3f, 0.f));
		sprite->addKeyframe(MOVE_UP, glm::vec2(0.4f, 0.f));
		
		sprite->setAnimationSpeed(MOVE_DOWN, 8);
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.1f, 0.f));
		sprite->addKeyframe(MOVE_DOWN, glm::vec2(0.f, 0.f));

		sprite->setAnimationSpeed(EXPLOSION, 4);
		sprite->addKeyframe(EXPLOSION, glm::vec2(0.5f, 0.f));
		sprite->addKeyframe(EXPLOSION, glm::vec2(0.6f, 0.f));
		sprite->addKeyframe(EXPLOSION, glm::vec2(0.7f, 0.f));
		sprite->addKeyframe(EXPLOSION, glm::vec2(0.8f, 0.f));
		sprite->addKeyframe(EXPLOSION, glm::vec2(0.9f, 0.f));
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	scrollDispl = tileMapPos;
	bM= bulletManager;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{	
	sprite->update(deltaTime);
	if (sprite->animation() == EXPLOSION) cout << "explosion" << endl;
	else if (map->collisionMoveLeft(glm::ivec2(posPlayer.x+scrollDispl.x+1, posPlayer.y), glm::ivec2(28, 16)))
	{
		sprite->changeAnimation(EXPLOSION);
		posPlayer.x += 2;
	}
	else if (map->collisionMoveRight(glm::ivec2(posPlayer.x + scrollDispl.x-20, posPlayer.y), glm::ivec2(28, 16)))
	{
		sprite->changeAnimation(EXPLOSION);
		posPlayer.x -= 2;
	}
	else if (map->collisionMoveDown(glm::ivec2(posPlayer.x + scrollDispl.x+1, posPlayer.y), glm::ivec2(28, 16), &posPlayer.y))
	{
		sprite->changeAnimation(EXPLOSION);
		posPlayer.y -= 2;
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{		
		posPlayer.x -= 2;			
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
			posPlayer.x += 2;		
		
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_UP))
	{
		int s = sprite->keyframe();
		if(s == 1) 
			sprite->changeAnimation(STAND_UP);
		if (sprite->animation() != MOVE_UP && sprite->animation() != STAND_UP)
			sprite->changeAnimation(MOVE_UP);
		posPlayer.y -= 2;		
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_DOWN))
	{
		int s = sprite->keyframe();
		if (s == 1)
			sprite->changeAnimation(STAND_DOWN);
		else if (sprite->animation() != MOVE_DOWN && sprite->animation() != STAND_DOWN)
			sprite->changeAnimation(MOVE_DOWN);
		posPlayer.y += 2;	
	}
	else
	{
		sprite->changeAnimation(STAND_RIGHT);
	}
	if ((Game::instance().getKey('z') || Game::instance().getKey('Z')) && timeBetweenBullets <= 0)
	{
		bM->createPlayerBullet(posPlayer.x - 16, posPlayer.y + 130, *aux);
		timeBetweenBullets = 10;

	}
	
	scrollDispl.x += 1;		
	timeBetweenBullets--;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

glm::vec2 Player::getPosition() {
	return posPlayer;
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}
glm::vec2 Player::getAnimationAndKeyframe() {
	return glm::vec2(sprite->animation(), sprite->keyframe());
}
void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




