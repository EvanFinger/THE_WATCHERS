#include "DamageComponent.h"

DamageComponent::DamageComponent(int damage)
{
	this->damage = damage;
}

DamageComponent::~DamageComponent()
{

}

const int& DamageComponent::getDamage() const
{
	return this->damage;
}

void DamageComponent::modifyDamage(int new_damage)
{
	this->damage = new_damage;
}
