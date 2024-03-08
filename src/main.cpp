#include "main.h"

int main() {
    
	Game *game = new Game();
    game->loop();
    delete game;
	return 0;
}
END_OF_MAIN()

