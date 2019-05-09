// SFML_Shooter.cpp : A basic 2D shooter 
#include "pch.h"
#include <SFML/Graphics.hpp>   //using namespace sf 
#include <time.h> 
#include <iostream>
#include <cstdbool>

//dimensions for window size and background 
int num_vertBox = 30, num_horzBox = 30;
int size = 16; //number of pixels 
int w = size * num_horzBox;  //background number of pixels in width 
int h = size * num_vertBox;    //background number of pixels in height 


//The direction of player one
int direction;    //direction the player is moving

//The direction of player two
int directionTwo; //direction the second player is moving


//The Struct of a player in the game
struct Player
{
	int x, y;        //each sprite needs an x,y coordinate 
	int alive = true;
	int dirTemp = -1;
};

//Create the two players
Player p1;
Player p2;


//This represents the bullets fired by each player
struct Bullet
{
	int x, y;            //the coordinates for the bullet 
	int direction = -1;  //the direction of the bullet
	bool fired = false;  //the bullet was fired
};

//Create two bullets
Bullet b1;
Bullet b2;


//This represents the 

//bullet collision detection
void bulletCollision() {

}

//Updates the location of player one's bullets
//Checks for collisions 
void bulletOneMove() {
	//std::cout << "Bullet X:" << b1.x << "  Bullet Y:" << b1.y << std::endl;
	//The bullet moves in the direction it was fired.
	if (b1.fired == false) {
		//do nothing
		b1.x = p1.x;
		b1.y = p1.y;
	}
	else {

		if (b1.direction == 0) {
			b1.y -= 1;
		}
		if (b1.direction == 1) {
			b1.y += 1;
		}
		if (b1.direction == 2) {
			b1.x -= 1;
		}
		if (b1.direction == 3) {
			b1.x += 1;
		}

		//Check for collision with player
		if (b1.x == p2.x && b1.y == p2.y) {
			//the player two was hit
			std::cout << "Player 2 Hit!" << std::endl;
			b1.fired = false;
			b1.x = p1.x;
			b1.y = p1.y;
			//Kill the player
			p2.alive = false;
		}

		//Check for collision with enemy bullet
		if (b1.x == b2.x &&b1.y == b2.y) {
			//the bullets collided
			b1.fired = false;
			b2.fired = false;

			b2.x = p2.x;
			b2.y = p2.y;
			b1.x = p1.x;
			b1.y = p1.y;

		}
		//check for collision with wall
		if (b1.x > num_horzBox - 1) {
			b1.fired = false;
		}

		//Left
		if (b1.x < 0) {
			b1.fired = false;
		}
	
		//Bottom
		if (b1.y > num_vertBox - 1) {
			b1.fired = false;
		}
		//Top
		if (b1.y < 0) {
			b1.fired = false;
		}

	}
}


void bulletTwoMove() {
	if (b2.fired == false) {
		//do nothing
		b2.x = p2.x;
		b2.y = p2.y;
	}
	else {

		if (b2.direction == 0) {
			b2.y -= 1;
		}
		if (b2.direction == 1) {
			b2.y += 1;
		}
		if (b2.direction == 2) {
			b2.x -= 1;
		}
		if (b2.direction == 3) {
			b2.x += 1;
		}

		//check for player collision
		if (b2.x == p1.x && b2.y == p1.y) {
			//Player one was hit
			std::cout << "Player 1 Hit!" << std::endl;
			p1.alive = false;
			b2.fired = false;
			b2.x = p2.x;
			b2.y = p2.y;


		}
		
		//check for collision with other bullet
		if (b1.x == b2.x && b1.y == b2.y) {
			//Bullets collided
			b1.fired = false;
			b2.fired = false;
			b2.x = p2.x;
			b2.y = p2.y;
			b1.x = p1.x;
			b1.y = p1.y;


		}
		//check for hitting the wall
		//check for collision with wall
		if (b2.x > num_horzBox - 1) {
			b2.fired = false;
		}

		//Left
		if (b2.x < 0) {
			b2.fired = false;
		}

		//Bottom
		if (b2.y > num_vertBox - 1) {
			b2.fired = false;
		}
		//Top
		if (b2.y < 0) {
			b2.fired = false;
		}
	}
}

