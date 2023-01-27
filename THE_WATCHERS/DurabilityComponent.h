#ifndef DURABILITY_COMPONENT_H
#define DURABILITY_COMPONENT_H

#include "HealthComponent.h"
#include "ShieldComponent.h"

class DurabilityComponent
{
private:

protected:
	
public:
	//Public Components
	HealthComponent* healthComponent;
	ShieldComponent* shieldComponent;


	DurabilityComponent(int max_health, int max_shield, int armor);
	virtual ~DurabilityComponent();

	//Access

	//Functions

	void damage(int damage);
	void heal(int heal);
	void recharge(int recharge);
};

#endif