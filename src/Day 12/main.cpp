#include <SFML/Graphics.hpp>
#include <iostream>

int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "PONG");

    window.setVerticalSyncEnabled(true);
    sf::Image image;
    image.create(800, 600, sf::Color::Black);

    sf::Texture texture;
    texture.loadFromImage(image);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sf::Font font;
    if(!font.loadFromFile("../resources/arial.ttf")) {

    }

    sf::Text leftText;
    leftText.setFont(font);
    leftText.setString("0");
    leftText.setFillColor(sf::Color::White);
    leftText.setCharacterSize(20);
    leftText.setPosition(20, 10);

    sf::Text rightText;
    rightText.setFont(font);
    rightText.setString("0");
    rightText.setFillColor(sf::Color::White);
    rightText.setCharacterSize(20);
    rightText.setPosition(760, 10);

    unsigned int leftPlayerScore = 0;
    unsigned int rightPlayerScore = 0;

    //Paddles
    unsigned int width = 20;
    unsigned int height = 100;
    unsigned int paddleSpeed = 500;
    // Left Paddle
    sf::Image leftPaddle;
    leftPaddle.create(width, height, sf::Color::White);

    sf::Texture leftPaddleTexture;
    leftPaddleTexture.loadFromImage(leftPaddle);

    sf::Sprite leftPaddleSprite;
    leftPaddleSprite.setTexture(leftPaddleTexture);
    leftPaddleSprite.setPosition(10, 250);


    // Right Paddle
    sf::Image rightPaddle;
    rightPaddle.create(width, height, sf::Color::White);

    sf::Texture rightPaddleTexture;
    rightPaddleTexture.loadFromImage(rightPaddle);

    sf::Sprite rightPaddleSprite;
    rightPaddleSprite.setTexture(rightPaddleTexture);
    rightPaddleSprite.setPosition(770, 250);



    // Ball
    sf::Image ballImage;
    ballImage.create(20,20, sf::Color::White);

    sf::Texture ballTexture;
    ballTexture.loadFromImage(ballImage);

    sf::Sprite ballSprite;
    ballSprite.setTexture(ballTexture);
    ballSprite.setPosition(400, 300);
    float ballSpeedX = -500.0f;
    float ballSpeedY = 200.0f;


    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event {};
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        sf::Time dt = clock.restart();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            leftPaddleSprite.setPosition(leftPaddleSprite.getPosition().x,
                                         leftPaddleSprite.getPosition().y - (paddleSpeed * dt.asSeconds()));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            leftPaddleSprite.setPosition(leftPaddleSprite.getPosition().x,
                                         leftPaddleSprite.getPosition().y + (paddleSpeed * dt.asSeconds()));
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            rightPaddleSprite.setPosition(rightPaddleSprite.getPosition().x,
                                          rightPaddleSprite.getPosition().y - (paddleSpeed * dt.asSeconds()));
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            rightPaddleSprite.setPosition(rightPaddleSprite.getPosition().x,
                                          rightPaddleSprite.getPosition().y + (paddleSpeed * dt.asSeconds()));
        }

        ballSprite.setPosition(ballSprite.getPosition().x + (ballSpeedX * dt.asSeconds()),
                               ballSprite.getPosition().y + (ballSpeedY * dt.asSeconds()));

        sf::Vector2f ballPositionVector;
        ballPositionVector.x = ballSprite.getPosition().x + 10;
        ballPositionVector.y = ballSprite.getPosition().y + 10;

        sf::Vector2f rightPaddlePositionVector;
        rightPaddlePositionVector.x = rightPaddleSprite.getPosition().x + (float)width / 2;
        rightPaddlePositionVector.y = rightPaddleSprite.getPosition().y + (float)height / 2;

        sf::Vector2f leftPaddlePositionVector;
        leftPaddlePositionVector.x = leftPaddleSprite.getPosition().x + (float)width / 2;
        leftPaddlePositionVector.y = leftPaddleSprite.getPosition().y + (float)height / 2;

        if(ballPositionVector.x < 0 && ballSpeedX < 0) {
            rightPlayerScore++;
            rightText.setString(std::to_string(rightPlayerScore));
            ballSprite.setPosition(400,300);
        } else if(ballPositionVector.x > 800 && ballSpeedX > 0) {
            leftPlayerScore++;
            leftText.setString(std::to_string(leftPlayerScore));
            ballSprite.setPosition(400,300);
        } else if(ballPositionVector.y < 0 && ballSpeedY < 0) {
            ballSpeedY *= -1;
        } else if(ballPositionVector.y > 600 && ballSpeedY > 0) {
            ballSpeedY *= -1;
        }

        if(ballPositionVector.x < leftPaddlePositionVector.x + (float)width / 2 &&
           ballPositionVector.x > leftPaddlePositionVector.x - (float)width / 2 &&
           ballPositionVector.y < leftPaddlePositionVector.y + (float)height / 2 &&
           ballPositionVector.y > leftPaddlePositionVector.y - (float)height/ 2 &&
           ballSpeedX < 0) {
            ballSpeedX *= -1;
        }

        if(ballPositionVector.x < rightPaddlePositionVector.x + (float)width / 2 &&
           ballPositionVector.x > rightPaddlePositionVector.x - (float)width / 2 &&
           ballPositionVector.y < rightPaddlePositionVector.y + (float)height / 2 &&
           ballPositionVector.y > rightPaddlePositionVector.y - (float)height/ 2 &&
           ballSpeedX > 0) {
            ballSpeedX *= -1;
        }

        window.clear();

        window.draw(sprite);
        window.draw(leftPaddleSprite);
        window.draw(rightPaddleSprite);
        window.draw(ballSprite);
        window.draw(leftText);
        window.draw(rightText);

        window.display();
    }

    return 0;
}
