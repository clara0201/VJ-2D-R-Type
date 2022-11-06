#pragma once
#include "Sprite.h"
#include "TileMap.h"

class Bullet
{
public:
	void createBullet(float posx, float posy, bool player, ShaderProgram& shaderProgram, float speedy, int typeOfBullet, float desviationX, float desviationY);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap* tileMap);
	~Bullet();
	glm::vec2 ret_pos();
	glm::vec2 ret_size();
	glm::vec2 initial_pos;
	bool ret_player_bullet();
	bool alive, isPowerShot;

private:
	int dev;
	bool isPlayer;
	bool spreadBullet;
	float speed;
	int scrollDispl;
	float desvX;
	float desvY;
	glm::vec2 posBullet, size;
	int dir;
	int typeOf;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
};

#pragma once
