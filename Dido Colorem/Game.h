#pragma once

#include <SFML\Graphics.hpp>
#include <string>

#include "Map.h"

#define DEFAULT_MS_PER_UPDATE 1000.0f/60.0f

namespace dido{

	class Game{

	public:
		
		Game();
		Game(int const& w, int const& h, std::string const& title);
		~Game();

		void Run();
		void Update();
		void Render();

		void LoadRecources();

	private:
		sf::RenderWindow window;
		bool running;
		Map map;
		sf::View cam;
		sf::Vector2f previousCamPos;
	};
}