#include <SFML/Graphics.hpp>

// the scale factor of each pixel. 100 means each pixel is now 100x100 pixels.
const float SCALE_FACTOR = 100;
const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;

std::vector<sf::Sprite> itemsToDraw = {};

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Stack Demo", sf::Style::Close);
    window.setFramerateLimit(10);
    sf::Vector2i pos = sf::Vector2i(0, 0);
    window.setPosition(pos);


    sf::Texture texture;
    sf::Image image;
    image.create(1 * SCALE_FACTOR, 1 * SCALE_FACTOR, sf::Color::White);
    texture.loadFromImage(image);

    sf::Sprite startingBlock;
    startingBlock.setTexture(texture);
    startingBlock.setPosition(2 * SCALE_FACTOR, 2 * SCALE_FACTOR);
    startingBlock.setColor(sf::Color::Green);

    while (window.isOpen()) {
        window.clear(sf::Color::Black);
        window.draw(startingBlock);

        for (const auto &item: itemsToDraw) {
            window.draw(item);
        }
        window.display();


        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                // needed to ensure that the sprites are placed as a multiple of SCALE_FACTOR.
                int scaledX = event.mouseButton.x / SCALE_FACTOR;
                scaledX *= SCALE_FACTOR;
                int scaledY = event.mouseButton.y / SCALE_FACTOR;
                scaledY *= SCALE_FACTOR;

                sf::Sprite newSprite;
                newSprite.setTexture(texture);
                newSprite.setPosition(scaledX, scaledY);
                itemsToDraw.push_back(newSprite);
            }
            if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
                itemsToDraw.clear();
            }
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }

    return 0;
}
