#include "stdafx.h"
#include "Player.h"


//Init Functions
void Player::initVariables()
{
}

void Player::initComponents()
{
	
}

//Constructors/Destructors
Player::Player(float x, float y, int max_health, sf::Texture& texture_sheet)
{
	this->initVariables();
	this->setPosition(x, y);
	
	this->createMovementComponent(500.f, 20.f, 10.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("MOVE_RIGHT", 10.f, 0, 0,11, 0, 64, 64);

	this->createDurabilityComponent(max_health, 0, 0);

}

Player::~Player()
{
}

void Player::update(const float& dt)
{
	if (this->movementComponent)
		this->movementComponent->update(dt);
	Entity::update(dt);

	this->animationComponent->play("MOVE_RIGHT", dt);
}
