#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
class Ball 
{
private:
	enum class Color { GREEN, BLUE, RED, PINK, WHITE, YELLOW };
	Color colorr;
public:
	double xVelocity;
	double yVelocity;
	sf::Vector2f ballPosition;
	sf::CircleShape ball;
	sf::Clock timeExist;
	~Ball()
	{
		std::cout << "The ball has been deleted" << std::endl;
	}

	Ball(sf::RenderWindow* window, int level)
	{
		std::cout << "The ball has been spawned" << std::endl;

		timeExist.restart();

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> xx(20, 1200);
		std::uniform_int_distribution<> yy(20, 700);

		ballPosition.x = xx(gen);
		ballPosition.y = yy(gen);

		ball.setPosition(ballPosition);		
		setRandomColor();

		std::uniform_int_distribution<> xvel(level, level + 3);
		std::uniform_int_distribution<> yvel(level, level + 3);
		xVelocity = xvel(gen);
		yVelocity = yvel(gen);
		ball.setRadius(level * 5);

		window->draw(ball);
		window->display();
	}
	void setRandomColor()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> c(0, 5);
		int color = c(gen);
		switch (color) {
		case 0:
			colorr = Color::GREEN;
			break;
		case 1:
			colorr = Color::BLUE;
			break;
		case 2:
			colorr = Color::RED;
			break;
		case 3:
			colorr = Color::PINK;
			break;
		case 4:
			colorr = Color::WHITE;
			break;
		case 5:
			colorr = Color::YELLOW;
			break;
		}
		switch (colorr)
		{
		case Color::GREEN:
			ball.setFillColor(sf::Color(124, 252, 0));
			break;
		case Color::BLUE:
			ball.setFillColor(sf::Color(0, 0, 255));
			break;
		case Color::RED:
			ball.setFillColor(sf::Color(255, 0, 0));
			break;
		case Color::PINK:
			ball.setFillColor(sf::Color(255, 20, 147));
			break;
		case Color::WHITE:
			ball.setFillColor(sf::Color(255, 255, 255));
			break;
		case Color::YELLOW:
			ball.setFillColor(sf::Color(228, 208, 10));
			break;
		}
	}
};

