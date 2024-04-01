#include "Precomp.h"
#include "Game.h"

Object web(sf::Vector2f(1500.0f, 1340.0f), sf::Vector2f(100.f, 110.f), "web");
Object lever(sf::Vector2f(3600.f, 895.0f), sf::Vector2f(32.f, 100.f), "lever");

void Game::initWindow() {
	this->window.create(sf::VideoMode(1280, 720), "Fort Knight", sf::Style::Titlebar | sf::Style::Close);
	if (!this->texture.loadFromFile("Map/castle.png")) {
		std::cout << "Could not load background picture" << "\n";
	}
	if (!this->font.loadFromFile("Fonts/LongaIberica-DEMO.ttf")) {
		std::cout << "Could not load font" << "\n";
	}
	this->sprite.setTexture(texture);
	this->sprite.setScale(7.f, 7.f);
	this->myView.setSize(1280, 720);
	this->window.setFramerateLimit(60);
	this->shader.loadFromFile("blur.frag", sf::Shader::Fragment);
	leverIsSet = false;
	endIsReached = false;
	gameHasBegun = false;
	foward = true;
	this->fade.setPosition(sf::Vector2f(0.f, 0.f));
	this->fade.setSize(sf::Vector2f(10000.f, 10000.f));
	this->fade.setFillColor(sf::Color(0, 0, 0, multi));
	this->textEnd.setCharacterSize(200.f);
	this->textEnd.setFillColor(sf::Color::Red);
	this->textEnd.setFont(font);
	this->textEnd.setString("THE  END");
	this->textEnd.setPosition(sf::Vector2f(3500.f, 580.0f));
	this->textPressESC.setCharacterSize(60.f);
	this->textPressESC.setFillColor(sf::Color::White);
	this->textPressESC.setFont(font);
	this->textPressESC.setString("PRESS  *ESC*  TO EXIT");
	this->textPressESC.setPosition(sf::Vector2f(3585.f, 950.0f));
	this->textStart.setCharacterSize(200.f);
	this->textStart.setFillColor(sf::Color::Red);
	this->textStart.setFont(font);
	/*this->textStart.setString("ELEDN RING 2077");*/
	this->textStart.setString("FORT   KNIGHT");
	this->textStart.setPosition(sf::Vector2f(590.f, 990.f));
	this->textPressSpace.setCharacterSize(60.f);
	this->textPressSpace.setFillColor(sf::Color::White);
	this->textPressSpace.setFont(font);
	this->textPressSpace.setString("PRESS  *SPACE*  TO START");
	this->textPressSpace.setPosition(sf::Vector2f(780.f, 1500.f));
	this->textD.setCharacterSize(120.f);
	this->textD.setFillColor(sf::Color(255, 255, 255, i));
	this->textD.setFont(font);
	this->textD.setString("D");
	this->textD.setPosition(sf::Vector2f(3685.f, 780.0f));
	this->textD.setOutlineThickness(0.5f);
	this->textD.setOutlineColor(sf::Color::Black);
}

void Game::setUpTiles() {

}

void Game::initPlayer() {
	this->player = new Player();
}

void Game::initEntities() {
	this->slime = new Slime();
	this->suriken = new Suriken();
}

void Game::initTiles() {
	
}

Game::Game() {
	this->initWindow();
	this->initPlayer();
	this->initEntities();
	this->player->setPosition(980.f, 1390.f);
	/*this->player->setPosition(3550.f, 895.0f);*/
	this->slime->setPosition(2700.f, 1390.f);
	this->suriken->setPosition(2750.f, 1200.f);
}

Game::~Game() {
	delete this->player;
	delete this->slime;
	delete this->suriken;
}

void Game::updatePlayer() {
	this->player->update();
}

void Game::updateEntities() {
	this->slime->update();
	this->suriken->update();
}

