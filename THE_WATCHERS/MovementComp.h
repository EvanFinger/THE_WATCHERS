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

class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity;
	float acceleration;
	float deceleration;

	sf::Vector2f velocity;


	//Inits

public:
	MovementComponent(sf::Sprite& sprite, 
		float maxVelocity, float acceleration, float deceleration);
	virtual ~MovementComponent();

	//access
	const sf::Vector2f& getVelocity() const;

	//Funcs
	void move(const float dir_x, const float dir_y, const float& dt);
	void update(const float& dt);
};


#endif