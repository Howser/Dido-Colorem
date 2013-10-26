#include "Game.h"
#include <iostream>

namespace dido{
	Game::Game(){
	
	}

	Game::Game(int const& w, int const& h, std::string const& title)
		: window(sf::VideoMode(w, h), title, sf::Style::Close), map(100, 100){
			window.display();
	}

	Game::~Game(){
		window.close();
	}

	void Game::Run(){

		LoadRecources();

		sf::Clock gameClock;
		
		int previous = gameClock.getElapsedTime().asMilliseconds();
		float lag = 0;

		int updates = 0;
		int frames = 0;

		float fpsPrint = gameClock.getElapsedTime().asSeconds();

		running = true;
		while (running){

			int current = gameClock.getElapsedTime().asMilliseconds();
			lag += current - previous;
			previous = current;
			while (lag >= DEFAULT_MS_PER_UPDATE)
			{
				Update();
				updates++;
				lag -= DEFAULT_MS_PER_UPDATE;
			}

			Render();
			frames++;
			
			if (gameClock.getElapsedTime().asSeconds() - fpsPrint >= 1){
				std::cout << "Updates: " << updates << ". Frames: " << frames << std::endl;
				frames = 0;
				updates = 0;
				fpsPrint = gameClock.getElapsedTime().asSeconds();
			}
		}
	}

	void Game::Update(){
		
		// Process window events n stuff
		sf::Event e;
		while (window.pollEvent(e)){
			if (e.type == sf::Event::Closed){
				running = false;
			}
		}
	}

	void Game::Render(){
		window.clear(sf::Color::Magenta);

		// Render stuff in here
		map.Render(&window);
		window.display();
	}

	void Game::LoadRecources(){
		sf::Texture tileset;
		tileset.loadFromFile("Content/raw.png");
		map.SetTexture(tileset);
		map.InitMap();
	}
}