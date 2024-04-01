#pragma once

class Collision
{
private:
	sf::RectangleShape& body;
public:
	Collision(sf::RectangleShape& body);
	~Collision();
	void Move(float dx, float dy) const;
	bool leverIsSet;

	bool checkCollision(const Collision& other, float push, bool leverIsSet) const;

	sf::Vector2f GetPosition() const { return body.getPosition(); }
	sf::Vector2f GetHalfSize() const { return body.getPosition()/2.f; }
};

