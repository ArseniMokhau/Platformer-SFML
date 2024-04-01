#include "Precomp.h"
#include "Slime.h"


void Slime::initVariables() {
	this->slimeState = slimeIdle;
	this->lookDir = Left;
}

void Slime::initTexture() {
	if (!this->texture.loadFromFile("Slime/slime_idle3.png")) {
		std::cout << "Could not load Slime idle texture sheet" << "\n";
	}
}

void Slime::initSprite() {
	this->sprite.setTexture(this->texture);
	this->currentFrame = sf::IntRect(0, 0, 72, 80);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(4.f, 4.f);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 11.f, 32.f);
}

void Slime::render(sf::RenderTarget& target) {
	sHitbox.setSize(sf::Vector2f(54, 64));
	sHitbox.setPosition(this->sprite.getPosition());
	/*sHitbox.setFillColor(sf::Color::Red);
	target.draw(sHitbox);*/
	target.draw(this->sprite);
	
}

void Slime::initAnimations() {
	this->clock.restart();
	this->animationSwapSlime = true;
}

void Slime::physics() {
	this->vMaxX = 5.f;
	this->vMinX = 1.f;
	this->acceleration = 1.5f;
	this->drag = 0.9f;
}

Slime::Slime() {
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->physics();
}

Slime::~Slime() {

}

Collision Slime::GetCollision()
{
	return Collision(sHitbox);
}

void Slime::movement(const float x, const float y) {
	this->velocity.x += x * this->acceleration;
	if (std::abs(this->velocity.x) > this->vMaxX) {
		if (this->velocity.x < 0.f) {
			this->velocity.x = this->vMaxX * -1.f;
		}
		else this->velocity.x = this->vMaxX * 1.f;
	}
	this->acceleration = 1.2f;
}

void Slime::updatePhysics() {
		this->velocity *= this->drag;
		if (std::abs(this->velocity.x) < this->vMinX) {
			this->velocity.x = 0.f;
		}
	this->sprite.move(this->velocity);
}

void Slime::udateMovement() {
	this->slimeState = slimeIdle;
	if (this->cooldownClock.getElapsedTime().asSeconds() >= 2.f && this->lookDir==Left) {
		this->slimeState = MovingL;
		this->velocity.x = -9.f;
		this->cooldownClock.restart();
		i++;
		if (i >= 6) {
			this->lookDir = Right;
			i = 0;
		}
	}
	if (this->cooldownClock.getElapsedTime().asSeconds() >= 2.f && this->lookDir == Right) {
		this->slimeState = MovingR;
		this->velocity.x = 9.f;
		this->cooldownClock.restart();
		i++;
		if (i >= 6) {
			this->lookDir = Left;
			i = 0;
		}
	}
}

const bool& Slime::getAnimationSwapSlime() {
	animationSwapSlime = this->animationSwapSlime;
	if (this->animationSwapSlime) {
		this->animationSwapSlime = false;
	}
	return animationSwapSlime;
}

const sf::Vector2f Slime::getPosition() {
	return this->sprite.getPosition();
}

const sf::Vector2f Slime::getHitboxPosition() {
	return this->sHitbox.getPosition();
}

const sf::Vector2f Slime::getHitboxSize() {
	return this->sHitbox.getSize();
}

const sf::FloatRect Slime::getGlobalBounds() const {
	return this->sprite.getGlobalBounds();
}

void Slime::setPosition(const float x, const float y) {
	this->sprite.setPosition(x, y);
}

void Slime::resetVelocityY() {
	this->velocity.y = 0.f;
}

void Slime::resetVelocityX() {
	this->velocity.x = 0.f;
}

void Slime::resetClock() {
	this->clock.restart();
	this->animationSwapSlime = true;
}

void Slime::resetCooldownClock() {
	this->cooldownClock.restart();
}

void Slime::updateAnimations() {
	if (this->slimeState == SlimeState::slimeIdle) {
		if (this->clock.getElapsedTime().asSeconds() >= 0.1f && this->cooldownClock.getElapsedTime().asSeconds() >= 0.35f || this->getAnimationSwapSlime() && this->cooldownClock.getElapsedTime().asSeconds() >= 0.35f) {
			this->texture.loadFromFile("Slime/slime_idle3.png");
			this->currentFrame.top = 288.f;
			this->currentFrame.left += 80.f;
			if (this->currentFrame.left >= 560.f) {
				this->currentFrame.left = 0;
			}
			this->clock.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}

	if (this->slimeState == SlimeState::slimeJump) {
	}

	if (this->slimeState == SlimeState::MovingR) {
		if (this->clock.getElapsedTime().asSeconds() >= 0.05f || this->getAnimationSwapSlime()) {
			this->texture.loadFromFile("Slime/slime_move.png");
			this->currentFrame.top = 288.f;
			this->currentFrame.left += 80.f;
			while (this->currentFrame.left >= 560.f) {
				this->currentFrame.left = 0;
			}
			this->clock.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(4.f, 4.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 11.f, 32.f);
	}
	if (this->slimeState == SlimeState::MovingL) {
		if (this->clock.getElapsedTime().asSeconds() >= 0.05f || this->getAnimationSwapSlime()) {
			this->texture.loadFromFile("Slime/slime_move.png");
			this->currentFrame.top = 288.f;
			this->currentFrame.left += 80.f;
			if (this->currentFrame.left >= 560.f) {
				this->currentFrame.left = 0;
			}
			this->clock.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(-4.f, 4.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 7.f, 32.f);
	}
}

void Slime::update() {
	this->udateMovement();
	this->updateAnimations();
	this->updatePhysics();
}
