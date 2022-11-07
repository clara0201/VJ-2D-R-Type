#ifndef _ENEMY_INCLUDE
#define _ENEMY_INCLUDE

#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Player.h"
#include "BulletManager.h"

class Enemy
{
public:
	void init(const glm::vec2& tileMapPos, ShaderProgram& shaderProgram, Player* target, int typeOf, BulletManager* bulletManager);
	void update(int deltaTime);
	void render();

	void setTileMap(TileMap* tileMap);
	void setPosition(const glm::vec2& pos);
	glm::vec2 ret_pos();
	glm::vec2 ret_size();
	int ret_type();
	bool isFinished();
	void hit();
	void stopScrollingF();
	bool ret_direction();
	void changeDirection();
	void showExplosion();
	void changeScrollDispl(int newScroll);

	int health_remaining();

	~Enemy();

private:
	BulletManager* bM;
	int typeofEnemy, health, cooldown, deathCooldown;
	glm::vec2 posEnemy, size;
	float scrollDispl;
	Player* player;

	Texture spritesheet, winTex,  blastTex;
	Sprite* sprite, *winScreen, *blast;

	bool stopScrolling;
	Texture bossSpritesheet;
	Sprite* blackSprite;

	TileMap* map;
	ShaderProgram* aux;
	int timeToMove;
	int iterator;
	bool movingUp;
	int directionCooldown;
	ShaderProgram* shaderProgram;

	bool isKilled;

};
#endif
#pragma once
