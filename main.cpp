#include "header.hpp"
#include "Game.hpp"
#include "GameObject.hpp"
#include "Projectile.hpp" 
// directions for sprite
enum directions {down,left,right,up};
int main()
{
	Game game = Game();
	game.runGame();

	return 0;
}