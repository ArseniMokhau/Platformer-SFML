#pragma once
#include "Precomp.h"
using namespace std;
using namespace sf;
class EscapeMenu
{
public:
	EscapeMenu(float width, float hight);
	~EscapeMenu();
	void MoveUp();
	void MoveDown();
	void draw(RenderWindow& window);
	int EscPressed() {
		return EscSelected;
	}
private:
	int EscSelected;
	Font font;
	Text escMenu[3];
};