void move() {
	//We want to fire the bullet if the players hit their shoot key
	if (direction == 4) {
		b1.fired = true;

	}

	if (directionTwo == 4) {
		b2.fired = true;
		
	}

	//We want to move both players up if they hit their up key
	//if player one presses up 
	if (direction == 0) {
		p1.y -= 1;
	}
	//if player two presses up 
	if (directionTwo == 0) {
		p2.y -= 1;
	}

	//We want to move both players down if they hit their down key
	//if player one presses down 
	if (direction == 1) {
		p1.y += 1;
	}

	//if player two presses down
	if (directionTwo == 1) {
		p2.y += 1;
	}

	//We want to move both players left if they hit their left key
	//if player one presses left 
	if (direction == 2) {
		p1.x -= 1;
	}
	//if player two presses left
	if (directionTwo == 2) {
		p2.x -= 1;
	}

	//We want to move both players right if they hit their right key
	//if player one presses right 
	if (direction == 3) {
		p1.x += 1;
	}
	//if player two presses right
	if (directionTwo == 3) {
		p2.x += 1;
	}

	//DO COLLISION CHECKS

	//Boundary Checking both players
	//Players can not leave the screen
	//LEFT and RIGHT 
	if (p1.x > num_horzBox-1) {
		p1.x -= 1;
	}
	if (p2.x > num_horzBox-1) {
		p2.x -= 1;
	}

	if (p1.x < 0) {
		p1.x += 1;
	}
	if (p2.x < 0) {
		p2.x += 1;
	}

	//TOP and BOTTOM 
	if (p1.y > num_vertBox-1) {
		p1.y -= 1;
	}
	if (p2.y > num_vertBox-1) {
		p2.y -= 1;
	}

	if (p1.y < 0) {
		p1.y += 1;
	}
	if (p2.y < 0) {
		p2.y += 1;
	}


	//I need to know the last looking location to determine the shooting path
	if (direction != -1) {
		if (b1.fired == false) {
			b1.direction = direction;
		}
		p1.dirTemp = direction;
	}
	else if(b1.fired==false) {
		b1.direction = p1.dirTemp;
	}

	if (directionTwo != -1) {
		if (b2.fired == false) {
			b2.direction = directionTwo;
		}
		p2.dirTemp = directionTwo;
	}
	else if(b2.fired ==false)
	{
		b2.direction = p2.dirTemp;
	}

	//I want them to only move when the key is held down so both direction are reset each time
	direction = -1;
	directionTwo = -1;

}


int main()
{
	//Setting pseudorandom time, TODO:discuss true random vs pseudorandom  
	srand(time(0));

	//Window that we can play the game in  
	sf::RenderWindow window(sf::VideoMode(w, h), "2D-Shooter");

	//Textures load an image into the GPU Memory 
	sf::Texture t1, t2, t3, t4,t5;
	t1.loadFromFile("image/white.png");
	t2.loadFromFile("image/red.png");
	t3.loadFromFile("image/green.png");
	t4.loadFromFile("image/strawberry.png");
	t5.loadFromFile("image/dead.png");


	//Sprite has physical dimmensions that can be set in  
	//coordinate system, setPosition(x,y), and drawn on screen 
	sf::Sprite sprite1(t1);
	sf::Sprite sprite2(t2);
	sf::Sprite sprite3(t3);
	sf::Sprite sprite4(t4);
	sf::Sprite sprite5(t5);
	



	sf::Clock clock;
	float timer = 0.0f, delay = 0.09f;
	float delayTwo =0.14;
	int counter = 0;
	while (window.isOpen())
	{
		//Error in class I placed this before the while loop 
		//Should be placed in while loop as shown here to update 
		//timer  

		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer += time;
		
		//Allow us to check when a user does something 
		sf::Event e;

		//Check when the window is closed 
		while (window.pollEvent(e))
		{
			//If user presses x in the top right, Windows, top left, Mac,  close the window 
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		
		if (timer > delay)
		{
			
			timer = 0; //reset timer 
			if (counter % 2== 0) {
				move();    //move the players 
			}
			counter++;
			bulletOneMove(); //move the bullet
			bulletTwoMove(); //move the bullet

		}



		//Control for Player one
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) direction = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)) direction = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)) direction = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) direction = 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) direction = 4;
		if (p1.alive == false) {
			direction = -1;
		}



		//Control for Player two
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) directionTwo = 0;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) directionTwo = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) directionTwo = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) directionTwo = 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) directionTwo = 4;
		if (p2.alive == false) {
			directionTwo = -1;
		}

		/*****************/
		//Draw in window
		/*****************/
		window.clear();    //clear the window so new frame can be drawn in 

		//NOTE: Order matters as we will draw over items listed first.  
		//Hence the background should be the first thing you will always do 
		//1st: Draw Background first 
		for (int i = 0; i < num_horzBox; i++)
		{
			for (int j = 0; j < num_vertBox; j++)
			{
				//Set position of sprite1 one at a time 
				sprite1.setPosition(i*size, j*size);

				//Draw sprite1 but, do not show it on screen.  
				window.draw(sprite1);

			}
		}
		
		//2nd: Draw in any bullets if they were fired
		sprite4.setPosition(b1.x*size, b1.y*size);
		window.draw(sprite4);

		sprite4.setPosition(b2.x*size, b2.y*size);
		window.draw(sprite4);

		//3rd: The draw the players onto the screen 

			//position sprite2 one at a time
		if (p1.alive) {
			sprite2.setPosition(p1.x*size, p1.y*size);
			window.draw(sprite2);
			}
		else {
			sprite5.setPosition(p1.x*size, p1.y*size);
			window.draw(sprite5);
		}

		if (p2.alive) {
			sprite3.setPosition(p2.x*size, p2.y*size);
			window.draw(sprite3);
		}
		else {
			sprite5.setPosition(p2.x*size, p2.y*size);
			window.draw(sprite5);

		}
		

			//Show everything we have drawn on the screen	
			window.display();
				
	}

	return 0;

}