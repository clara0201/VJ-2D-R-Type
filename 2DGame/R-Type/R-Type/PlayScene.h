#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Scene.h"
#include "MenuScene.h"
#include "Force.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class PlayScene : public Scene
{

public:
	PlayScene(MenuScene* menuS);
	~PlayScene();

	void init();
	void update(int deltaTime);
	void checkBullets();
	void render();

	virtual Scene* changeState();

private:
	void initShaders();

private:
	TileMap *map;
	Player *player;
	Force* force;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	int tileMapDispl;
	Texture backgroundSpritesheet, forceUnitTex;
	Sprite* background, *forceUnit;
	BulletManager bulletManager;
	string state;
	MenuScene* menu;
	bool forceHit;

};


#endif // _SCENE_INCLUDE

