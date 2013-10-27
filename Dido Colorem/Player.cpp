#include "Player.h"

#include <iostream>

namespace dido{

	Player::Player(){}

	Player::Player(float x, float y, Map* map)
		: playerSprite(), map(map) {
			playerSprite.setPosition(x, y);
			gravity = 0.4f;
			moveSpeed = 5;
			maxYVelocity = 12;
			jumpPower = 10;
			canJump = false;
			ySpeed = 0;
	}

	Player::~Player(){}

	void Player::Update(){

		if (sf::Joystick::isConnected(0)){
			// Joystick stuff

			float px = playerSprite.getPosition().x;
			float py = playerSprite.getPosition().y;
			
			float c = 0;
			
			float moveAmount = sf::Joystick::getAxisPosition(0, sf::Joystick::X)*moveSpeed/100;

			if (moveAmount > 0)
				c = 16;

			if (map->CheckCollision(px + moveAmount + c, py) || map->CheckCollision(px + moveAmount + c, py + 15)){
				if (moveAmount > 0)
					moveAmount = map->Snap(px+moveAmount + c) - px - c - 1;
				else 
					moveAmount = map->Snap(px+moveAmount + c) - px + 16;
			}

			playerSprite.move(moveAmount, 0);

			if (sf::Joystick::isButtonPressed(0, 0) && canJump)
				Jump();

		} else {
			float px = playerSprite.getPosition().x;
			float py = playerSprite.getPosition().y;
			
			float c = 0;
			// Do it the old fashioned way
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){

				float moveAmount = -moveSpeed;
				if (map->CheckCollision(px + moveAmount, py) || map->CheckCollision(px + moveAmount, py + 15))
					moveAmount = map->Snap(px + moveAmount) - px + 16;
				playerSprite.move(moveAmount, 0);

			} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){

				float moveAmount = moveSpeed;
				if (map->CheckCollision(px + moveAmount + 16, py) || map->CheckCollision(px + moveAmount + 16, py + 15))
					moveAmount = map->Snap(px + moveAmount + 16) - px - 17;
				playerSprite.move(moveAmount, 0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
				Jump();
		}

		if (!canJump){
			float px = playerSprite.getPosition().x;
			float py = playerSprite.getPosition().y;

			ySpeed += gravity;
			if (ySpeed > maxYVelocity)
				ySpeed = maxYVelocity;

			float moveAmount = ySpeed;

			if (ySpeed > 0){
				if (map->CheckCollision(px, py + ySpeed + 16) || map->CheckCollision(px + 16, py + ySpeed + 16)){
					moveAmount = map->Snap(py + moveAmount + 16) - py - 16;
					ySpeed = 0;
					canJump = true;
				}
			} else {
				if (map->CheckCollision(px, py + ySpeed) || map->CheckCollision(px + 16, py + ySpeed)){
					moveAmount = map->Snap(py + moveAmount) - py + 16;
					ySpeed = 0;
				}
			}
			playerSprite.move(0, moveAmount);

		} else {
			float px = playerSprite.getPosition().x;
			float py = playerSprite.getPosition().y;

			if (!map->CheckCollision(px, py + 16) || !map->CheckCollision(px+16, py+ 16)){
				canJump = false;
			}
		}
	}

	void Player::Render(sf::RenderWindow* window){
		window->draw(playerSprite);
	}

	void Player::SetTexture(sf::Texture tex){
		playerTexture = tex;
		playerSprite.setTexture(playerTexture);
	}

	sf::Vector2f Player::GetPosition(){
		return playerSprite.getPosition();
	}


	void Player::Jump(){
		ySpeed = -jumpPower;
		canJump = false;
	}
}