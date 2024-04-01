#pragma once
class Tilemap : public sf::Drawable
{
private:
	sf::Vector2f Point1, Point2;
	sf::Color Colour;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const;
public:
	Tilemap();
	~Tilemap();
	void initTiles();
	void update();
	void render();
};

