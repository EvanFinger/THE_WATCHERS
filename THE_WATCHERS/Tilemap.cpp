#include "stdafx.h"
#include "Tilemap.h"

Tilemap::Tilemap()
{
	this->gridSizeF = 50.f;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->mapSize.x = 50;
	this->mapSize.y = 50;
	this->layers = 1;

	if (!this->tileTexture.loadFromFile("Images/tst.png"))
		std::cout << "ERROR LOADING TILE TEXTURE";

	this->map.resize(this->mapSize.x, std::vector< std::vector <Tile*> >());
	for (size_t x = 0; x < this->mapSize.x; x++)
	{
		for (size_t y = 0; y < this->mapSize.y; y++)
		{
			this->map[x].resize(this->mapSize.y, std::vector< Tile* >());
			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, &this->tileTexture ));
			}
		}
	}
}

Tilemap::~Tilemap()
{
	for (size_t x = 0; x < this->mapSize.x; x++)
	{
		for (size_t y = 0; y < this->mapSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
			}
		}
	}
}

void Tilemap::update()
{

}

void Tilemap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if(z)
					z->render(target);
			}
		}
	}
}
