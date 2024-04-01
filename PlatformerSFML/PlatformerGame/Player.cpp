#include "Precomp.h"
#include "Player.h"

void Player::initVariables() {
	this->state = Idle;
}

void Player::initTexture() {
	if (!texture.loadFromFile("Knight/16x16 knight 2 v3.png")) {
		std::cout << "Could not load Player idle texture sheet"<<"\n";
	}
}

void Player::initSprite() {
	this->pModel.setTexture(&texture, false);
	/*this->pModel.setOutlineColor(sf::Color::Green);
	this->pModel.setOutlineThickness(1.f);*/
	this->currentFrame = sf::IntRect(0, 0, 64, 64);
	this->pModel.setTextureRect(this->currentFrame);
	this->pModel.setScale(4.f, 4.f);
	this->pModel.setSize(sf::Vector2f(64, 64));
	this->pModel.setOrigin(this->pModel.getSize() / 2.f);
	
}

void Player::render(sf::RenderTarget& target) {
	target.draw(this->pModel);
	this->pHitbox.setSize(sf::Vector2f(40, 68));
	this->pHitbox.setPosition(this->pModel.getPosition().x-20.f, this->pModel.getPosition().y-4.f);
	/*this->pHitbox.setFillColor(sf::Color::Red);
	target.draw(this->pHitbox);*/
}

void Player::initAnimations() {
	this->clock.restart();
	this->animationSwap = true;
}

void Player::physics() {
	this->vMaxX = 11.f;
	this->vMinX = 1.f;
	this->vMaxY = 11.f;
	this->acceleration = 1.2f;
	this->drag = 0.9f;
	this->gravity=8.f;
}

Player::Player() {
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimations();
	this->physics();
}

Player::~Player() {

}

void Player::movement(const float x, const float y){
	this->velocity.x += x * this->acceleration;
	if (std::abs(this->velocity.x) > this->vMaxX && !(this->jumpClock.getElapsedTime().asSeconds() >= 0.8f)) {
		if (this->velocity.x < 0.f) {
			this->velocity.x = this->vMaxX * -1.f;
		}
		else this->velocity.x = this->vMaxX * 1.f;
	}
	this->acceleration = 1.2f;
}

Collision Player::GetCollisionModel()
{
	return Collision(pModel);
}

Collision Player::GetCollisionHitbox()
{
	return Collision(pHitbox);
}

void Player::updatePhysics() {
	if (this->jumpClock.getElapsedTime().asSeconds() >= 0.45f) {
		this->velocity.y += 0.7 * this->gravity;
		if (std::abs(this->velocity.y) > this->vMaxY) {
			if (this->velocity.y < 0.f) {
				this->velocity.y = this->vMaxY * -1.f;
			}
			else this->velocity.y = this->vMaxY * 1.f;
		}
		this->velocity *= this->drag;
		if (std::abs(this->velocity.x) < this->vMinX) {
			this->velocity.x = 0.f;
		}
	}
	this->pModel.move(this->velocity);
}

void Player::udateMovement() {
	if (gameHasBegun) {
		if (!endIsReached) {
			this->state = Idle;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && this->jumpClock.getElapsedTime().asSeconds() >= 1.5f) {
				this->jumpClock.restart();
				this->state = Jump;
				this->velocity.y = -10.f;
				this->acceleration = 1.6f;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
				this->state = RunningL;
				this->movement(-1.f, 0.f);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
				this->movement(1.f, 0.f);
				this->state = RunningR;
			}
		}
	}
}

const bool& Player::getAnimationSwap() {
	animationSwap = this->animationSwap;
	if (this->animationSwap) {
		this->animationSwap = false;
	}
	return animationSwap;
}

const sf::Vector2f Player::getPosition() {
	return this->pModel.getPosition();
}

const sf::Vector2f Player::getHitboxPosition() {
	return this->pModel.getOrigin();
}

const sf::Vector2f Player::getHitboxSize() const {
	return this->pModel.getSize();
}

const sf::FloatRect Player::getGlobalBounds() const {
	return this->pModel.getGlobalBounds();
}

void Player::setPosition(const float x, const float y) {
	this->pModel.setPosition(x, y);
}

void Player::resetVelocityY() {
	this->velocity.y = 0.f;
}

void Player::resetVelocityX() {
	this->velocity.x = 0.f;
}

void Player::resetClock() {
	this->clock.restart();
	this->animationSwap = true;
}

void Player::resetJumpClock() {
	this->jumpClock.restart();
}

void Player::updateAnimations() {
	if (!endIsReached) {
		if (this->state == PlayerState::Idle && this->jumpClock.getElapsedTime().asSeconds() >= 0.4) {
			if (this->clock.getElapsedTime().asSeconds() >= 0.1f || this->getAnimationSwap()) {
				this->currentFrame.top = 0.f;
				this->currentFrame.left += 64.f;
				if (this->currentFrame.left >= 320.f) {
					this->currentFrame.left = 0;
				}
				this->clock.restart();
				this->pModel.setTextureRect(this->currentFrame);
			}
		}

		if (this->state == PlayerState::Jump) {
			if (this->getAnimationSwap()) {
				this->currentFrame.top = 128.f;
				this->currentFrame.left = 64.f;
				this->clock.restart();
				this->pModel.setTextureRect(this->currentFrame);
			}
		}
		if (this->state == PlayerState::RunningR && this->jumpClock.getElapsedTime().asSeconds() >= 0.25f) {
			if (this->clock.getElapsedTime().asSeconds() >= 0.06f || this->getAnimationSwap()) {
				this->currentFrame.top = 64.f;
				this->currentFrame.left += 64.f;
				if (this->currentFrame.left >= 448.f) {
					this->currentFrame.left = 0;
				}
				this->clock.restart();
				this->pModel.setTextureRect(this->currentFrame);
			}
			this->pModel.setScale(4.f, 4.f);
			this->pModel.setOrigin(this->pModel.getSize() / 2.f);
		}
		if (this->state == PlayerState::RunningL && this->jumpClock.getElapsedTime().asSeconds() >= 0.25f) {
			if (this->clock.getElapsedTime().asSeconds() >= 0.06f || this->getAnimationSwap()) {
				this->currentFrame.top = 64.f;
				this->currentFrame.left += 64.f;
				if (this->currentFrame.left >= 448.f) {
					this->currentFrame.left = 0;
				}
				this->clock.restart();
				this->pModel.setTextureRect(this->currentFrame);
			}
			this->pModel.setScale(-4.f, 4.f);
			this->pModel.setOrigin(this->pModel.getSize() / 2.f);
		}
	}
	else {
		if (this->clock.getElapsedTime().asSeconds() >= 0.06f || this->getAnimationSwap()) {
			this->currentFrame.top = 64.f;
			this->currentFrame.left += 64.f;
			if (this->currentFrame.left >= 448.f) {
				this->currentFrame.left = 0;
			}
			this->clock.restart();
			this->pModel.setTextureRect(this->currentFrame);
		}
		this->pModel.setScale(4.f, 4.f);
		this->pModel.setOrigin(this->pModel.getSize() / 2.f);
	}
}

void Player::update() {
	this->udateMovement();
	this->updateAnimations();
	this->updatePhysics();
}

