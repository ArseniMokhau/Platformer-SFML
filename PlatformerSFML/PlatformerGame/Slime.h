#pragma once
#include"Collision.h"
enum SlimeState { slimeIdle = 0, MovingL = 1, MovingR, slimeJump};
enum LookDir { Left = 0, Right = 1};
class Slime
{
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Clock clock;
	sf::Clock cooldownClock;
	sf::Event event;

	bool animationSwapSlime;
	short slimeState;
	short lookDir;
	int i = 0;
	sf::IntRect currentFrame;
	sf::RectangleShape sHitbox;

	sf::Vector2f velocity;
	bool spaceIsHeld = false;
	float vMaxX;
	float vMinX;
	float acceleration;
	float drag;

	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimations();
	void physics();
public:
	Slime();
	virtual ~Slime();
	const bool& getAnimationSwapSlime();
	const sf::Vector2f getPosition();
	const sf::Vector2f getHitboxPosition();
	const sf::Vector2f getHitboxSize();
	const sf::FloatRect getGlobalBounds() const;
	Collision GetCollision();

	void setPosition(const float x, const float y);
	void resetVelocityY();
	void resetVelocityX();

	void movement(const float x, const float y);
	void updatePhysics();
	void udateMovement();
	void resetClock();
	void resetCooldownClock();
	void updateAnimations();
	void update();
	void render(sf::RenderTarget& target);
};