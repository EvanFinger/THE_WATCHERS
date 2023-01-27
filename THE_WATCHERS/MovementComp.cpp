#include "MovementComp.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, 
	float maxVelocity, float acceleration, float deceleration)
	: sprite(sprite),maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{
}

const sf::Vector2f& MovementComponent::getVelocity() const
{
	return this->velocity;
}

//funcs

void MovementComponent::move(const float dir_x, const float dir_y, const float& dt )
{

	/*Accelerates sprite to maxVelocity*/
	this->velocity.x += this->acceleration * dir_x;

	this->velocity.y += this->acceleration * dir_y;
}

void MovementComponent::update(const float& dt)
{
	//Deceleration
	if (this->velocity.x > 0.f) //positive x
	{
		//Max Velocity Control
		if (this->velocity.x > this->maxVelocity)
			this->velocity.x = this->maxVelocity;

		//Deceleration
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f)
		{
			this->velocity.x = 0.f;
		}
	}
	else if (this->velocity.x < 0.f) //negative x
	{
		//max Velocity Control
		if (this->velocity.x < -this->maxVelocity)
			this->velocity.x = -this->maxVelocity;

		//Deceleration
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f)
		{
			this->velocity.x = 0.f;
		}
	}
	if (this->velocity.y > 0.f) //positive y
	{
		//Max Velocity Control
		if (this->velocity.y > this->maxVelocity)
			this->velocity.y = this->maxVelocity;

		//Deceleration
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f)
		{
			this->velocity.y = 0.f;
		}
	}
	else if (this->velocity.y < 0.f) //negative y
	{
		//Max Velocity Control
		if (this->velocity.y < -this->maxVelocity)
			this->velocity.y = -this->maxVelocity;

		//Deceleration
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f)
		{
			this->velocity.y = 0.f;
		}
	}
	//Final Movement
	this->sprite.move(this->velocity * dt);
}
