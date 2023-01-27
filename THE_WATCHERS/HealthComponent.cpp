#include "HealthComponent.h"
#include <iostream>

HealthComponent::HealthComponent(int max_health, int armor)
{
	this->maxHealth = max_health;
	this->armor = armor;

	this->health = maxHealth;
}

HealthComponent::~HealthComponent()
{

}

const int HealthComponent::getMaxHealth() const
{
	return maxHealth;
}

//Access
const int HealthComponent::getHealth() const
{
	return this->health;
}

const int HealthComponent::getArmor() const
{
	return this->armor;
}

void HealthComponent::updateHealth(int damage, int healing)
{
	this->health += healing;
	this->health -= damage;
}

void HealthComponent::updateArmor(int flatPEN, int percentagePEN)
{

}

//Functions
