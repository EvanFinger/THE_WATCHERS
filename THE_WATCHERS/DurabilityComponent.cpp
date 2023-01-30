#include "stdafx.h"
#include "DurabilityComponent.h"

DurabilityComponent::DurabilityComponent(int max_health, int max_shield, int armor)
{
	this->healthComponent = new HealthComponent(max_health, armor);
	this->shieldComponent = new ShieldComponent(max_shield);
}

DurabilityComponent::~DurabilityComponent()
{
	delete this->healthComponent;
	delete this->shieldComponent;
}

void DurabilityComponent::damage(int damage)
{
	while (damage > 0)
	{
		if (this->healthComponent->getHealth() > 0)
		{
			this->healthComponent->updateHealth(1, 0);
			damage -= 1;
		}
		else
		{
			damage = 0;
		}
	}
}
