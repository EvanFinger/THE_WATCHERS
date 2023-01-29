#ifndef HEALTH_COMPONENT_H
#define HEALTH_COMPONENT_H

class HealthComponent
{
private:
	int maxHealth;
	int health;
	int armor; //not finalized
public:
	HealthComponent(int max_health, int armor);
	virtual ~HealthComponent();

	//Access
	const int getMaxHealth() const;
	const int getHealth() const;
	const int getArmor() const;

	//Functions
	void updateHealth(int damage, int healing);
	void updateArmor(int flatPEN, int percentagePEN);
};

#endif
