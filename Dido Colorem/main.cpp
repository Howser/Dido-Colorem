#include <SFML\Window.hpp>
#include <iostream>

int main(){
	sf::Window w(sf::VideoMode(640, 480), "Dido Colorem", sf::Style::Close);

	w.display();

	sf::Event e;

	while(w.isOpen()){
		while (w.pollEvent(e)){
			if (e.type == sf::Event::Closed)
				w.close();
		}
	}
	std::cout << "BYEBTYE" << std::endl;
}