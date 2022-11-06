#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "BulletManager.h"
#include "Scene.h"

enum SpreadDeviation {
	DEVIATION_1L, DEVIATION_2L, NO_DEVIATION, DEVIATION_1R, DEVIATION_2R
};


void BulletManager::createPlayerBullet(float posPlayerx, float posPlayery, int typeOf, ShaderProgram &shaderProgram) {
	Bullet* new_bull;
	new_bull = new Bullet;
	new_bull->setTileMap(map);
	new_bull->createBullet(posPlayerx, posPlayery, 1, shaderProgram, 1.5f, typeOf, 1.f, 0.f);
	activeBullets.emplace_back(new_bull);	
}

void BulletManager::createEnemyBullet(float posEnemyx, float posEnemyy, float posPlayerx, float posPlayery, ShaderProgram& shaderProgram) {
	Bullet* new_bull;
	new_bull = new Bullet;
	float directionX = posPlayerx - posEnemyx;
	float directionY = posPlayery - posEnemyy;
	float squaredX= directionX * directionX;
	float squaredY = directionY * directionY;
	float division = sqrt(squaredX + squaredY);
	directionX = directionX / division;
	directionY = directionY / division;
	new_bull->setTileMap(map);
	new_bull->createBullet(posEnemyx, posEnemyy, 1, shaderProgram, 1.5f, 1, directionX, directionY);	
	activeBullets.emplace_back(new_bull);

}

void BulletManager::update(int deltaTime) {
	for (int i = 0; i < int(activeBullets.size()); ++i) {
		activeBullets[i]->update(deltaTime);
	}
}

void BulletManager::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void BulletManager::render() {
	for (int i = 0; i < int(activeBullets.size()); ++i) {
		activeBullets[i]->render();
	}
}

void BulletManager::set_actBullets(vector<Bullet*> bullets) {
	activeBullets = bullets;
}

vector<Bullet*> BulletManager::ret_actBullets() {
	return activeBullets;
}
