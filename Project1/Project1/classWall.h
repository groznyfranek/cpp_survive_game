#include <SFML/Graphics.hpp>
#include <random>
class Wall 
{
public:
    sf::FloatRect wallRect;
    sf::RectangleShape wall;
    Wall()
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> wallX(300, 980);
        std::uniform_int_distribution<> wallY(200, 520);
        std::uniform_int_distribution<> wallHeight(200, 400);

        int wallPosX = wallX(gen);
        int wallPosY = wallY(gen);
        int wallWidthVal = 1;
        int wallHeightVal = wallHeight(gen);

        wallRect = sf::FloatRect(wallPosX, wallPosY, wallWidthVal, wallHeightVal);

        wall.setPosition(sf::Vector2f(wallRect.left, wallRect.top));
        wall.setSize(sf::Vector2f(wallRect.width, wallRect.height));
        wall.setFillColor(sf::Color::Blue);
    }
};
