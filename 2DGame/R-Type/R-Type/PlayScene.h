#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Scene.h"


// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class PlayScene : public Scene
{

public:
	PlayScene();
	~PlayScene();

	void init();
	void update(int deltaTime);
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

	string state;

};


#endif // _SCENE_INCLUDE

