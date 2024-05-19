#include <SFML/Graphics.hpp>
#include <iostream>

// ������� ��� �������� �� ������� ���糿 ���� ������������
bool checkCollision(const sf::FloatRect& rect1, const sf::FloatRect& rect2)
{
    return rect1.intersects(rect2);
}

// ������� ��� ����������� ���� ����� �� ��� ��������
void moveToEdge(sf::RectangleShape& tank, const sf::Vector2f& velocity, const sf::RectangleShape& otherTank)
{
    sf::Vector2f stepVelocity = velocity;
    // �������� ���� ����, ��� ����� ��������� ������ ��������
    while(std::abs(stepVelocity.x) > 0.1f || std::abs(stepVelocity.y) > 0.1f)
    {
        sf::Vector2f moveStep = {stepVelocity.x * 0.5f, stepVelocity.y * 0.5f};
        sf::Vector2f newPos = tank.getPosition() + moveStep;
        sf::FloatRect newRect(newPos, tank.getSize());

        if(!checkCollision(newRect, otherTank.getGlobalBounds()))
        {
            tank.move(moveStep);
        }

        stepVelocity *= 0.5f;  // �������� ���� �����
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "2D Tank Collision");

    // ��������� ���� ������������, �� ������������� �����
    sf::RectangleShape tank1(sf::Vector2f(50.f, 50.f));
    tank1.setFillColor(sf::Color::Green);
    tank1.setPosition(200.f, 300.f);

    sf::RectangleShape tank2(sf::Vector2f(50.f, 50.f));
    tank2.setFillColor(sf::Color::Blue);
    tank2.setPosition(400.f, 300.f);

    sf::Vector2f velocity1(0.f, 0.f);  // �������� ������� �����
    sf::Vector2f velocity2(0.f, 0.f);  // �������� ������� �����
    float speed = 10.f;  // �������� ���� �����

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // �������� �������� ����� �������� �����
        velocity1 = {0.f, 0.f};
        velocity2 = {0.f, 0.f};

        // ������� ����� ��� ��������� ������ ������ (WASD)
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            velocity1.y = -speed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            velocity1.y = speed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            velocity1.x = -speed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            velocity1.x = speed;
        }

        // ������� ����� ��� ��������� ������ ������ (������)
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            velocity2.y = -speed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            velocity2.y = speed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            velocity2.x = -speed;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            velocity2.x = speed;
        }

        // ��������� ������� ����� ���������
        sf::Vector2f newPos1 = tank1.getPosition() + velocity1;
        sf::Vector2f newPos2 = tank2.getPosition() + velocity2;

        sf::FloatRect newRect1(newPos1, tank1.getSize());
        sf::FloatRect newRect2(newPos2, tank2.getSize());

        // �������� ����� �� ��������� ������� ����� ���� ���� ��������
        if(!checkCollision(newRect1, tank2.getGlobalBounds()))
        {
            tank1.move(velocity1);
        }
        else
        {
            moveToEdge(tank1, velocity1, tank2);
        }

        if(!checkCollision(newRect2, tank1.getGlobalBounds()))
        {
            tank2.move(velocity2);
        }
        else
        {
            moveToEdge(tank2, velocity2, tank1);
        }

        window.clear();
        window.draw(tank1);
        window.draw(tank2);
        window.display();
    }

    return 0;
}
