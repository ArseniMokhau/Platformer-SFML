#include "Precomp.h"
#include "Game.h"


void Game::initWindow() {
	this->window.create(sf::VideoMode(1280, 720), "Platformer", sf::Style::Titlebar | sf::Style::Close);
	this->texture.loadFromFile("Map/backgroundmap.png");
	this->sprite.setTexture(texture);
	this->sprite.setScale(3.65f, 3.65f);
	this->myView.setSize(1280, 720);
	this->window.setFramerateLimit(60);
	this->wall.setSize(sf::Vector2f(66, 63));
	this->wall.setFillColor(sf::Color::Transparent);
	this->space.setSize(sf::Vector2f(66, 63));
	this->space.setFillColor(sf::Color::Transparent);
	this->spikes.setSize(sf::Vector2f(66, 63));
	this->spikes.setFillColor(sf::Color::Transparent);
}
void Game::initPlayer() {
	this->player = new Player();
}

Game::Game() {
	this->initWindow();
	this->initPlayer();
	this->player->setPosition(4500.f, 2600.f);
}
Game::~Game() {
	delete this->player;
}
void Game::updatePlayer() {
	this->player->update();
}


void Game::updateCollision() {

	// walls//
	if (this->player->getPosition().y -42 > 2650.f) {
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x, 2650.f+42);
	}
	if (this->player->getPosition().y-12 < 1900.f) {
		this->player->resetVelocityX();
		this->player->setPosition(this->player->getPosition().x, 1900.f+12);
	}
	if (this->player->getPosition().x - 42 > 5885.f) {
		this->player->resetVelocityX();
		this->player->setPosition(5885.f + 42, this->player->getPosition().y);
	}
	//other constructions//
	if (this->player->getPosition().x - 42 >= 4775.f && this->player->getPosition().x - 42 <= 4865.f) {
		if (this->player->getPosition().y - 42 > 2460.f) {
			this->player->resetVelocityY();
			this->player->setPosition(this->player->getPosition().x, 2460.f + 42);
		}
	}
	if (this->player->getPosition().x -42 >= 4761.f && this->player->getPosition().x - 42 <= 4865.f && this->player->getPosition().y - 42 > 2465.f) {
		this->player->resetVelocityX();
		this->player->setPosition(4761.f+42, this->player->getPosition().y);
	}
	if (this->player->getPosition().x - 42 >= 4865.f && this->player->getPosition().x - 42 <= 5250 && this->player->getPosition().y - 42 > 2600.f) {
		this->player->resetVelocityX();
		this->player->resetVelocityY();
		this->player->setPosition(4500.f, 2600.f);
	}
	if (this->player->getPosition().x - 42 >= 5230.f && this->player->getPosition().x - 42 <= 5333) {
		if (this->player->getPosition().y - 42 > 2220.f) {
			this->player->resetVelocityY();
			this->player->setPosition(this->player->getPosition().x, 2220.f + 42);
		}
	}
	if (this->player->getPosition().x - 42 >= 5216.f && this->player->getPosition().x - 42 <= 5333 && this->player->getPosition().y - 42 > 2235.f) {
		this->player->resetVelocityX();
		this->player->setPosition(5216.f + 42, this->player->getPosition().y);
	}
	if (this->player->getPosition().x - 12 >= 5256.f && this->player->getPosition().x - 42 <= 5760.f && this->player->getPosition().y - 42 > 2238.f) {
		if (this->player->getPosition().x - 12 <= 5333.f) {
			this->player->resetVelocityX();
			this->player->setPosition(5333.f + 12, this->player->getPosition().y);
		}
	}
	if (this->player->getPosition().x - 12 >= 5333.f && this->player->getPosition().x - 42 <= 5760.f && this->player->getPosition().y - 42 > 2600.f) {
		this->player->resetVelocityX();
		this->player->resetVelocityY();
		this->player->setPosition(4500.f, 2600.f);
	}
	if (this->player->getPosition().x - 42 >= 5760.f && this->player->getPosition().x - 42 <= 5903) {
		if (this->player->getPosition().y - 42 > 2395.f) {
			this->player->resetVelocityY();
			this->player->setPosition(this->player->getPosition().x, 2395.f + 42);
		}
	}
	if (this->player->getPosition().x - 42 >= 5746.f && this->player->getPosition().x - 42 <= 5903 && this->player->getPosition().y - 42 > 2395.f) {
		this->player->resetVelocityX();
		this->player->setPosition(5746.f + 42, this->player->getPosition().y);
	}
}
void Game::update() {
	while (this->window.pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->window.close();
		}
		if (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Keyboard::Escape) {
			this->window.close();
		}
		if (this->event.type == sf::Event::KeyReleased && (this->event.key.code == sf::Keyboard::Keyboard::W || this->event.key.code == sf::Keyboard::Keyboard::A || this->event.key.code == sf::Keyboard::Keyboard::S || this->event.key.code == sf::Keyboard::Keyboard::D || this->event.key.code == sf::Keyboard::Keyboard::Space)) {
			this->player->resetClock();
		}
	}
	this->updatePlayer();
	this->updateCollision();
}
void Game::renderPlayer() {
	this->player->render(this->window);
}
void Game::render() {
	this->window.clear();
	this->window.draw(this->sprite);
	int i = 0;
	for (int mapX = 0; mapX < 26; mapX++)
	{
		for (int mapY = 0; mapY < 14; mapY++)
		{

			if (map[mapY][mapX] == 1)
			{
				wall.setPosition(4384 + mapX * 66, 1940 +mapY * 63);
				window.draw(wall);
			}
			if (map[mapY][mapX] == 0) {
				space.setPosition(4384 + mapX * 66, 1940 + mapY * 63);
				window.draw(space);
			}
			if (map[mapY][mapX] == 2) {
				spikes.setPosition(4384 + mapX * 66, 1940 + mapY * 63);
				window.draw(spikes);
			}
		}
	}
	this->renderPlayer();
	this->myView.setCenter(this->player->getPosition());
	this->window.setView(myView);
	this->window.display();
}
const sf::RenderWindow & Game::getWindow() const{
	return this->window;
}