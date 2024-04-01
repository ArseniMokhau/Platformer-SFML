#include "Precomp.h"
#include "Suriken.h"



void Suriken::initVariables() {
}

void Suriken::initTexture() {
	if (!this->texture.loadFromFile("Suriken/Suriken.png")) {
		std::cout << "Could not load Slime idle texture sheet" << "\n";
	}
}

void Suriken::initSprite() {
	this->sprite.setTexture(this->texture);
	this->currentFrame = sf::IntRect(0, 0, 32, 32);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(2.5f, 2.5f);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 28.f, 3.f);
	this->sprite.setColor(sf::Color(245, 255, 255, 180));
}

void Suriken::render(sf::RenderTarget& target) {
	surHitbox.setSize(sf::Vector2f(66, 66));
	surHitbox.setPosition(this->sprite.getPosition());
	/*surHitbox.setFillColor(sf::Color::Blue);
	target.draw(surHitbox);*/
	target.draw(this->sprite);
}

void Suriken::initAnimations() {
	this->clock.restart();
}

Suriken::Suriken() {
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
}

Suriken::~Suriken() {

}


const sf::Vector2f Suriken::getPosition() {
	return this->sprite.getPosition();
}

const sf::Vector2f Suriken::getHitboxPosition() {
	return this->sprite.getOrigin();
}

const sf::FloatRect Suriken::getGlobalBounds() const {
	return this->sprite.getGlobalBounds();
}

void Suriken::setPosition(const float x, const float y) {
	this->sprite.setPosition(x, y);
}

Collision Suriken::GetCollision()
{
	return Collision(surHitbox);
}

void Suriken::resetClock() {
	this->clock.restart();
}

void Suriken::updateAnimations() {
	if (this->clock.getElapsedTime().asSeconds() >= 0.07f) {
		this->currentFrame.top = 0.f;
		this->currentFrame.left += 32.f;
		if (this->currentFrame.left >= 256.f) {
			this->currentFrame.left = 0;
		}
		this->clock.restart();
		this->sprite.setTextureRect(this->currentFrame);
	}
}

void Suriken::update() {
	this->updateAnimations();
}