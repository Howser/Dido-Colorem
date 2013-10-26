#pragma once

#include <SFML\Graphics.hpp>
#include <vector>


namespace dido{

	struct Tile{

		int texX;
		int texY;
	};

	class Map{

	public:
		Map();
		Map(int const& w, int const& h);
		
		~Map();

		void SetTexture(sf::Texture tilesheet);
		void InitMap(); // Temp func just to get something on the screen

		void Render(sf::RenderWindow* window);

	private:
		std::vector<std::vector<Tile*> > solidLayer;
		std::vector<std::vector<Tile*> > foregroundLayer;
		sf::Texture tilesheet;

		int width, height;
	};
}