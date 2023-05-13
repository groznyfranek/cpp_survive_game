#include <SFML/Graphics.hpp>

#include <random>
#include <vector>
#include <windows.h>
#include <fstream>
#include <string>
#include <stdio.h>        
#include <time.h> 

#include "classBall.h"
#include "classWall.h"
#include "classLabel.h"
#include "figure.h"

#define WIN32_LEAN_AND_MEAN

#pragma warning(disable : 4996)

class Game
{
public:
	int level;
	std::vector<Ball*> table;
    Wall* wall;
    Label* label;
    Figure* character;
    sf::RenderWindow* window;
	sf::Image* icon;
	Game()
	{
		std::cout << "The game has started" << std::endl;
		level = 1;
		window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Try to survive");
		window->setFramerateLimit(120);

		wall = new Wall;
		label = new Label(level);
		character = new Figure;
		icon = new sf::Image;

		for (int i = 0; i < 5; ++i)
		{
			table.push_back(new Ball(window, this->level));
		}

		std::string str = "Use keyboard arrows to avoid balls and walls";
		LPCSTR lpcstr = static_cast<LPCSTR>(str.c_str());
		bool accept = MessageBoxA(NULL, lpcstr, "Attention", MB_OK);

		if (!icon->loadFromFile("steve.png"))
		{
			std::cout << "Failed to load icon" << std::endl;
		}
		window->setIcon(icon->getSize().x, icon->getSize().y, icon->getPixelsPtr());
	}
	void physics(Ball* ball, sf::FloatRect& wallRect, sf::RectangleShape& player, int& col, int& h)
	{
		int existTime = ball->timeExist.getElapsedTime().asSeconds();
		if (ball->ballPosition.x < 0 || ball->ballPosition.x > 1280 - (ball->ball.getRadius() * 2)) ball->xVelocity *= -1;
		if (ball->ballPosition.y < 0 || ball->ballPosition.y > 720 - (ball->ball.getRadius() * 2)) ball->yVelocity *= -1;
		if (ball->ballPosition.x < wallRect.left + wallRect.width && ball->ballPosition.x + ball->ball.getRadius() * 2 > wallRect.left &&
			ball->ballPosition.y < wallRect.top + wallRect.height && ball->ballPosition.y + ball->ball.getRadius() * 2 > wallRect.top) {
			if (ball->ballPosition.x + ball->ball.getRadius() < wallRect.left || ball->ballPosition.x + ball->ball.getRadius() > wallRect.left + wallRect.width)
			{
				ball->xVelocity *= -1;
			}
			if (ball->ballPosition.y + ball->ball.getRadius() < wallRect.top || ball->ballPosition.y + ball->ball.getRadius() > wallRect.top + wallRect.height)
			{
				ball->yVelocity *= -1;
			}
		}

		if ((ball->ballPosition.x < player.getPosition().x + player.getSize().x && ball->ballPosition.x + ball->ball.getRadius() * 2 >player.getPosition().x &&
			ball->ballPosition.y < player.getPosition().y + player.getSize().y && ball->ballPosition.y + ball->ball.getRadius() * 2 >player.getPosition().y)
			&& existTime >= 2)
		{			
			--col;
			--h;
			std::cout << "YOU'VE GOT HIT!" << std::endl;
			erase(table, ball);
			table.push_back(new Ball(window, level));
			std::cout << "Lives left: " << h << std::endl;
			std::cout << std::endl;
			int r = std::rand() % 256;
			int g = std::rand() % 256;
			int b = std::rand() % 256;
			double brightness = (r + g + b) / 3.0f;
			while (brightness < 50.0f)
			{
				r = std::rand() % 256;
				g = std::rand() % 256;
				b = std::rand() % 256;
				brightness = (r + g + b) / 3.0f;
			}
			player.setFillColor(sf::Color(b, g, r));

			double x = player.getSize().x * 1.1f;
			double y = player.getSize().y * 1.1f;
			sf::Vector2f v(x, y);
			player.setSize(v);
			return;
		}

		ball->ballPosition.x += ball->xVelocity;
		ball->ballPosition.y += ball->yVelocity;
		ball->ball.setPosition(ball->ballPosition);
	}
	void run()
	{
		while (window->isOpen())
		{
			sf::Event event;
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window->close();
					for (auto& p : table)
					{
						delete p;
					}
					table.clear();
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				{
					window->close();
					for (auto& p : table)
					{
						delete p;
					}
					table.clear();
				}
			}
			if (level >= 10)
			{
				for (auto& p : table)
				{
					delete p;
				}
				table.clear();
				std::string str_result = "";
				str_result += "Congratulations \nYou reached level " + std::to_string(level);
				std::ofstream save("results.txt", std::ios::app);
				time_t timetoday;
				time(&timetoday);
				save << asctime(localtime(&timetoday)) << " Result: " << label->total << "\n Level: 10" << std::endl;
				save << "THE PLAYER HAS WON " << std::endl;
				save << "---------------------------" << std::endl;
				save.close();
				std::cout << "Your progress is saved" << std::endl;
				LPCSTR lpcstr = static_cast<LPCSTR>(str_result.c_str());
				int result = MessageBoxA(NULL, lpcstr, "YOU WON", MB_ICONWARNING | MB_RETRYCANCEL);
				if (result == 2)
				{
					window->close();
					for (auto& p : table)
					{
						delete p;
					}
					table.clear();					
				}

				if (result == 4) // retry
				{
					std::cout << "Your progress is saved" << std::endl;
					std::cout << "Restarting game... \nRestarting game... \nRestarting game..." << std::endl;
					std::cout << std::endl;
					
					delete wall;
					delete label;
					delete character;
					delete window;
					delete icon;
					level = 1;
					window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Try to survive");
					window->setFramerateLimit(120);
					wall = new Wall;
					label = new Label(level);
					character = new Figure;
					icon = new sf::Image;
					if (!icon->loadFromFile("steve.png"))
					{
						std::cout << "Failed to load icon" << std::endl;
					}
					window->setIcon(icon->getSize().x, icon->getSize().y, icon->getPixelsPtr());

					for (int i = 0; i < 5; ++i)
					{
						table.push_back(new Ball(window, 1));
					}
					std::cout << "The game has stared" << std::endl;
					std::string str = "Use keyboard arrows to avoid balls and walls";
					LPCSTR lpcstr = static_cast<LPCSTR>(str.c_str());
					bool accept = MessageBoxA(NULL, lpcstr, "Attention", MB_OK);
					}
			}
			if (character->health <= 0)
			{
				std::ofstream save("results.txt", std::ios::app); 
				time_t timetoday;
				time(&timetoday);
				save << asctime(localtime(&timetoday)) << " Result: " << label->total << "\n Level: " << level << std::endl;
				save << "---------------------------" << std::endl;
				save.close();
				std::cout << "Your progress is saved" << std::endl;
				for (auto& p : table)
				{
					delete p;
				}
				table.clear();
				std::string strResult = "";
				strResult += "Result: " + std::to_string(label->total) + "s\n" + "You reached level " + std::to_string(level);
				LPCSTR lpcstr = static_cast<LPCSTR>(strResult.c_str());
				int result = MessageBoxA(NULL, lpcstr, "YOU DIED", MB_ICONWARNING | MB_RETRYCANCEL);
				if (result == 2) // cancel
				{
					window->close();
					for (auto& p : table)
					{
						delete p;
					}
					table.clear();
				}
				if (result == 4) // retry
				{
					std::cout << "Restarting game... \nRestarting game... \nRestarting game..." << std::endl; 
					std::cout << std::endl;
					delete wall;
					delete label;
					delete character;
					delete window;
					this->level = 1;
					window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Try to survive");
					window->setFramerateLimit(120);
					wall = new Wall;
					label = new Label(level);
					character = new Figure;

					for (int i = 0; i < 5; ++i)
					{
						table.push_back(new Ball(window, 1));
					}

					std::string str = "Use keyboard arrows to avoid balls and walls";
					LPCSTR lpcstr = static_cast<LPCSTR>(str.c_str());
					bool accept = MessageBoxA(NULL, lpcstr, "Attention", MB_OK);
				}
			}
			//phycics  
			for (auto& i : table)
			{
				physics(i, wall->wallRect, character->character, label->collisions, character->health);
				for (auto& j : table)
				{
					handleCollision(i, j);
				}
			}

			character->move(wall);

			//render
			window->clear();

			for (auto& b : table)
			{
				window->draw(b->ball);
			}

			if (character->health > 0) level = label->work(level, table, character->deltaTime, window);

			window->draw(label->text);
			window->draw(wall->wall);
			window->draw(character->character);
			window->display();
		}
	}
	void handleCollision(Ball* p1, Ball* p2)
	{
		sf::Vector2f delta = p2->ball.getPosition() - p1->ball.getPosition();
		double distance = std::sqrt(std::pow(delta.x, 2) + std::pow(delta.y, 2));

		if (distance <= p1->ball.getRadius() + p2->ball.getRadius())
		{
			double p1x = p1->xVelocity;
			double p1y = p1->yVelocity;
			double p2x = p2->xVelocity;
			double p2y = p2->yVelocity;

			p1->xVelocity = p2x;
			p1->yVelocity = p2y;
			p2->xVelocity = p1x;
			p2->yVelocity = p1y;
		}
	}
	void erase(std::vector<Ball*>& table, Ball* b)
	{
		auto it = std::find(table.begin(), table.end(), b);
		if (it != table.end())
		{
			table.erase(it);
			delete b;
		}
	}
};