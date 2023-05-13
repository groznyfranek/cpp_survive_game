#include <SFML/Graphics.hpp>
class Figure
{
private:
    int characterPosX;
    int characterPosY;
    int characterWidthVal;
    int characterHeightVal;
    const int maxHealth = 5;
public:
	int health;
	sf::FloatRect characterRect;
	sf::RectangleShape character;    
    double deltaTime;
    
    Figure()
	{
		health = 5;
		int initialHealth = 5;
		deltaTime = 0.05;

		characterPosX = 1000;
		characterPosY = 100;
		characterWidthVal = 35;
		characterHeightVal = 35;

		characterRect = sf::FloatRect(characterPosX, characterPosY, characterWidthVal, characterHeightVal);

		character.setPosition(sf::Vector2f(characterRect.left, characterRect.top));
		character.setSize(sf::Vector2f(characterRect.width, characterRect.height));
		character.setFillColor(sf::Color::Green);
	}
    void move(Wall* wall)
    {
        double speed = 200.f;
        sf::Vector2f newPosition = character.getPosition();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            newPosition.x -= speed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            newPosition.x += speed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            newPosition.y -= speed * deltaTime;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            newPosition.y += speed * deltaTime;
        }

        // Check collision with wall
        sf::FloatRect wallBounds(wall->wall.getPosition(), wall->wall.getSize());

        if (newPosition.x < wallBounds.left + wallBounds.width && newPosition.x + character.getSize().x > wallBounds.left &&
            newPosition.y < wallBounds.top + wallBounds.height && newPosition.y + character.getSize().y > wallBounds.top)
        {
            return;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            if ((character.getPosition().x - speed * deltaTime >= 0))
            {
                character.move(-speed * deltaTime, 0);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            if (character.getPosition().x + character.getSize().x + speed * deltaTime <= 1280)
            {
                character.move(speed * deltaTime, 0);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            if (character.getPosition().y - speed * deltaTime >= 0)
            {
                character.move(0, -speed * deltaTime);
            }
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            if (character.getPosition().y + character.getSize().y + speed * deltaTime <= 720)
            {
                character.move(0, speed * deltaTime);
            }
        }
    }
};
