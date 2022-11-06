#ifndef _BULLETMANAGER_INCLUDE
#define _BULLETMANAGER_INCLUDE

#include "Bullet.h"
#include "TileMap.h"


class BulletManager
{
public:
	void createPlayerBullet(float posPlayerx, float posPlayery, int type, ShaderProgram& shaderProgram);
	void createEnemyBullet(float posEnemyx, float posEnemyy, float posPlayerx, float posPlayery, ShaderProgram& shaderProgram);
	void setTileMap(TileMap* tileMap);
	void update(int deltaTime);
	void render();

	void set_actBullets(vector<Bullet*> bullets);
	vector<Bullet*> ret_actBullets();


private:
	vector<Bullet*> activeBullets;
	TileMap* map;
};

#endif

#pragma once
