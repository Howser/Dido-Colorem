#include "LevelManager.h"
#include "Game.h"

namespace dido{

	LevelManager::LevelManager(Map* map){
		LevelManager::map = map;
	}

	LevelManager::LevelManager(void)
	{

	}

	LevelManager::~LevelManager(void)
	{
		delete map;
	}

	void LevelManager::LoadMap(Map* map){
		sf::Texture tileSheet, background;
		delete map;
		switch (currentColor)
		{
		case LevelManager::Color::Normal:
			tileSheet.loadFromFile("Content/tilesets/backgrounds/normal.png");
			background.loadFromFile("Content/tilesets/normal.png");
			break;
		case LevelManager::Color::Red:
			tileSheet.loadFromFile("Content/tilesets/backgrounds/red.png");
			background.loadFromFile("Content/tilesets/red.png");
			break;
		case LevelManager::Color::Yellow:
			tileSheet.loadFromFile("Content/tilesets/backgrounds/yellow.png");
			background.loadFromFile("Content/tilesets/yellow.png");
			break;
		case LevelManager::Color::Green:
			tileSheet.loadFromFile("Content/tilesets/backgrounds/green.png");
			background.loadFromFile("Content/tilesets/green.png");
			break;
		case LevelManager::Color::Blue:
			tileSheet.loadFromFile("Content/tilesets/backgrounds/blue.png");
			background.loadFromFile("Content/tilesets/blue.png");
			break;
		case LevelManager::Color::Purple:
			tileSheet.loadFromFile("Content/tilesets/backgrounds/purple.png");
			background.loadFromFile("Content/tilesets/purple.png");
			break;
		default:
			break;
		}
		map->Load("Content/testmap2.png");
	}

	void LevelManager::NextLevel(){
		switch (currentColor)
		{
		case Normal:
			currentColor = Color::Red;
			break;
		case Red:
			currentColor = Color::Yellow;
			break;
		case Yellow:
			currentColor = Color::Green;
			break;
		case Green:
			currentColor = Color::Blue;
			break;
		case Blue:
			currentColor = Color::Purple;
			break;
		case Purple:
			currentColor = Color::RAINBOW;
			break;
		default:
			break;
		}
		LoadMap(map);
	}
}