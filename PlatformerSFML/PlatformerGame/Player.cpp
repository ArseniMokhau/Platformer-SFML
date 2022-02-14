#include "Precomp.h"
#include "Player.h"

void Player::initVariables() {
	this->state = Idle;
}

void Player::initTexture() {
	if (!this->texture.loadFromFile("Knight/16x16 knight 2 v3.png")) {
		std::cout << "Could not load Player idle texture sheet"<<"\n";
	}
}

void Player::initSprite() {
	this->sprite.setTexture(this->texture);
	this->currentFrame = sf::IntRect(0, 0, 64, 64-16);
	this->sprite.setTextureRect(this->currentFrame);
	this->sprite.setScale(4.f, 4.f);
	this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 10.f,32.f);
}

void Player::render(sf::RenderTarget& target) {
	target.draw(this->sprite);
	sf::RectangleShape pHitbox;
	pHitbox.setFillColor(sf::Color::Transparent);
	pHitbox.setSize(sf::Vector2f(56, 64));
	pHitbox.setPosition(this->sprite.getPosition());
	target.draw(pHitbox);
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
	this->gravity=5.f;
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
}

void Player::updatePhysics() {
	if (this->jumpClock.getElapsedTime().asSeconds() >= 0.45f) {
		this->velocity.y += 0.7 * this->gravity;
		if (std::abs(this->velocity.y) > this->vMaxY && !(this->state == Jump)) {
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
	this->sprite.move(this->velocity);
}

void Player::udateMovement() {
	this->state = Idle;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))) {
		this->movement(-1.f, 0.f);
		this->state = RunningL;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && this->jumpClock.getElapsedTime().asSeconds() >= 1.5f) {
			this->jumpClock.restart();
			this->sprite.setScale(-4.f, 4.f);
			this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 7.f, 32.f);
			this->state = Jump;
			this->velocity.x = -11.f;
			this->velocity.y = -11.f;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))) {
		this->movement(1.f, 0.f);
		this->state = RunningR;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && this->jumpClock.getElapsedTime().asSeconds() >= 1.5f) {
			this->jumpClock.restart();
			this->sprite.setScale(4.f, 4.f);
			this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 10.f, 32.f);
			this->state = Jump;
			this->velocity.x = 11.f;
			this->velocity.y = -11.f;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && this->jumpClock.getElapsedTime().asSeconds() >= 1.5f) {
		this->jumpClock.restart();
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
		this->sprite.setScale(-4.f, 4.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 7.f, 32.f);
		this->state = Jump;
		this->velocity.x = -11.f;
		this->velocity.y = -11.f;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
		    this->sprite.setScale(4.f, 4.f);
		    this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 10.f, 32.f);
		    this->state = Jump;
		    this->velocity.x = 11.f;
		    this->velocity.y = -11.f;
	}
	else {
		this->state = Jump;
		this->velocity.y = -11.f;
	}
	}
}

const bool& Player::getAnimationSwap() {
	bool aSwap = this->animationSwap;
	if (this->animationSwap) {
		this->animationSwap = false;
	}
	return aSwap;
}

const sf::Vector2f Player::getPosition() {
	return this->sprite.getPosition();
}

const sf::Vector2f Player::getHitboxPosition() {
	return this->sprite.getOrigin();
}

const sf::FloatRect Player::getGlobalBounds() const {
	return this->sprite.getGlobalBounds();
}

void Player::setPosition(const float x, const float y) {
	this->sprite.setPosition(x, y);
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
	if (this->state == PlayerState::Idle) {
		 if (this->clock.getElapsedTime().asSeconds() >= 0.1f || this->getAnimationSwap()) {
			this->currentFrame.top = 0.f;
			this->currentFrame.left += 64.f;
			if (this->currentFrame.left >= 320.f) {
				this->currentFrame.left = 0;
			}
			this->clock.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	
	if (this->state == PlayerState::Jump) {
		 if (this->clock.getElapsedTime().asSeconds() >= 0.2f || this->getAnimationSwap()) {
			this->currentFrame.top = 128.f;
			if (this->currentFrame.left <= 128.f) {
				this->currentFrame.left += 64.f;
			}
			this->clock.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
	}
	if (this->state == PlayerState::RunningR) {
		 if (this->clock.getElapsedTime().asSeconds() >= 0.06f || this->getAnimationSwap()) {
		    this->currentFrame.top = 64.f;
			this->currentFrame.left += 64.f;
			if (this->currentFrame.left >= 448.f) {
				this->currentFrame.left = 0;
			}
			this->clock.restart();
			this->sprite.setTextureRect(this->currentFrame);	
		}
		 this->sprite.setScale(4.f, 4.f);
		 this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 10.f, 32.f);
	}
	if (this->state == PlayerState::RunningL) {
		if (this->clock.getElapsedTime().asSeconds() >= 0.06f || this->getAnimationSwap()) {
			this->currentFrame.top = 64.f;
			this->currentFrame.left += 64.f;
			if (this->currentFrame.left >= 448.f) {
				this->currentFrame.left = 0;
			}
			this->clock.restart();
			this->sprite.setTextureRect(this->currentFrame);
		}
		this->sprite.setScale(-4.f, 4.f);
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width / 7.f, 32.f);
	}
}

void Player::update() {
	this->udateMovement();
	this->updateAnimations();
	this->updatePhysics();
}

