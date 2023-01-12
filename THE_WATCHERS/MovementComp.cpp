#include "MovementComp.h"

MovementComp::MovementComp(float maxVelocity)
{
	this->maxVelocity = maxVelocity;
}

MovementComp::~MovementComp()
{
}

const sf::Vector2f& MovementComp::getVelocity() const
{
	return this->velocity;
}

//funcs

void MovementComp::move(const float dir_x, const float dir_y)
{
	this->velocity.x = dir_x * maxVelocity;
	this->velocity.y = dir_y * maxVelocity;

}

void MovementComp::update(const float& dt)
{

}
