#include "Precomp.h"
#include "Game.h"

int main() {
	srand(static_cast<unsigned>(time(0)));
	Game platformer;
	while (platformer.getWindow().isOpen()) {
		platformer.update();
		platformer.render();
	}
	return 0;
}