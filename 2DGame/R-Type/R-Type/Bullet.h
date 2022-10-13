#pragma once
#include "Sprite.h"
#include "TileMap.h"

class Bullet
{
public:
	void createBullet(float posx, float posy, bool player, ShaderProgram& shaderProgram, float speedy);
	void update(int deltaTime);
	void render();
	void setTileMap(TileMap* tileMap);
	~Bullet();
	glm::vec2 ret_pos();
	glm::vec2 ret_size();
	bool ret_player_bullet();

private:
	int dev;
	bool isPlayer;
	bool spreadBullet;
	float speed;
	int scrollDispl;
	glm::vec2 posBullet, size;
	int dir;
	Texture spritesheet;
	Sprite* sprite;
	TileMap* map;
};

#pragma once