void Game::updateCollision() {
	if (this->player->getPosition().x >= 3760 && this->player->getPosition().y < 958.f) {
		endIsReached = true;
		leverIsSet = true;
	}
	if (lever.GetCollision().checkCollision(this->player->GetCollisionModel(), 1.f, leverIsSet) && !leverIsSet) {
			this->player->resetVelocityX();
			this->player->resetVelocityY();
	}
	//spider web
	if (web.GetCollision().checkCollision(this->player->GetCollisionModel(), 0.0f, leverIsSet)) {
		this->player->resetVelocityX();
		this->player->resetVelocityY();
	}
	if (this->slime->GetCollision().checkCollision(this->player->GetCollisionHitbox(), 0.0f, leverIsSet)) {
		this->player->setPosition(980.f, 1390.f);
	}
	if (this->suriken->GetCollision().checkCollision(this->player->GetCollisionHitbox(), 0.0f, leverIsSet)) {
		this->player->setPosition(980.f, 1390.f);
	}

	//World walls//
	if (this->player->getPosition().y > 1390.f) {
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x, 1390.f);
	}
	if (this->player->getPosition().y < 0.f) {
		this->player->resetVelocityX();
		this->player->setPosition(this->player->getPosition().x, 0.f);
	}
	if (this->player->getPosition().x > 4800.f) {
		this->player->resetVelocityX();
		this->player->setPosition(4800.f, this->player->getPosition().y);
	}
	if (this->player->getPosition().x < 805.f) {
		this->player->resetVelocityX();
		this->player->setPosition(805.f, this->player->getPosition().y);
	}
	//b1
	if (this->player->getPosition().x > 1210.f && this->player->getPosition().x < 1230.f && this->player->getPosition().y < 1300.f) {
		this->player->resetVelocityX();
		this->player->setPosition(1210.f, this->player->getPosition().y);
	}
	if (this->player->getPosition().x > 1220.f && this->player->getPosition().x < 1800.f && this->player->getPosition().y < 1340.f && this->player->getPosition().y > 1300.f) {
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x, 1340.f);
	}
	if (this->player->getPosition().x > 1220.f && this->player->getPosition().x - 20.f < 1800.f && this->player->getPosition().y < 1300.f) {
		this->player->resetVelocityX();
		this->player->setPosition(1820.f, this->player->getPosition().y);
	}
	//b2
	if (this->player->getPosition().x > 2335.f && this->player->getPosition().x < 2345.f && this->player->getPosition().y < 1300.f && this->player->getPosition().y > 1165.f) {
		this->player->resetVelocityX();
		this->player->setPosition(2335.f, this->player->getPosition().y);
	}
	if (this->player->getPosition().x > 2340.f && this->player->getPosition().x < 2690.f && this->player->getPosition().y < 1340.f && this->player->getPosition().y > 1300.f) {
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x, 1340.f);
	}
	if (this->player->getPosition().x > 2340.f && this->player->getPosition().x < 2700.f && this->player->getPosition().y +10.f > 1165.f && this->player->getPosition().y < 1180.f) {
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x, 1165.f);
	}
	if (this->player->getPosition().x > 2670.f && this->player->getPosition().x - 20.f < 2700.f && this->player->getPosition().y < 1300.f && this->player->getPosition().y > 1185.f) {
		this->player->resetVelocityX();
		this->player->setPosition(2720.f, this->player->getPosition().y);
	}
	//b3.1
	if (this->player->getPosition().x > 2895.f && this->player->getPosition().x < 2905.f && this->player->getPosition().y < 1180.f && this->player->getPosition().y > 1056.f) {
		this->player->resetVelocityX();
		this->player->setPosition(2895.f, this->player->getPosition().y);
	}
	if (this->player->getPosition().x > 2895.f && this->player->getPosition().x < 3250.f && this->player->getPosition().y + 10.f > 1056.f && this->player->getPosition().y < 1070.f) {
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x, 1056.f);
	}
	if (this->player->getPosition().x > 2900.f && this->player->getPosition().x < 3150.f && this->player->getPosition().y < 1220.f && this->player->getPosition().y > 1180.f) {
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x, 1220.f);
	}
	//b3.2
	if (this->player->getPosition().x > 3120.f && this->player->getPosition().x < 3130.f && this->player->getPosition().y > 1070.f) {
		this->player->resetVelocityX();
		this->player->setPosition(3120.f, this->player->getPosition().y);
	}
	if (this->player->getPosition().x > 3250.f && this->player->getPosition().x < 3265.f && this->player->getPosition().y > 1090.f) {
		this->player->resetVelocityX();
		this->player->setPosition(3265.f, this->player->getPosition().y);
	}
	//b4
	if (this->player->getPosition().x > 3440.f && this->player->getPosition().x < 3455.f && this->player->getPosition().y < 1070.f && this->player->getPosition().y > 943.f) {
		this->player->resetVelocityX();
		this->player->setPosition(3440.f, this->player->getPosition().y);
	}
	if (this->player->getPosition().x > 3440.f && this->player->getPosition().x < 5000.f && this->player->getPosition().y + 10.f > 943.f && this->player->getPosition().y < 958.f) {
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x, 943.f);
	}
	if (this->player->getPosition().x > 3445.f && this->player->getPosition().x < 5000.f && this->player->getPosition().y < 1120.f && this->player->getPosition().y > 1080.f) {
		this->player->resetVelocityY();
		this->player->setPosition(this->player->getPosition().x, 1120.f);
	}
	if (this->player->getPosition().x > 3890.f && this->player->getPosition().x < 3900.f && this->player->getPosition().y > 1090.f) {
		this->player->resetVelocityX();
		this->player->setPosition(3890.f, this->player->getPosition().y);
	}
	//Spikes
	if (this->player->getPosition().x > 3255.f && this->player->getPosition().x < 5000.f && this->player->getPosition().y > 1300) {
		this->player->resetVelocityX();
		this->player->setPosition(980.f, 1390.f);
	}
}

