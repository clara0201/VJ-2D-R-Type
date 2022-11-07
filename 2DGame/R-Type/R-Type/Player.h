#ifndef _PLAYER_INCLUDE
#define _PLAYER_INCLUDE


#include "Sprite.h"
#include "TileMap.h"
#include "BulletManager.h"


// Player is basically a Sprite that represents the player. As such it has
// all properties it needs to track its movement, jumping, and collisions.


class Player
{

public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, BulletManager* bulletManager);
	void update(int deltaTime);
	void render();
	void stopScrollingF();
	void hit();
	
	void setTileMap(TileMap *tileMap);
	void setPosition(const glm::vec2 &pos);
	glm::vec2 getAnimationAndKeyframe();
	glm::vec2 getPosition();

	bool invulnerable;
	int num_lives;
	
private:
	bool bJumping, countingShoot;
	int timeBetweenBullets, shootingTimer;
	glm::ivec2 tileMapDispl, scrollDispl, posPlayer;
	int jumpAngle, startY;
	bool stopScrolling;
	Texture spritesheet;
	Texture explosionSpritesheet;
	Sprite *sprite;
	TileMap *map;
	BulletManager* bM;

};


#endif // _PLAYER_INCLUDE


