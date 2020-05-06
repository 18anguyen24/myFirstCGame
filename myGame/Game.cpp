#include "Game.h"

//Default Constructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initEnemies();
}

//Accessors
const bool Game::running() const
{
	return this->window->isOpen();
}

const bool Game::getEndGame() const
{
	return this->endGame;
}

//Functions
void Game::update()
{
	this->pollEvents();

	if (this->endGame == false)
	{
		this->updateMousePositions();
		this->updateEnemies();
	}

	//end game condition
	if (this->health <= 0)
	{
		this->endGame = true;
	}

} 

void Game::render()
{
	/*
		@return void
		-clear old frame
		-render objects
		-display frame in window

		Renders the game objects.
	*/
	this->window->clear();

	//Draw game objects
	this->renderEnemies();

	this->window->display();

}

void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMousePositions()
{
	/*
		@return void
		
		updates the mouse positions:
		* Mouse position relative to window(Vector2i)
	*/

	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::spawnEnemy()
{
	/*
		@return void

		Spawns enemies and sets their color and positions.
		-Sets a random position.
		-Sets a random color.
		-Adds enemy to the vector.
	*/

	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
		0.f
	);

	this->enemy.setFillColor(sf::Color::Green);

	//Spawn enemy
	this->enemies.push_back(this->enemy);
}

void Game::updateEnemies()
{
	/*
		@return void

		Updates the enemy spawn timer and spawns enemies
		when the total amount of enemies is smaller than the max
		Moves the enemies downwards.
		Removes the enemes at the edge of the screen //TODO
	*/
	//Updating the timer for enemy spawning
	if (this->enemies.size() < this->maxEnemies)
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax)
		{
			//Spawn the enemy and reset the timer
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}

	//Moving and updating the enemies
	for (int i = 0; i < this->enemies.size(); i++)
	{
		bool deleted = false;

		this->enemies[i].move(0.f, 5.f);

		//If enemy is past the bottom of the screen, delete it
		if (this->enemies[i].getPosition().y > this->window->getSize().y)
		{
			this->enemies.erase(this->enemies.begin() + i);
			this->health -= 1;
			std::cout << "Health: " << this->health << std::endl;
		}
	}

	//Check if clicked upon, actually attacking the enemy
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (this->mouseHeld == false)
		{
			this->mouseHeld = true;
			bool deleted = false;
			for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
			{
				if (this->enemies[i].getGlobalBounds().contains(this->mousePosView))
				{
					//Delete the enemy
					deleted = true;
					this->enemies.erase(this->enemies.begin() + i);

					//Gain points
					this->points += 1;
					std::cout << "Points: " << this->points << std::endl;
				}
			}
		}
	}
	else
	{
		this->mouseHeld = false;
	}
}

void Game::renderEnemies()
{
	//Rendering all the enemies
	for (auto& e : this->enemies)
	{
		this->window->draw(e);
	}
}

//Private Functions
void Game::initVariables()
{
	this->window = nullptr;

	//Game logic
	this->endGame = false;
	this->points = 0;
	this->health = 10;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->maxEnemies = 10;
	this->mouseHeld = false;
}

void Game::initWindow()
{
	//Size of window
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Game 1", sf::Style::Titlebar | sf::Style::Close);

	//Framerate
	this->window->setFramerateLimit(60);
}

void Game::initEnemies()
{
	//Position of enemy on x/y axis; top left corner is 0, 0
	//object's origin is always at top left corner
	this->enemy.setPosition(10.f, 10.f);
	
	//Sets size of enemy, needs .f to signify it's a float value
	//c++ has to set it to float so it is efficient
	this->enemy.setSize(sf::Vector2f(100.f, 100.f));
	this->enemy.setScale(sf::Vector2f(0.5f, 0.5f)); // resizes/scales object, multiply it by current size

	//Fills color of object
	this->enemy.setFillColor(sf::Color::Cyan);

	//Border of object
	//this->enemy.setOutlineColor(sf::Color::Green);

	//Thiccness of border
	//this->enemy.setOutlineThickness(1.f);
}

//Destructor
Game::~Game()
{
	delete this->window;
}
