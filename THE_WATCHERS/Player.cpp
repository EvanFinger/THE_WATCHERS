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
	
	this->createMovementComponent(250.f, 10.f, 4.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE_LEFT", 10.f, 0, 0,7, 0, 16, 16);

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

	this->animationComponent->play("IDLE_LEFT", dt);
}
