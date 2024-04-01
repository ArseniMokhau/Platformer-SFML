#pragma once
#include "Collision.h"

class Object
{
private:
	sf::RectangleShape wHitbox;
	sf::Texture texture;
	sf::IntRect currentFrame;
public:
	sf::Sprite sprite;
	Object(sf::Vector2f position, sf::Vector2f size, std::string name);
	~Object();
	void render(sf::RenderTarget& target);
	const sf::Vector2f getPosition();
	Collision GetCollision();
};

