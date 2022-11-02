#include "Force.h"

enum ForceAnims
{
	IDLE
};

void Force::init(ShaderProgram& texProgram)
{
	attached = false;
	enabled = false;

	forceSpritesheet.loadFromFile("images/forceSpritesheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	force = Sprite::createSprite(glm::ivec2(16, 12), glm::vec2(0.25f, 1.0f), &forceSpritesheet, &texProgram);
	force->setNumberAnimations(4);

	force->setAnimationSpeed(IDLE, 6);
	force->addKeyframe(IDLE, glm::vec2(0.0f, 0.f));
	force->addKeyframe(IDLE, glm::vec2(0.25f, 0.f));
	force->addKeyframe(IDLE, glm::vec2(0.5f, 0.f));
	force->addKeyframe(IDLE, glm::vec2(0.75f, 0.f));

	force->changeAnimation(0);
	force->setPosition(glm::vec2(100, 100));
}

void Force::update(int deltaTime)
{
	force->update(deltaTime);

	checkCollision();
}

void Force::render()
{
	if(enabled) force->render();
}

void Force::enable() {
	enabled = true;
}

void Force::checkCollision()
{
}

void Force::attachPlayer()
{
}
