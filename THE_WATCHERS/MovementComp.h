#ifndef MOVEMENT_COMP_H
#define MOVEMENT_COMP_H

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <vector>
#include <stack>
#include <map>

#include "SFML\System.hpp"
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Network.hpp"

class MovementComp
{
private:
	float maxVelocity;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	sf::Vector2f deceleration;

	//Inits

public:
	MovementComp(float maxVelocity);
	virtual ~MovementComp();

	//access
	const sf::Vector2f& getVelocity() const;

	//Funcs
	void move(const float dir_x, const float dir_y);
	void update(const float& dt);
};


#endif