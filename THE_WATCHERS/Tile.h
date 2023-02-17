#ifndef TILE
#define TILE



class Tile
{
private:

	//rendering objects/colors
	std::vector<sf::Texture> textures;
	std::vector<sf::Sprite> sprites;
	
protected:

	sf::RectangleShape shape;
public:
	Tile();
	//Tile(float x, float y, float grid_size_f, sf::Color color);
	Tile(float x, float y, float grid_size_f, sf::Texture* texture = nullptr);
	virtual ~Tile();


	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

#endif