#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>

// ��������� ��� ����������� �� ������� �� ��������
const float SCALE = 30.f;

// �������� �������
class MyContactListener : public b2ContactListener
{
public:
    void BeginContact(b2Contact* contact) override
    {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        if(fixtureA->IsSensor() || fixtureB->IsSensor())
        {
            std::cout << "Player entered sensor" << std::endl;
        }
    }

    void EndContact(b2Contact* contact) override
    {
        b2Fixture* fixtureA = contact->GetFixtureA();
        b2Fixture* fixtureB = contact->GetFixtureB();

        if(fixtureA->IsSensor() || fixtureB->IsSensor())
        {
            std::cout << "Player left sensor" << std::endl;
        }
    }
};

int main()
{
    // ��������� ���� SFML
    sf::RenderWindow window(sf::VideoMode(800, 600), "Box2D and SFML");

    // ��������� ���� Box2D � ����������
    b2World world(b2Vec2(0.0f, 9.8f));

    // ��������� ��������� �������
    MyContactListener myContactListener;
    world.SetContactListener(&myContactListener);

    // ��������� ����
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(400.f / SCALE, 550.f / SCALE);

    b2Body* groundBody = world.CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    groundBox.SetAsBox((800.f / 2) / SCALE, (50.f / 2) / SCALE);

    groundBody->CreateFixture(&groundBox, 0.0f);

    // ��������� ������
    b2BodyDef playerBodyDef;
    playerBodyDef.type = b2_dynamicBody;
    playerBodyDef.position.Set(400.f / SCALE, 500.f / SCALE);

    b2Body* playerBody = world.CreateBody(&playerBodyDef);

    b2PolygonShape playerBox;
    playerBox.SetAsBox((50.f / 2) / SCALE, (50.f / 2) / SCALE);

    b2FixtureDef playerFixtureDef;
    playerFixtureDef.shape = &playerBox;
    playerFixtureDef.density = 1.0f;
    playerFixtureDef.friction = 0.3f;

    playerBody->CreateFixture(&playerFixtureDef);

    // ��������� �������
    b2BodyDef sensorBodyDef;
    sensorBodyDef.position.Set(400.f / SCALE, 300.f / SCALE);

    b2Body* sensorBody = world.CreateBody(&sensorBodyDef);

    b2CircleShape sensorShape;
    sensorShape.m_radius = 50.f / SCALE;

    b2FixtureDef sensorFixtureDef;
    sensorFixtureDef.shape = &sensorShape;
    sensorFixtureDef.isSensor = true;

    sensorBody->CreateFixture(&sensorFixtureDef);

    // ³���������� ����
    sf::RectangleShape ground(sf::Vector2f(800.f, 50.f));
    ground.setFillColor(sf::Color::Green);
    ground.setOrigin(400.f, 25.f);
    ground.setPosition(400.f, 550.f);

    // ³���������� ������
    sf::RectangleShape player(sf::Vector2f(50.f, 50.f));
    player.setFillColor(sf::Color::Blue);
    player.setOrigin(25.f, 25.f);

    // ³���������� �������
    sf::CircleShape sensor(50.f);
    sensor.setFillColor(sf::Color(255, 0, 0, 100)); // ������������ ��������
    sensor.setOrigin(50.f, 50.f);
    sensor.setPosition(400.f, 500.f);

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        // ������� �������� �����������
        b2Vec2 velocity(0.f, playerBody->GetLinearVelocity().y);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            velocity.x = -5.f;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            velocity.x = 5.f;
        }
        playerBody->SetLinearVelocity(velocity);

        // ��������� ���� Box2D
        world.Step(1 / 60.f, 6, 2);

        // ��������� ��������� ������
        b2Vec2 playerPosition = playerBody->GetPosition();
        player.setPosition(playerPosition.x * SCALE, playerPosition.y * SCALE);
        player.setRotation(playerBody->GetAngle() * 180 / b2_pi);

        // �������� ����
        window.clear();

        // ��������� ��'����
        window.draw(ground);
        window.draw(player);
        window.draw(sensor);

        // ³���������� ����
        window.display();
    }

    return 0;
}
