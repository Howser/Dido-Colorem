#pragma once

#include <SFML\Graphics.hpp>

#include "Map.h"

#define NO_COLLISION sf::Rect<float>(-1, -1, 16, 16)

namespace dido{

	class Player{
	
	public:

		Player();
		Player(float x, float y, Map* map);
		~Player();

		void Update();
		void Render(sf::RenderWindow* window);

		void SetTexture(sf::Texture tex);
		sf::Vector2f GetPosition();

	private:
		sf::Sprite playerSprite;
		sf::Texture playerTexture; // this is retart i know

		float gravity; 
		float moveSpeed;
		float ySpeed;
		float maxYVelocity;
		float jumpPower;
		bool canJump;

		void ProcessCollisionsVertical(bool bottom);
		void ProcessCollisionsHorizontal(bool right);

		Map* map;

	private:
		void Jump();
	};
}