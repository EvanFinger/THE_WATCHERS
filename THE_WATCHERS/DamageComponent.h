#ifndef DAMAGE_COMPONENT_H
#define DAMAGE_COMPONENT_H

enum damage_constants { INSTAKILL = -1, DAMAGE_NULL = 0 };
class DamageComponent
{
private:
	int damage;
public:
	DamageComponent(int damage);
	virtual ~DamageComponent();

	
//Access
	const int& getDamage() const;

//Funtions
	void modifyDamage(int new_damage);

};

#endif