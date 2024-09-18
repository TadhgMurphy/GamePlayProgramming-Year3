#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 

//const int GRID_HEIGHT = 8;
//const int GRID_WIDTH = 8;
const int GRID_SIZE = 8;
const int TILE_TYPES = 5;
const int TILE_SIZE = 64;

bool checkForMatches(int grid[GRID_SIZE][GRID_SIZE])
{
	bool matchFound = false;

	for (int y = 0; y < GRID_SIZE; y++)
	{
		for (int x = 0; x < GRID_SIZE; x++)
		{
			if (grid[y][x] == grid[y][x + 1]
				&& grid[y][x + 1] == grid[y][x + 2]
				&& grid[y][x] != -1)
			{
				matchFound = true;
				grid[y][x] = -1;
				grid[y][x + 1] = -1;
				grid[y][x + 2] = -1;
			}
		}
	}

	for (int x = 0; x < GRID_SIZE; x++)
	{
		for (int y = 0; y < GRID_SIZE; y++)
		{
			if (grid[y][x] == grid[y + 1][x]
				&& grid[y + 1][x] == grid[y + 2][x]
				&& grid[y][x] != -1)
			{
				matchFound = true;
				grid[y][x] = -1;
				grid[y + 1][x] = -1;
				grid[y + 2][x] = -1;
			}
		}
	}

	return matchFound;
}

void initialiseGrid(int grid[GRID_SIZE][GRID_SIZE])
{
	for (int y = 0; y < GRID_SIZE; y++)
	{
		for (int x = 0; x < GRID_SIZE; x++)
		{
			grid[y][x] = rand() % TILE_TYPES;
		}
	}
}

int main()
{

	sf::RenderWindow window(sf::VideoMode(800, 600), "Match3");

	srand(time(NULL));

	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);

	sf::Time timeSinceLastUpdate = sf::Time::Zero;


	sf::Clock clockForFrameRate;

	clockForFrameRate.restart();

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		timeSinceLastUpdate += clockForFrameRate.restart();


		if (timeSinceLastUpdate > timePerFrame)
		{
			window.display();


			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}