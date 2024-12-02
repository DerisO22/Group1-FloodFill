#include <iostream>
#include <stack>
#include <vector>
#include <SFML/Graphics.hpp>

// the scale factor of each pixel. 100 means each pixel is now 100x100 pixels.
const int SCALE_FACTOR = 100;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const sf::Color COLOR_TO_REPLACE = sf::Color::Black;
const sf::Color REPLACEMENT_COLOR = sf::Color::Magenta;

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Stack Demo", sf::Style::Close);

void floodFill(const int x, const int y, sf::Image &image, sf::Texture &texture, sf::Sprite &sprite) {
    std::stack<std::pair<int, int> > container = {};
    std::vector<std::pair<int, int> > visited = {};
    container.push(std::make_pair(x, y));


    while (!container.empty()) {
        int currentX = container.top().first;
        int currentY = container.top().second;
        container.pop();

        if (currentX < 0 || currentX >= WINDOW_WIDTH || currentY < 0 || currentY >= WINDOW_HEIGHT) {
            continue;
        }

        if (std::find(visited.begin(), visited.end(), std::make_pair(currentX, currentY)) != visited.end()) {
            continue;
        }

        if (image.getPixel(currentX / SCALE_FACTOR, currentY / SCALE_FACTOR) != COLOR_TO_REPLACE) {
            std::printf("not filling (%d,%d) because the color is rgb(%u,%u,%u)\n", currentX, currentY,
                        image.getPixel(currentX / SCALE_FACTOR, currentY / SCALE_FACTOR).r,
                        image.getPixel(currentX / SCALE_FACTOR, currentY / SCALE_FACTOR).g,
                        image.getPixel(currentX / SCALE_FACTOR, currentY / SCALE_FACTOR).b);
            visited.push_back({currentX, currentY}); // add to the visited vector so we don't revisit it.
            continue;
        }

        // printf("Current is %d %d\n", currentX, currentY);
        visited.push_back({currentX, currentY});

        image.setPixel(currentX / SCALE_FACTOR, currentY / SCALE_FACTOR, REPLACEMENT_COLOR);
        texture.loadFromImage(image);

        window.clear();
        window.draw(sprite);
        window.display();

        // these are needed for some reason when ($X, 400) gets pushed, for example.
        // it keeps adding ($X, 500) to the stack, which then adds ($X, 400) back, which causes an infinite loop
        if (currentX - (1 * SCALE_FACTOR) >= 0)
            container.push(std::make_pair(currentX - (1 * SCALE_FACTOR), currentY));
        if (currentX + (1 * SCALE_FACTOR) < WINDOW_WIDTH)
            container.push(std::make_pair(currentX + (1 * SCALE_FACTOR), currentY));
        if (currentY - (1 * SCALE_FACTOR) >= 0)
            container.push(std::make_pair(currentX, currentY - (1 * SCALE_FACTOR)));
        if (currentY + (1 * SCALE_FACTOR) < WINDOW_HEIGHT)
            container.push(std::make_pair(currentX, currentY + (1 * SCALE_FACTOR)));
    }
}

int main() {
    window.setFramerateLimit(10);
    sf::Vector2i pos = sf::Vector2i(0, 0);
    window.setPosition(pos);

    sf::Image image;
    image.create(WINDOW_WIDTH, WINDOW_HEIGHT, sf::Color::Black);
    image.setPixel(0, 0, sf::Color::White);
    image.setPixel(0, 1, sf::Color::White);
    image.setPixel(0, 2, sf::Color::White);
    image.setPixel(4, 2, sf::Color::White);
    image.setPixel(5, 2, sf::Color::White);
    image.setPixel(6, 2, sf::Color::White);

    image.setPixel(2, 0, sf::Color::Red);
    image.setPixel(2, 1, sf::Color::Red);
    image.setPixel(2, 2, sf::Color::Red);
    image.setPixel(2, 3, sf::Color::Red);
    image.setPixel(3, 2, sf::Color::Red);
    image.setPixel(4, 0, sf::Color::Red);
    image.setPixel(5, 0, sf::Color::Red);

    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite;
    sprite.setScale(SCALE_FACTOR, SCALE_FACTOR);
    sprite.setTexture(texture);


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
                // needed to ensure that the sprites are placed as a multiple of SCALE_FACTOR.
                int scaledX = event.mouseButton.x / SCALE_FACTOR;
                scaledX *= SCALE_FACTOR;
                int scaledY = event.mouseButton.y / SCALE_FACTOR;
                scaledY *= SCALE_FACTOR;


                printf("Mouse clicked at %d %d\n", scaledX, scaledY);
                if (scaledX >= 0 && scaledX < WINDOW_WIDTH && scaledY >= 0 && scaledY < WINDOW_HEIGHT) {
                    floodFill(scaledX, scaledY, image, texture, sprite);
                }
            }

            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}
