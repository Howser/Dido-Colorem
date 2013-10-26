#include <SFML\Window.hpp>
#include <iostream>
#include "Game.h"

int main(){
	
	dido::Game game(640, 480, "Dido Colorem");
	game.Run();

}