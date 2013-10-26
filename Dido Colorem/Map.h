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

		void Load(std::string path);

		void Render(sf::RenderWindow* window);

		sf::Rect<float> CheckCollision(sf::Rect<float> const& collisionMask);

	private:
		std::vector<std::vector<Tile*> > solidLayer;
		std::vector<std::vector<Tile*> > foregroundLayer;
		sf::Texture tilesheet;

		int width, height;

	private:
		void SetSize(int w, int h);
	};
}