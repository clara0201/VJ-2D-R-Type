#include "Sprite.h"

class Force
{

public:
	void init(ShaderProgram& shaderProgram);
	void update(int deltaTime);
	void render();

	void checkCollision();
	void attachPlayer();
	void enable();

private:
	bool attached, enabled;
	Texture forceSpritesheet;
	Sprite* force;
};

