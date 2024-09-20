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
		for (int x = 0; x < GRID_SIZE - 2; x++)
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
		for (int y = 0; y < GRID_SIZE - 2; y++)
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

void dropTiles(int grid[GRID_SIZE][GRID_SIZE])
{
	for (int x = 0; x < GRID_SIZE; x++)
	{
		for (int y = GRID_SIZE - 1; y >= 0; y--)
		{
			if (grid[y][x] == -1)
			{
				for (int k = y; k > 0; k--)
				{
					grid[k][x] = grid[k - 1][x]; //Moves tiles down
				}
				grid[0][x] = rand() % TILE_TYPES;// Drops new tiles
			}
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

	int grid[GRID_SIZE][GRID_SIZE];
	initialiseGrid(grid);

	sf::Texture tileTextures[TILE_TYPES];
	for (int i = 0; i < TILE_TYPES; i++)
	{
		tileTextures[i].loadFromFile("tile" + std::to_string(i) + ".png");
	}

	sf::RectangleShape tileOutline(sf::Vector2f(TILE_SIZE, TILE_SIZE));
	tileOutline.setFillColor(sf::Color::Transparent);
	tileOutline.setOutlineThickness(3);
	tileOutline.setOutlineColor(sf::Color::Black);

	sf::Vector2i selectedTile(-1, -1);
	bool tileSelected = false;

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					int x = event.mouseButton.x / TILE_SIZE;
					int y = event.mouseButton.y / TILE_SIZE;
					if (!tileSelected)
					{
						selectedTile = sf::Vector2i(x, y);
						tileSelected = true;

						tileOutline.setPosition(x * TILE_SIZE, y * TILE_SIZE);
					}
					else
					{
						std::swap(grid[selectedTile.y][selectedTile.x], grid[y][x]);
						tileSelected = false;

						// Check for matches after swapping
						if (checkForMatches(grid))
						{
							// Drop tiles and keep checking for new matches
							do
							{
								dropTiles(grid);
							} while (checkForMatches(grid)); // Repeat until no more matches
						}
						else
						{
							// If no match is found, swap back
							std::swap(grid[selectedTile.y][selectedTile.x], grid[y][x]);
						}
					}
				}
			}
		}

		
		window.clear();
		for (int y = 0; y < GRID_SIZE; y++)
		{
			for (int x = 0; x < GRID_SIZE; x++)
			{
				if (grid[y][x] != -1)
				{
					sf::Sprite sprite(tileTextures[grid[y][x]]);
					sprite.setPosition(x * TILE_SIZE, y * TILE_SIZE);
					window.draw(sprite);
				}
			}
		}

		if (tileSelected)
		{
			window.draw(tileOutline);
		}

		window.display();
	}

	
	return 0;
}