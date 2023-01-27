#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComp.h"
#include "AnimationComponent.h"
#include "DamageComponent.h"
#include "DurabilityComponent.h"

class Entity
{
private:
	void initVariables();

protected:

	sf::Sprite sprite;

	MovementComponent* movementComponent;
	DamageComponent* damageComponent;
	AnimationComponent* animationComponent;

public:
	//Public Components
	DurabilityComponent* durabilityComponent;

	Entity();
	virtual ~Entity();

	//Component Funtions
	void setTexture(sf::Texture& texture);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createDurabilityComponent(int max_health, int max_shield, int armor);

	//Functions
	virtual void setPosition(const float& x, const float& y);
	virtual void move(const float dir_x, const float dir_y, const float& dt);
	virtual void setScale(float x, float y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

#endif