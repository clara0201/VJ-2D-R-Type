#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_UP, STAND_DOWN, STAND_RIGHT, MOVE_UP, MOVE_DOWN, EXPLOSION
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
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
		sprite->setAnimationSpeed(EXPLOSION, 8);
		sprite->addKeyframe(EXPLOSION, glm::vec2(0.5f, 0.f));
		sprite->addKeyframe(EXPLOSION, glm::vec2(0.6f, 0.f));
		sprite->addKeyframe(EXPLOSION, glm::vec2(0.7f, 0.f));
		sprite->addKeyframe(EXPLOSION, glm::vec2(0.8f, 0.f));
		sprite->addKeyframe(EXPLOSION, glm::vec2(0.9f, 0.f));
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if (sprite->animation() == EXPLOSION) cout << "explosion" << endl;
	else if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{		
		posPlayer.x -= 2;	
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(28, 16)))
		{
			sprite->changeAnimation(EXPLOSION);
			posPlayer.x += 2;
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
			posPlayer.x += 2;		
			if (map->collisionMoveRight(posPlayer, glm::ivec2(28, 16)))
			{
				sprite->changeAnimation(EXPLOSION);
				posPlayer.x -= 2;
			}
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
		if(map->collisionMoveDown(posPlayer, glm::ivec2(28, 16), &posPlayer.y))
		{ 
			sprite->changeAnimation(EXPLOSION);
			posPlayer.y -= 2;
		}

	}
	else
	{		
			sprite->changeAnimation(STAND_RIGHT);
	}
	
	/*if(bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{
			if(Game::instance().getSpecialKey(GLUT_KEY_UP))
			{
				bJumping = true;
				jumpAngle = 0;
				startY = posPlayer.y;
			}
		}
	}*/
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}




