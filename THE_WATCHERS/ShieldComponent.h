#ifndef SHIELD_COMPONENT_H
#define SHIELD_COMPONENT_H

class ShieldComponent
{
private:
	int max_shield;
	int shield;
public:
	ShieldComponent(int max_shield);
	virtual ~ShieldComponent();

	//Access
	const int getShield() const;

	//Functions
	void updateShield(int shield_damage, int shield_recharge);
};

#endif