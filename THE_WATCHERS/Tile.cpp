#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
}

//Tile::Tile(float x, float y, float grid_size_f, sf::Color color)
//{
//	this->shape.setPosition(x, y);
//	this->shape.setSize(sf::Vector2f(grid_size_f, grid_size_f));
//	this->shape.setFillColor(sf::Color::Blue); //temp color
//	this->shape.setOutlineThickness(1);
//	this->shape.setOutlineColor(sf::Color::Black);
//}

Tile::Tile(float x, float y, float grid_size_f, sf::Texture* texture)
{
	this->shape.setPosition(x, y);
	this->shape.setSize(sf::Vector2f(grid_size_f, grid_size_f));
	this->shape.setOutlineThickness(1);
	this->shape.setOutlineColor(sf::Color::Transparent);
	this->shape.setTexture(texture);
}

Tile::~Tile()
{
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
