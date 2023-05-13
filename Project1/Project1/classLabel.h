#include <SFML/Graphics.hpp>
#include <iomanip>
#include <sstream>
#include <string>
class Label
{
public:
    std::string levelLabel;
    int toNextLevel;
    int total;
    int collisions;
    std::string hearts;
    sf::Text text;
    sf::Font font;
    sf::Clock totalTime;
    sf::Clock upgradeTime;

    Label(int level)
    {
        toNextLevel = 20;
        total = 0;
        collisions = 5;
        hearts = "<3<3<3<3<3";
        totalTime.restart();
        upgradeTime.restart();
        levelLabel = "Level " + std::to_string(level)+"  |  To next level: " + std::to_string(toNextLevel) + "  |  Total: " + std::to_string(total)+ "  |  lives: " + hearts;
        if (!font.loadFromFile("./font.ttf"))
        {
            std::cout << "Failed to load font" << std::endl;
        }
        text.setFont(font);
        text.setOutlineThickness(1.0f);
        text.setOutlineColor(sf::Color::White);
        text.setPosition(sf::Vector2f(0, 0));
        text.setString(levelLabel);
    }
    int work(int& level, std::vector<Ball*>& table, double& deltaTime, sf::RenderWindow* window)
    {
        total = totalTime.getElapsedTime().asSeconds();
        toNextLevel = 16 - upgradeTime.getElapsedTime().asSeconds();

        double speed = deltaTime / 0.05;
        speed *= 100;
        std::stringstream stream;
        stream << std::fixed << std::setprecision(2) << speed;
        std::string strSpeed = stream.str();

        hearts = "";
        std::string heart = "<3 ";
        for (int i = 0; i < collisions; ++i)
        {
            hearts += heart;
        }

        levelLabel = "Level " + std::to_string(level) + "  |  To next level: " + std::to_string(toNextLevel) + "  |  Total: " + std::to_string(total)
            + "  |  Lives: " + hearts + " |  Speed: " + strSpeed +"%";
        text.setString(levelLabel);

        if (toNextLevel <= 0)
        {
            level++;
            if (level % 2 == 0 )table.push_back(new Ball(window,level)); 
            std::cout << "Level up! You're now on level " << level << std::endl;                       
            std::cout << "Balls on board: " << table.size() << std::endl;
            std::cout << std::endl;
            upgradeTime.restart();
            deltaTime *= 0.9;
            for (auto& ball : table)
            {
                if (level <= 5)
                {
                    ball->xVelocity *= 1.1;
                    ball->yVelocity *= 1.1;
                }
                if (level <= 5)
                {
                    ball->ball.setRadius(level * 5);

                }
            }
        }
        return level;
    } 
};