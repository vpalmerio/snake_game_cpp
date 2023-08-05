//============================================================================
// Name        : SFML Snake Game.cpp
// Author      : Vincent
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================



#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;


//initial direction
float pos_x = 0.f;
float pos_y = 20.f;
float rotation = 180.f;
sf::CircleShape snakeHead(20.f, 3);


int amountofsquares = 0;

vector<int> vectorpos_y(amountofsquares);

vector<int> vectorpos_x(amountofsquares);


void keyPress() {
	//where everything happens
	float currentrotation = snakeHead.getRotation();


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		pos_x = 0.f;
		pos_y = -20.f;
		if (currentrotation != 0){
		rotation = 0;
		snakeHead.setRotation(rotation);
		}
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		pos_x = 0.f;
		pos_y = 20.f;
		if (currentrotation != 180) {
		rotation = 180;
		snakeHead.setRotation(rotation);
		}
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		pos_x = -20.f;
		pos_y = 0.f;
		if (currentrotation != 270) {
		rotation = 270;
		snakeHead.setRotation(rotation);
		}
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		pos_x = 20.f;
		pos_y = 0.f;
		if (currentrotation != 90) {
		rotation = 90;
		snakeHead.setRotation(rotation);
	}
	}
}
int main() {


	//settings
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	//initialize window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Game", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);


	snakeHead.setFillColor(sf::Color::Blue);
	snakeHead.setPosition(100.f, 100.f);
	snakeHead.setRotation(180.f);

	//middle of entity
	snakeHead.setOrigin(20.f,20.f);

	//create apple
	sf::RectangleShape apple(sf::Vector2f(40.f, 40.f));
	apple.setPosition(0, 0);

	//frame count
	int frameCount = 0;

	//while loops repeats every frame
	while (window.isOpen()) {
		frameCount++;
		cout << "new frame: " << frameCount << endl;
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event)){

			// "close requested" event: close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);



		//vectors

		cout << "vectorsizeX: " << vectorpos_x.size() << endl;
		cout << "vectorsizeY: " << vectorpos_y.size() << endl;
		if (frameCount == 10) {
			frameCount = 0;
			//			timepassed++;

			int vectorSizeX = vectorpos_x.size();
			int vectorSizeY = vectorpos_y.size();


			vectorpos_x.erase(vectorpos_x.begin(), end(vectorpos_x) - (amountofsquares));
			vectorpos_y.erase(vectorpos_y.begin(), end(vectorpos_y) - (amountofsquares));


			vectorpos_x.push_back(snakeHead.getPosition().x);
			vectorpos_y.push_back(snakeHead.getPosition().y);

			cout << "position added: " << vectorpos_x[vectorSizeX]<< ", " << vectorpos_y[vectorSizeY] << endl;


			//this is here to move the snakehead after the current position is added
			snakeHead.move(pos_x, pos_y);


			//		create apple every 10 frames
			apple.setOrigin(20.f,20.f);
			apple.setFillColor(sf::Color::Red);

			sf::FloatRect appleBoundingBox = apple.getGlobalBounds();
			sf::FloatRect snakeBoundingBox = snakeHead.getGlobalBounds();


			if (snakeBoundingBox.intersects(appleBoundingBox)) {
				amountofsquares++;

				cout << "Apple Acquired" << endl;
				// create new apple in random position here
				srand (time(NULL));
				int appleXPosition = rand() % 800;
				srand (time(NULL));
				int appleYPosition = rand() % 600;
				apple.setPosition(appleXPosition, appleYPosition);
			}
		}






		//checks if key is pressed and acts accordingly, this was moved here because
		//the current position needs to be saved first, then a new position is
		//given through keypress()
		keyPress();
		window.draw(snakeHead);
		window.draw(apple);


		sf::Vector2f point = snakeHead.getPosition();
		int pos_x = snakeHead.getPosition().x;
		int pos_y = snakeHead.getPosition().y;

		if (amountofsquares >= 1) {
			for (int i = amountofsquares; i > 0; i = i-1) {
				sf::RectangleShape square(sf::Vector2f(40.f, 40.f));
				//		create new square each time
				square.setOrigin(20.f,20.f);

				
				//draws squares in different positions according to vector
				square.setPosition(vectorpos_x[vectorpos_x.size() - i],  vectorpos_y[vectorpos_y.size() - i]);
				square.setFillColor(sf::Color::Blue);

				cout << "square position: " << vectorpos_x[vectorpos_x.size() - i] << ", " << vectorpos_y[vectorpos_y.size() - i] << endl;
				cout << "snakeHead position: " << pos_x << ", " << pos_y  << endl;

				sf::Vector2f point2 = square.getPosition();
				if (point == point2)
				{
					
					cout << "Game Ended" << endl;
					window.close();
				}

				window.draw(square);
			}
		}




		// end of the magic
		window.display();
	}
	cout << "Program Ended" << endl;
	return 0;
}
