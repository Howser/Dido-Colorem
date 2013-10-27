#include "Game.h"
#include <iostream>

namespace dido{
	Game::Game(){
		
	}

	Game::Game(int const& w, int const& h, std::string const& title)
		: window(sf::VideoMode(w, h), title, sf::Style::Close), map(100, 100), player(100, 120, &map){
			window.setVerticalSyncEnabled(true);

			window.display();

			cam.reset(sf::FloatRect(0, 0, 640/2, 480/2));
			cam.setViewport(sf::Rect<float>(0,0, 1, 1));
			window.setView(cam);
	}

	Game::~Game(){
		window.close();
	}

	void Game::Run(){

		if (sf::Joystick::isConnected(0))
			std::cout << "Controller Detected." << std::endl;

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

		previousCamPos = cam.getCenter();
		player.Update();
		cam.setCenter(player.GetPosition());
		map.Update(cam.getCenter() - previousCamPos, &window);
	}

	void Game::Render(){
		window.clear(sf::Color::Magenta);

		window.setView(cam);
		// Render stuff in here
		map.Render(&window);
		player.Render(&window);
		window.display();	
	}

	void Game::LoadRecources(){
		sf::Texture tileset, background, playerTexture;
		tileset.loadFromFile("Content/tilesets/green.png");
		background.loadFromFile("Content/background.png");
		map.SetTexture(tileset, background);
		map.Load("Content/testmap2.png");
		playerTexture.loadFromFile("Content/dido.png", sf::IntRect(0, 0, 16, 16));
		
		player.SetTexture(playerTexture);
	}
}