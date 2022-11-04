#include "Force.h"

enum ForceAnims
{
	IDLE
};

void Force::init(ShaderProgram& texProgram, Player* player)
{
	attached = false;
	enabled = false;
	this->player = player;

	forceSpritesheet.loadFromFile("images/forceSpritesheet.png", TEXTURE_PIXEL_FORMAT_RGBA);
	force = Sprite::createSprite(glm::ivec2(16, 12), glm::vec2(0.25f, 1.0f), &forceSpritesheet, &texProgram);
	force->setNumberAnimations(4);

	force->setAnimationSpeed(IDLE, 6);
	force->addKeyframe(IDLE, glm::vec2(0.0f, 0.f));
	force->addKeyframe(IDLE, glm::vec2(0.25f, 0.f));
	force->addKeyframe(IDLE, glm::vec2(0.5f, 0.f));
	force->addKeyframe(IDLE, glm::vec2(0.75f, 0.f));

	force->changeAnimation(0);
	force->setPosition(glm::ivec2(100, 0));

}

void Force::update(int deltaTime)
{
	force->update(deltaTime);

	checkCollision();
	if (attached) attachPlayer();
}

void Force::render()
{
	if(enabled) force->render();
}

void Force::enable() {
	enabled = true;
	force->setPosition(glm::ivec2(100, 200));

}

void Force::checkCollision()
{
	bool forceColX = player->getPosition().x + 28 >= force->getPosition().x && player->getPosition().x + 28 <= force->getPosition().x + 16;
	bool forceColY = player->getPosition().y + 16 >= force->getPosition().y && player->getPosition().x + 28 <= force->getPosition().x + 12;
	
	if (forceColX && forceColY && !attached) attached = true;
}

void Force::attachPlayer()
{
	force->setPosition(glm::vec2(player->getPosition().x + 26, player->getPosition().y+2));
}
