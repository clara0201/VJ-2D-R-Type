#include "Sprite.h"
#include "Player.h"

class Force
{

public:
	void init(ShaderProgram& shaderProgram, Player* player);
	void update(int deltaTime);
	void render();

	void checkCollision();
	void attachPlayer();
	void enable();
	void disable();

private:
	bool attached, enabled;
	Texture forceSpritesheet;
	Sprite* force;
	Player* player;
	//glm::ivec2 posForce;
};

