#include "Precomp.h"
#include "EscapeMenu.h"
EscapeMenu::EscapeMenu(float width, float hight) {
	if (!font.loadFromFile("Fonts/RINGM___.TTF")) {
		cout << "No fonts to load";
	}

	//Continue
	escMenu[0].setFont(font);
	escMenu[0].setFillColor(Color::Black);
	escMenu[0].setString("Continue");
	escMenu[0].setCharacterSize(60);
	escMenu[0].setPosition(400,200);

	//Restart
	escMenu[1].setFont(font);
	escMenu[1].setFillColor(Color::Black);
	escMenu[1].setString("Restart");
	escMenu[1].setCharacterSize(60);
	escMenu[1].setPosition(400, 300);

	//Exit
	escMenu[1].setFont(font);
	escMenu[1].setFillColor(Color::Black);
	escMenu[1].setString("Exit");
	escMenu[1].setCharacterSize(60);
	escMenu[1].setPosition(400, 400);

	EscSelected = -1;
}
EscapeMenu::~EscapeMenu() {
}

//Draw

void EscapeMenu::draw(RenderWindow& window) {
	for (int i = 0; i < 3; ++i) {
		window.draw(escMenu[i]);
	}
}

//UP
void EscapeMenu::MoveUp() {
	if (EscSelected - 1 >= 0) {
		escMenu[EscSelected].setFillColor(Color::Black);
		EscSelected--;
		if (EscSelected == -1) {
			EscSelected = 2;
		}
		escMenu[EscSelected].setFillColor(Color::Blue);
	}
}

//DOWN
void EscapeMenu::MoveDown() {
	if (EscSelected+1 <= 3){
		escMenu[EscSelected].setFillColor(Color::Black);
		EscSelected++;
		if (EscSelected == 3) {
			EscSelected = 0;
		}
		escMenu[EscSelected].setFillColor(Color::Blue);
	}
}
