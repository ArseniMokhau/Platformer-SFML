#include "Precomp.h"
#include "Tilemap.h"

Tilemap::Tilemap() {
	
}

Tilemap::~Tilemap() {

}

void Tilemap::initTiles() {
	this->Colour.Green;
}

void Tilemap::draw(sf::RenderTarget& target, sf::RenderStates states)const {
	sf::Vertex line[2];
	line[0] = sf::Vertex(this->Point1, this->Colour);
	line[1] = sf::Vertex(this->Point2, this->Colour);
	target.draw(line, 2, sf::Lines, states);
}

void Tilemap::update(){

}

void Tilemap::render(){
	
}
