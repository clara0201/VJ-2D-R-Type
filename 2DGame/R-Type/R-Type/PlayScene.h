#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Enemy.h"
#include "Scene.h"
#include "MenuScene.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class PlayScene : public Scene
{

public:
	PlayScene(MenuScene* menuS);
	~PlayScene();

	void init();
	void update(int deltaTime);
	void initEnemies();
	void moveEnemies();
	void stopEnemies();
	void checkHits();
	void checkEnemiesHits();
	void checkBullets();
	void render();

	virtual Scene* changeState();

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int tileMapDispl;
	Texture backgroundSpritesheet;
	vector<Enemy*> enemyList;
	vector<Enemy*> flowerList;

	Sprite* background;
	BulletManager bulletManager;
	string state;
	MenuScene* menu;
	int cooldown;
	int directionCooldown;
	bool movingUp;
	int flowerIterator;
	int butterflyShootCooldown;
};


#endif // _SCENE_INCLUDE

