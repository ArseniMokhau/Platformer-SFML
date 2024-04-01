#include "Precomp.h"
#include "Player.h"
#include "Slime.h"
#include "Suriken.h"
#include "Object.h"
#include "Collision.h"
#pragma once

class Game
{
private:
	sf::Font font;
	sf::Text textEnd;
	sf::Text textPressESC;
	sf::Text textStart;
	sf::Text textPressSpace;
	sf::Text textD;
	sf::Vector2i exitPosition;
	sf::Vector2i playerPosition;
	std::vector<sf::Vector2i> enemyPositions;

	sf::Shader shader;
	sf::RectangleShape fade;

	sf::RenderWindow window;
	sf::RenderWindow menuWindow;
	sf::RenderWindow escWindow;
	sf::View myView;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Event event;

	Player* player;
	Slime* slime;
	Suriken* suriken;

	bool leverIsSet;
	bool gameHasBegun;
	bool foward;
	int multi = 235;
	int i = 0;

	void initWindow();
	void initPlayer();
	void initEntities();
	void initTiles();
	void setUpEntityPositions();
	void setUpTiles();

public:

	bool endIsReached;
	std::vector<std::vector<Object*>> objects;

	Game();
	virtual ~Game();
	
	void updatePlayer();
	void updateEntities();

	void updateCollision();
	void updateEntityCollision();

	void update();

	void renderPlayer();
	void renderEntities();
	void renderTiles();

	void render();

	const sf::RenderWindow& getWindow() const;
};

