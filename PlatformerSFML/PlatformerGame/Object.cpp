#include "Precomp.h"
#include "Object.h"


Object::Object(sf::Vector2f position, sf::Vector2f size, std::string name) {
	if (name == "web") {
		if (!this->texture.loadFromFile("Map/environment.png")) {
			std::cout << "Could not load Web texture" << "\n";
		}
		this->currentFrame = sf::IntRect(0, 360, 48, 24);
		wHitbox.setTexture(&texture, false);
		wHitbox.setTextureRect(this->currentFrame);
		wHitbox.setScale(1.7f, 1.3f);
	}
	if (name == "lever") {
		if (!this->texture.loadFromFile("Map/Spear.png")) {
			std::cout << "Could not load Lever texture" << "\n";
		}
		this->currentFrame = sf::IntRect(32, 0, 16, 64);
		wHitbox.setTexture(&texture, false);
		wHitbox.setTextureRect(this->currentFrame);
		wHitbox.setScale(2.f, 2.f);
	}
	wHitbox.setSize(size);
	wHitbox.setOrigin(75.f / 2.f, 75.f/2.f);
	wHitbox.setPosition(position);
}

const sf::Vector2f Object::getPosition() {
	return this->wHitbox.getPosition();
}

Object::~Object()
{
}

void Object::render(sf::RenderTarget& target)
{
	target.draw(wHitbox);
}

Collision Object::GetCollision()
{
	return Collision(wHitbox);
}