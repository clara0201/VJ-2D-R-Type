#pragma once

// base class for all scenes in the game
class Scene
{
public:
	virtual void init() = 0;
	virtual void render() = 0;
	virtual void update(int deltaTime) = 0;
	virtual Scene* changeState() = 0;
};