void Game::updateEntityCollision() {
	if (this->slime->getPosition().y > 1390.f) {
		this->slime->resetVelocityY();
		this->slime->setPosition(this->slime->getPosition().x, 1390.f);
	}
	if (this->slime->getPosition().x > 4800.f) {
		this->slime->resetVelocityX();
		this->slime->setPosition(4800.f, this->slime->getPosition().y);
	}
	if (this->slime->getPosition().x < 805.f) {
		this->slime->resetVelocityX();
		this->slime->setPosition(805.f, this->slime->getPosition().y);
	}
}

void Game::update() {
	while (this->window.pollEvent(this->event)) {
		if (gameHasBegun) {
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
		else {
			if (this->event.type == sf::Event::Closed) {
				this->window.close();
			}
			if (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Keyboard::Escape) {
				this->window.close();
			}
			if (this->event.type == sf::Event::KeyPressed && this->event.key.code == sf::Keyboard::Keyboard::Space) {
				this->gameHasBegun=true;
				this->player->gameHasBegun = true;
			}
		}
	}
	this->updatePlayer();
	this->updateEntities();
	this->updateCollision();
	this->updateEntityCollision();
}

void Game::renderPlayer() {
	this->player->render(this->window);
}

void Game::renderEntities() {
	this->slime->render(this->window);
	this->suriken->render(this->window);
}

void Game::renderTiles() {
	web.render(this->window);
	lever.render(this->window);
}

void Game::render() {
	this->window.clear();
	this->window.draw(this->sprite);
	this->renderPlayer();
	this->renderEntities();
	this->renderTiles();
	this->window.draw(this->fade);
	if (gameHasBegun) {
		if (!endIsReached) {
			while (multi > 30) {
				multi -= 1;
			}
			this->fade.setFillColor(sf::Color(0, 0, 0, multi));
			if (i == 255) {
				foward = false;
			}
			if (i == 0) {
				foward = true;
			}
			if (foward) {
				i+=3;
			}
			else {
				i-=3;
			}
			this->textD.setFillColor(sf::Color(255, 255, 255, i));
			this->window.draw(this->textD);
			this->renderTiles();
			this->myView.setCenter(this->player->getPosition().x, this->player->getPosition().y - 100.f);
		}
		else {
			this->player->endIsReached = true;
			this->player->movement(0.5, 0);
			this->fade.setFillColor(sf::Color(0, 0, 0, multi));
			if (multi < 245) {
				multi += 1;
			}
			this->window.draw(this->textEnd);
			this->window.draw(this->textPressESC);
		}
	}
	else {
		this->myView.setCenter(this->player->getPosition().x, this->player->getPosition().y - 100.f);
		this->renderPlayer();
		this->window.draw(this->textStart);
		this->window.draw(this->textPressSpace);
	}
	this->window.setView(myView);
	this->window.display();
}
const sf::RenderWindow& Game::getWindow() const {
	return this->window;
}