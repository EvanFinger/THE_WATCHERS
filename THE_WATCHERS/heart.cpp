#include "stdafx.h"
#include "heart.h"

heart::heart(float x, float y, sf::Texture& texture_sheet)
{
	this->setPosition(x, y);

	this->createAnimationComponent(texture_sheet);
	this->animationComponent->addAnimation("HEART_IDLE", 10.f, 0, 0, 0, 0, 16, 16);
}

heart::~heart()
{
	
}

void heart::update(const float &dt)
{
	this->animationComponent->play("HEART_IDLE", dt);
}

