#include <iostream>
#include <queue>
#include <stack>
#include <thread>
#include <vector>
#include <SFML/Graphics.hpp>

// the scale factor of each pixel. 100 means each pixel is now 100x100 pixels.
const int SCALE_FACTOR = 50;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const sf::Color COLOR_TO_REPLACE = sf::Color::Black;
const sf::Color REPLACEMENT_COLOR = sf::Color(30, 145, 43);

sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Stack Demo", sf::Style::Close);

void floodFill(const int x, const int y, sf::Image &image, sf::Texture &texture, sf::Sprite &sprite) {
    /*
     * The type of data structure we're using. DFS = stack and BFS = queue
     */
    std::stack<std::pair<int, int> > container = {};
    /*
     * A visited vector to hold the nodes/coordinates that we've visited before.
     */
    std::vector<std::pair<int, int> > visited = {};
    container.push(std::make_pair(x, y));

    while (!container.empty()) {
        int currentX = container.top().first;
        int currentY = container.top().second;
        container.pop();


        // We check to make sure that the node we're about to fill is within the window boundaries.
        if (currentX < 0 || currentX >= WINDOW_WIDTH || currentY < 0 || currentY >= WINDOW_HEIGHT) {
            continue;
        }

        // If the node we're currently visiting has already been visited, then exit the loop and go to the next item.
        if (std::find(visited.begin(), visited.end(), std::make_pair(currentX, currentY)) != visited.end()) {
            continue;
        }


        // If the current node doesn't match the COLOR_TO_REPLACE, then exit the loop and go to the next item.
        if (image.getPixel(currentX / SCALE_FACTOR, currentY / SCALE_FACTOR) != COLOR_TO_REPLACE) {
            std::printf("Not filling (%d,%d) because the color doesn't match COLOR_TO_REPLACE.\n", currentX, currentY);
            visited.push_back({currentX, currentY});
            continue;
        }


        // Now that we know the current node can be colored, add it to the visited vector and change the color of it.
        visited.push_back({currentX, currentY});
        image.setPixel(currentX / SCALE_FACTOR, currentY / SCALE_FACTOR, REPLACEMENT_COLOR);

        // SFML functions to draw the sprites to the screen
        texture.loadFromImage(image);
        window.clear();
        window.draw(sprite);
        window.display();

        // Add the surround nodes (west, east, north, south) to the stack.
        container.push(std::make_pair(currentX - (1 * SCALE_FACTOR), currentY));
        container.push(std::make_pair(currentX + (1 * SCALE_FACTOR), currentY));
        container.push(std::make_pair(currentX, currentY - (1 * SCALE_FACTOR)));
        container.push(std::make_pair(currentX, currentY + (1 * SCALE_FACTOR)));
    }
    printf("Done filling.\n");
}


int main() {
    // Changes the window framerate. This effects how fast the sprites are drawn when using floodFill.
    window.setFramerateLimit(8);
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

    image.setPixel(2, 0, sf::Color::Green);
    image.setPixel(2, 1, sf::Color::Red);
    image.setPixel(2, 2, sf::Color::Red);
    image.setPixel(2, 3, sf::Color::Cyan);
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

                printf("Mouse clicked at (%d,%d)\n", scaledX, scaledY);
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
