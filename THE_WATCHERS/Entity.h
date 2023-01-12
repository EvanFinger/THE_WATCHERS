#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComp.h"

class Entity
{
private:
	void initVariables();

protected:

	sf::Texture* texture;
	sf::Sprite* sprite;

	MovementComp* movementComponent;

public:
	Entity();
	virtual ~Entity();

	//Component Funtions
	void createSprite(sf::Texture* texture);
	void createMovementComponent(const float maxVelocity);

	//Functions
	virtual void setPosition(const float& x, const float& y);
	virtual void move(const float& dt, const float dir_x, const float dir_y);
	virtual void setScale(float x, float y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

#endif