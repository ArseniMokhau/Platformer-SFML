#pragma once
#include "Collision.h"
class Suriken
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Clock clock;
	sf::RectangleShape surHitbox;

	sf::IntRect currentFrame;

	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
public:
	Suriken();
	virtual ~Suriken();
	const sf::Vector2f getPosition();
	const sf::Vector2f getHitboxPosition();
	const sf::FloatRect getGlobalBounds() const;
	Collision GetCollision();

	void setPosition(const float x, const float y);

	void resetClock();
	void updateAnimations();
	void update();
	void render(sf::RenderTarget& target);
};

