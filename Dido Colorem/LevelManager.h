#pragma once
#include "Map.h"
namespace dido{
	class LevelManager
	{
	public:
		enum Color{
			Normal,
			Red,
			Yellow,
			Green,
			Blue,
			Purple,
			RAINBOW,
		};
		LevelManager(Map* map);
		LevelManager(void);
		~LevelManager(void);
		void NextLevel();
		void LoadMap(Map* map);
		Color currentColor;
	private:
		Map* map;
	};
}