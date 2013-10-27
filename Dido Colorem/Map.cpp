#include <iostream>

#include "Map.h"


namespace dido{

	Map::Map()
		: width(0), height(0), tilesheet(), solidLayer(), foregroundLayer() 
	{}

	Map::Map(int const& w, int const& h)
		: width(w), height(h), tilesheet(), solidLayer(), foregroundLayer(), backgroundImage()
	{}

	Map::~Map(){}

	void Map::Load(std::string path){
		sf::Image mapdata; 
		mapdata.loadFromFile(path);

		SetSize(mapdata.getSize().x, mapdata.getSize().y);

		// Auto tiling n stuff, each tile is asinged an ID depending on the surrounding tiles
		for (int x = 0; x < width; x++){
			for (int y = 0; y < height; y++){

				sf::Color tile = mapdata.getPixel(x, y);
				if (tile == sf::Color::Black){
					int id = 0;

					// check left and right tiles
					if (x > 0){
						if (mapdata.getPixel(x-1, y) == sf::Color::Black)
							id += 8;
					}
					if (x < width-1){
						if (mapdata.getPixel(x+1, y) == sf::Color::Black){
							id += 2;
						}
					}

					// check up and down tiles
					if (y > 0){
						if (mapdata.getPixel(x, y-1) == sf::Color::Black)
							id += 1;
					}
					if (y < height -1){
						if (mapdata.getPixel(x, y+1) == sf::Color::Black)
							id += 4;
					}

					Tile* t = new Tile();
					t->texX = (id%4)*16;
					t->texY = (id/4)*16;

					solidLayer[x][y] = t;
				}
			}
		}
	}

	void Map::Update(sf::Vector2f deltaCameraMovement, sf::RenderWindow* window){
		#pragma region Scroll
		imgPosOne.x += deltaCameraMovement.x/2;
		if (window->mapCoordsToPixel(imgPosOne).x >= -5){
			imgPosTwo.x = imgPosOne.x - backgroundImage.getSize().x;
		} else {
			imgPosTwo.x = imgPosOne.x + backgroundImage.getSize().x;
		}
		if (window->mapCoordsToPixel(imgPosTwo).x >= 0){
			imgPosOne.x = imgPosTwo.x - backgroundImage.getSize().x;
		} else {
			imgPosOne.x = imgPosTwo.x + backgroundImage.getSize().x;
		}
		#pragma endregion
	}

	void Map::RenderBackground(sf::RenderWindow* window, sf::Sprite* sprite){
		sprite->setPosition(imgPosOne);
		window->draw(*sprite);
		sprite->setPosition(imgPosTwo);
		window->draw(*sprite);
	}

	void Map::Render(sf::RenderWindow* window){

		sf::Sprite backgroundSprite(backgroundImage);
		RenderBackground(window, &backgroundSprite);
		
		for (int x = 0; x < width; x++){
			for (int y = 0; y < height; y++){
				if (solidLayer[x][y]!= NULL){
					sf::Sprite s(tilesheet, sf::IntRect(solidLayer[x][y]->texX, solidLayer[x][y]->texY, 16, 16));
					s.setPosition(x*16, y*16);
					window->draw(s);
				}
				if (foregroundLayer[x][y] != NULL){
					sf::Sprite s(tilesheet, sf::IntRect(foregroundLayer[x][y]->texX, foregroundLayer[x][y]->texY, 16, 16));
					s.setPosition(x*16, y*16);
					window->draw(s);
				}
			}
		}
	}
	 
	void Map::SetTexture(sf::Texture tilesheet, sf::Texture background){
		this->tilesheet = tilesheet;
		this->backgroundImage = background;

		imgPosOne.x = 0;
		imgPosOne.y = 0;
		imgPosTwo.x = 0;
		imgPosTwo.y = 0;
	}

	bool Map::CheckCollision(float xx, float yy){
		
		int x = xx/16;
		int y = yy/16;

		if (x < 0 || x > width-1 || y < 0 || y  > height-1)
			return false;

		if (solidLayer[x][y] != NULL)
			return true;
		return false;
	}

	int Map::Snap(float nr){
		return ((int)nr/16)*16;
	}

	void Map::SetSize(int w, int h){
		width = w;
		height = h;
		solidLayer.resize(width);
		foregroundLayer.resize(width);

		for (int x = 0; x < width; x++){

			solidLayer.at(x).resize(height, 0);
			foregroundLayer.at(x).resize(height, 0);
		}
	}
}