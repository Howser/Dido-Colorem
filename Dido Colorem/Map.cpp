#include "Map.h"

namespace dido{

	Map::Map()
		: width(0), height(0), tilesheet(), solidLayer()
	{}

	Map::Map(int const& w, int const& h)
		: width(w), height(h), tilesheet(), solidLayer()
	{}

	Map::~Map(){}

	void Map::InitMap(){ // TEMP

		solidLayer.resize(width);

		for (int x = 0; x < width; x++){
			solidLayer.at(x).resize(height, 0);
			for (int y = 0; y < height; y++){
				if (x == 0 || y == 0 || x == width-1 || y == height-1 ){
					Tile* t = new Tile();
					t->texX = 0;
					t->texY = 0;

					solidLayer[x][y] = t;
				} else {
					Tile* t = new Tile();
					t->texX = 16;
					t->texY = 0;

					solidLayer[x][y] = t;
				}
			}
		}

	}

	void Map::Render(sf::RenderWindow* window){

		for (int x = 0; x < width; x++){
			for (int y = 0; y < height; y++){
				if (solidLayer[x][y]!= NULL){
					sf::Sprite s(tilesheet, sf::IntRect(solidLayer[x][y]->texX, solidLayer[x][y]->texY, 16, 16));
					s.setPosition(x*16, y*16);
					window->draw(s);
				}
			}
		}

	}

	void Map::SetTexture(sf::Texture tilesheet){
		this->tilesheet = tilesheet;
	}
}