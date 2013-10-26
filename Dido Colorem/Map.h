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

		void SetTexture(sf::Texture tilesheet, sf::Texture background);

		void Load(std::string path);

		void Render(sf::RenderWindow* window);
		void RenderBackground(sf::RenderWindow* window, sf::Sprite* sprite);
		void Update(sf::Vector2f deltaCameraMovement, sf::RenderWindow* window);

		sf::Rect<float> CheckCollision(sf::Rect<float> const& collisionMask);

	private:
		std::vector<std::vector<Tile*> > solidLayer;
		std::vector<std::vector<Tile*> > foregroundLayer;

		sf::Texture backgroundImage;
		sf::Vector2f imgPosOne;
		sf::Vector2f imgPosTwo;

		sf::Texture tilesheet;

		int width, height;

	private:
		void SetSize(int w, int h);
	};
}