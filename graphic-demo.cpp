#include <SFML/Graphics.hpp>

const int SCALE_FACTOR = 20;
const int WINDOW_HEIGHT = 600;
const int WINDOW_WIDTH = 800;

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Stack Demo", sf::Style::Close);
    window.setVerticalSyncEnabled(true);


    sf::Texture texture;
    sf::Image image;
    image.create(100, 100, sf::Color::Red);
    texture.loadFromImage(image);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setOrigin(100 / 2, 100 / 2);
    sprite.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    while (window.isOpen()) {
        window.clear(sf::Color::Green);
        window.draw(sprite);
        window.display();


        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
    }
    return 0;
}
