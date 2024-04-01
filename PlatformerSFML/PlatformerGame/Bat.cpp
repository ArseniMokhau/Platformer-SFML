
#include "Precomp.h"
#include "Bat.h"
/*
void Bat::initVariables()
{
	this->state = FlyingR;
	this->velocity.x=1.f;
}

void Bat::initTexture()
{
	if (!this->texture1.loadFromFile("Bat/Bat_Sprite_Sheet.png")) {
		std::cout << "Could not load Player idle texture sheet" << "\n";
	}
}

void Bat::initSprite()
{
	this->sprite1.setTexture(this->texture1);
	this->currentFrame = sf::IntRect(0, 0, 16, 24);
	this->sprite1.setTextureRect(this->currentFrame);
	this->sprite1.setScale(2.f, 2.f);
	this->sprite1.setOrigin(0, 0);
}

void Bat::render(sf::RenderTarget& target) {
	target.draw(this->sprite1);
}

void Bat::initAnimations() {
	this->clock1.restart();
	this->animationSwap = true;
}

Bat::Bat()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
}

Bat::~Bat()
{
}

void Bat::movement(const float x, const float y)
{
	this->sprite1.move(this->velocity);
}

void Bat::udateMovement() {
	this->state = FlyingR;
	if (this->dirClock.getElapsedTime().asSeconds() >= 3.f) {
		if (this->state == BatState::FlyingR) {
			this->velocity.x = 1.f;
			this->state = FlyingL;
			this->dirClock.restart();
		}
		if (this->state == BatState::FlyingL) {
			this->velocity.x = -1.f;
			this->state = FlyingR;
			this->dirClock.restart();
		}
	}
}

const sf::Vector2f Bat::getPosition()
{
	return this->sprite1.getPosition();
}

const sf::FloatRect Bat::getGlobalBounds() const
{
	return this->sprite1.getGlobalBounds();
}

void Bat::setPosition1(const float posX, const float posY) {
	this->sprite1.setPosition(posX, posY);
}

void Bat::resetClock()
{
	this->clock1.restart();
	this->animationSwap = true;
}

void Bat::resetDirClock()
{
	this->dirClock.restart();
}

void Bat::updateAnimations()
{
	if (this->state == BatState::FlyingR) {
		if (this->clock1.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame.top = 24.f;
			this->currentFrame.left += 16.f;
			if (this->currentFrame.left >= 64.f) {
				this->currentFrame.left = 0;
			}
			this->clock1.restart();
			this->sprite1.setTextureRect(this->currentFrame);
		}
		this->sprite1.setScale(2.f, 2.f);
		this->sprite1.setOrigin(0, 0);
	}
	if (this->state == BatState::FlyingL) {
		if (this->clock1.getElapsedTime().asSeconds() >= 0.1f) {
			this->currentFrame.top = 24.f;
			this->currentFrame.left += 16.f;
			if (this->currentFrame.left >= 64.f) {
				this->currentFrame.left = 0;
			}
			this->clock1.restart();
			this->sprite1.setTextureRect(this->currentFrame);
		}
		this->sprite1.setScale(-2.f, 2.f);
		this->sprite1.setOrigin(this->sprite1.getGlobalBounds().width / 1.f, 0.f);
	}
}

void Bat::update()
{
	this->updateAnimations();
	this->udateMovement();
}
*/
