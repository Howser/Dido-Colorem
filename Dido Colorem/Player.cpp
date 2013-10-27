#include "Player.h"

#include <iostream>

namespace dido{

	Player::Player(){}

	Player::Player(float x, float y, Map* map)
		: playerSprite(), map(map), velocity()  {
			playerSprite.setPosition(x, y);
			gravity = 0.4f;
			moveAcceleration = 2.2f;
			maxXVelocity = 5;
			maxYVelocity = 12;
			jumpPower = 10;
	}

	Player::~Player(){}

	void Player::Update(){

		if (sf::Joystick::isConnected(0)){
			// Joystick stuff

			velocity.x += moveAcceleration*sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X)/100;
			if (sf::Joystick::isButtonPressed(0, 0) && canJump)
				Jump();

		} else {
			// Do it the old fashioned way
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				velocity.x -= moveAcceleration;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				velocity.x += moveAcceleration;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canJump)
				Jump();
		}

		// Simulate friction
		sf::Vector2f fric = -velocity * 0.5f;  
		fric.y = 0;

		ApplyForce(fric);

		// Gravity
		if (!canJump)
			velocity.y += gravity;

		// Cap speeds
		if (velocity.x > maxXVelocity)
			velocity.x = maxXVelocity;
		if (velocity.y > maxYVelocity)
			velocity.y = maxYVelocity;

		playerSprite.move(velocity);

		// Collision detection
		ProcessCollisionsVertical(true);
		ProcessCollisionsVertical(false);

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

	void Player::ApplyForce(sf::Vector2f force){
		velocity += force;
	}

	void Player::Jump(){
		velocity.y -= jumpPower;
		canJump = false;
	}

	void Player::ProcessCollisionsVertical(bool bottom){
		int dir = -32;

		if (bottom)
			dir = 31;

		if (map->CheckCollision(playerSprite.getPosition().x, playerSprite.getPosition().y+dir)){
			playerSprite.setPosition(playerSprite.getPosition().x, (map->Snap(playerSprite.getPosition().y+dir))-32);
			velocity.y = 0;
			if (bottom)
				canJump = true;

		} else if (map->CheckCollision(playerSprite.getPosition().x+32, playerSprite.getPosition().y+dir)){
			playerSprite.setPosition(playerSprite.getPosition().x, (map->Snap(playerSprite.getPosition().y+dir))-32);
			velocity.y = 0;
			if (bottom)
				canJump = true;

		} else if (map->CheckCollision(playerSprite.getPosition().x+16, playerSprite.getPosition().y+dir)){
			playerSprite.setPosition(playerSprite.getPosition().x, (map->Snap(playerSprite.getPosition().y+dir))-32);
			velocity.y = 0;// negate gravity, otherwise it keeps building making the player move at max speed when walking over the edge of a tile
			if (bottom)
				canJump = true;
		} else if (bottom) {
			canJump = false;
		}
	}
}