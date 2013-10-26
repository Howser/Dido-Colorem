#pragma once

#include <SFML\Graphics.hpp>
#include <string>

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

	private:
		sf::RenderWindow window;
		bool running;
	};
}