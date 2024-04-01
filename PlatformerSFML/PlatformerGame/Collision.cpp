#include "Precomp.h"
#include "Collision.h"


Collision::Collision(sf::RectangleShape& body):body(body) {

}

Collision::~Collision() {

}

void Collision::Move(float dx, float dy) const {
	body.move(dx, dy);
}

bool Collision::checkCollision(const Collision& other, float push, bool leverIsSet) const{
	sf::Vector2f otherPosition = other.GetPosition();
	sf::Vector2f thisPosition = GetPosition();
	sf::Vector2f otherHalfSize;
	sf::Vector2f thisHalfSize;
	otherHalfSize = other.GetHalfSize();
	thisHalfSize = GetHalfSize();
	leverIsSet = leverIsSet;


	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;

	float collisionX = abs(deltaX) - (32.f + 25.f);
	float collisionY = abs(deltaY) - (32.f + 25.f);
	

	if (collisionX<=0.0f && collisionY <= 0.0f && !leverIsSet) {

		if(otherPosition.x > thisPosition.x)
		Move(collisionX*push, 0.0f);

		else Move(-collisionX * push, 0.0f);

		return true;
	}

	return false;
}