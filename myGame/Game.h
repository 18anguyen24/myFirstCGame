#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <ctime>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
	Class that acts as the game engine.
	Wrapper class.
*/
class Game
{
public:
	//Default Constructor
	Game();

	//Accessors
	const bool running() const;
	const bool getEndGame() const;

	//Functions
	void update();
	void render();
	void pollEvents();
	void updateMousePositions();

	void spawnEnemy();
	void updateEnemies();
	void renderEnemies();

	//Destructor
	virtual ~Game();

private:
	//Variables
	//Window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Mouse Positions
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	
	//Game logic
	bool endGame;
	unsigned points; //points will never be below 0
	int health;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool mouseHeld;

	//Game objects
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;

	//Private functions
	void initVariables();
	void initWindow();
	void initEnemies();

};

#endif 

