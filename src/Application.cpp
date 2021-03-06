#pragma once 

#include <iostream>
#include <conio.h>           // _getch()
#include <SFML/Graphics.hpp> //Vector2i RenderWindow VideoMode
#include "planet1_Pawn.h"
#include "planet2_Pawn.h"
#include "planet3_Pawn.h"


//holds the window size 
sf::Vector2i viewSize(1300, 900);
//The viewMode is a SFML class that sets the width and the height of the window.
sf::VideoMode vm(viewSize.x, viewSize.y);
//Create a window 
sf::RenderWindow window(vm, "Basic Solar System Simulation 2D");
//Creating a sprite 
sf::Texture bgTexture;
sf::Sprite bgSprite;

#include <vector>

std::vector<Pawn*> planets;

planet1_Pawn planet1;
planet2_Pawn planet2;
planet3_Pawn planet3;



static void updateInput(sf::RenderWindow& win)
{
	sf::Event event;

	while (win.pollEvent(event))
	{

		// Request for closing the window
		if (event.type == sf::Event::Closed)
			win.close();

		//Key Pressed
		if (event.type == sf::Event::KeyPressed)
		{
			switch(event.key.code)
			{
			case sf::Keyboard::Escape:
				// The escape key was pressed
				std::cout << "window was ternimated." << std::endl;
				win.close();
				break;
			default:
				break;
			}
		}

		//Key Release
		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			default:
				break;
			}
		}
	}
}

static void BeginPlay(sf::RenderWindow &window)
{

	window.draw(bgSprite);
	window.draw(planet1);
	window.draw(planet2);
	window.draw(planet3);
}

static void Tick(float deltaTime)
{
	planet1.Tick(deltaTime);
	planet2.Tick(deltaTime);
	planet3.Tick(deltaTime);

}

#include <cmath>

int main()
{

	//Clock for deltaTime Calculation 
	sf::Clock dtClock;
	sf::Time dt = dtClock.restart();

	//Clock for FPS Calculation
	sf::Clock StopWatch;
	signed int Timer = StopWatch.getElapsedTime().asMilliseconds();
	signed int frames = 0;


	//Sprite initialization
	//background
	bgTexture.loadFromFile("Content/graphics/starbg2.png");
	bgSprite.setTexture(bgTexture);
	//Planets
	planet1.BeginPlay("Content/graphics/Planet-1.png",
		sf::Vector2f((float)viewSize.x/2,
			(float)viewSize.y/2),20.0f);
	planet2.BeginPlay("Content/graphics/Planet-2.png",
		sf::Vector2f((float)viewSize.x / 2, (float)viewSize.y / 2) + sf::Vector2f(200.0f,200.0f),
		20.0f);
	planet3.BeginPlay("Content/graphics/Planet-2.png",
		sf::Vector2f((float)viewSize.x / 2, (float)viewSize.y / 2) + sf::Vector2f(-200.0f, -200.0f),
		20.0f);

	planets.push_back(&planet1);
	planets.push_back(&planet2);
	planets.push_back(&planet3);
	


	
	while (window.isOpen())
	{
		//Handle Input Events
		updateInput(window);
		
		//Clear Current Buffer
		window.clear(sf::Color::Black);
		

		//deltaTime Clock
		BeginPlay(window);
		dt = dtClock.restart();
		float deltaTime = dt.asSeconds();
		if (deltaTime > 0.001)
			deltaTime = 0.001f;
		else
			deltaTime = dt.asSeconds();
		Tick(deltaTime);
		/*sf::Vertex line1[] =
		{
			sf::Vertex(sf::Vector2f(planet1.getPosition().x,planet1.getPosition().y),sf::Color::Red),
			sf::Vertex(sf::Vector2f(planet2.getPosition().x,planet2.getPosition().y),sf::Color::Green)
		};
		sf::Vertex line2[] =
		{
			sf::Vertex(sf::Vector2f(planet1.getPosition().x, planet1.getPosition().y)),
				sf::Vertex(sf::Vector2f(planet3.getPosition().x, planet3.getPosition().y))
		};

		window.draw(line1, 2, sf::Lines);
		window.draw(line2, 2, sf::Lines);*/

		//Render Game Objects
		window.display();


		//fps calculation
		++frames;
		if (StopWatch.getElapsedTime().asMilliseconds() - Timer > 1000)
		{
			Timer += 1000;
			//Memory Allocation Practice
			char* str1 = (char*)std::malloc(4 * sizeof(char));
			str1[0] = 'f';
			str1[1] = 'p';
			str1[2] = 's';
			str1[3] = '\0';
			std::string str2 = std::to_string(frames);
			std::string newTitle =  str1 + std::string(" : ") +  str2;

			window.setTitle(newTitle);

			//free memory
			std::free(str1);

			frames = 0;
		}

	}


	_getch();
	return 0;
}

