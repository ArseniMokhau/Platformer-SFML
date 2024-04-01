#pragma once
#include"Collision.h"

enum PlayerState{Idle=0, RunningL=1, RunningR, Jump, Dodge, Fall};
class Player
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Clock clock;
	sf::Clock jumpClock;
	sf::Event event;
	sf::RectangleShape pModel;
	sf::RectangleShape pHitbox;

	bool animationSwap;
	sf::IntRect currentFrame;
	

	sf::Vector2f velocity;
	bool spaceIsHeld = false;
	float vMaxX;
	float vMinX;
	float vMaxY;
	float acceleration;
	float accelerationY;
	float drag;
	float gravity;
	short state;

	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	void physics();
public:
	bool endIsReached = false;
	bool gameHasBegun = false;
	Player();
	virtual ~Player();
	const bool& getAnimationSwap();
	const sf::Vector2f getPosition();
	const sf::Vector2f getHitboxPosition();
	const sf::Vector2f getHitboxSize()const;
	const sf::FloatRect getGlobalBounds() const;
	Collision GetCollisionModel();
	Collision GetCollisionHitbox();

	void setPosition(const float x, const float y);
	void resetVelocityY();
	void resetVelocityX();

	void movement(const float x, const float y);
	void updatePhysics();
	void udateMovement();
	void resetClock();
	void resetJumpClock();
	void updateAnimations();
	void update();
	void render(sf::RenderTarget& target);
};

