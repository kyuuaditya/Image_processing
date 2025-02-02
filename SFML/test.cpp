#include <sfml/Graphics.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include <chrono>

int main() {
    // Load an image file
    sf::Image image;
    if (!image.loadFromFile("image.jpg")) {
        std::cerr << "Failed to load image" << std::endl;
        return -1;
    }

    // Get image size
    sf::Vector2u size = image.getSize();
    std::cout << "Image size: " << size.x << "x" << size.y << std::endl;

    int padding = 2;
    std::vector<std::vector<std::vector<int>>> imageData(size.x + padding, std::vector<std::vector<int>>(size.y + padding, std::vector<int>(3)));
    std::vector<std::vector<std::vector<int>>> tempImage(size.x + padding, std::vector<std::vector<int>>(size.y + padding, std::vector<int>(3)));

    // reading image data and sending it to an array
    for (unsigned int x = padding / 2; x < size.x + padding / 2; ++x) {
        for (unsigned int y = padding / 2; y < size.y + padding / 2; ++y) {
            sf::Color pixel = image.getPixel(x - padding / 2, y - padding / 2); // get pixel color
            imageData[x][y][0] = pixel.r;
            imageData[x][y][1] = pixel.g;
            imageData[x][y][2] = pixel.b;
        }
    }

    auto start = std::chrono::high_resolution_clock::now(); // Start time

    // ! <------------------------------------------ sobel filter ----------------------------------------->
    // 3x3 kernel    1  0 -1    -1 -2 -1
    //               2  0 -2     0  0  0
    //               1  0 -1     1  2  1
    // applying sobel filter to the image
    for (unsigned int x = 1; x < size.x - 1; ++x) {
        for (unsigned int y = 1; y < size.y - 1; ++y) {
            int gx = imageData[x - 1][y - 1][0] + 2 * imageData[x - 1][y][0] + imageData[x - 1][y + 1][0] - imageData[x + 1][y - 1][0] - 2 * imageData[x + 1][y][0] - imageData[x + 1][y + 1][0];
            int gy = imageData[x - 1][y - 1][0] + 2 * imageData[x][y - 1][0] + imageData[x + 1][y - 1][0] - imageData[x - 1][y + 1][0] - 2 * imageData[x][y + 1][0] - imageData[x + 1][y + 1][0];
            int g = sqrt(gx * gx + gy * gy);
            image.setPixel(x, y, sf::Color(g, g, g));
            tempImage[x][y][0] = g;
            tempImage[x][y][1] = g;
            tempImage[x][y][2] = g;
        }
    }
    imageData = tempImage;
    // ! <------------------------------------------ sobel filter ----------------------------------------->

    // ? <------------------------------------------ gaussian filter ----------------------------------------->
    // 3x3 kernel   1 2 1  
    //              2 4 2
    //              1 2 1
    // applying gaussian blur to the image
    for (unsigned int x = 1; x < size.x - 1; ++x) {
        for (unsigned int y = 1; y < size.y - 1; ++y) {
            int r = (imageData[x - 1][y - 1][0] + 2 * imageData[x - 1][y][0] + imageData[x - 1][y + 1][0] + 2 * imageData[x][y - 1][0] + 4 * imageData[x][y][0] + 2 * imageData[x][y + 1][0] + imageData[x + 1][y - 1][0] + 2 * imageData[x + 1][y][0] + imageData[x + 1][y + 1][0]) / 16;
            int g = (imageData[x - 1][y - 1][1] + 2 * imageData[x - 1][y][1] + imageData[x - 1][y + 1][1] + 2 * imageData[x][y - 1][1] + 4 * imageData[x][y][1] + 2 * imageData[x][y + 1][1] + imageData[x + 1][y - 1][1] + 2 * imageData[x + 1][y][1] + imageData[x + 1][y + 1][1]) / 16;
            int b = (imageData[x - 1][y - 1][2] + 2 * imageData[x - 1][y][2] + imageData[x - 1][y + 1][2] + 2 * imageData[x][y - 1][2] + 4 * imageData[x][y][2] + 2 * imageData[x][y + 1][2] + imageData[x + 1][y - 1][2] + 2 * imageData[x + 1][y][2] + imageData[x + 1][y + 1][2]) / 16;
            tempImage[x][y][0] = r;
            tempImage[x][y][1] = g;
            tempImage[x][y][2] = b;
        }
    }
    imageData = tempImage;
    // ? <------------------------------------------ gaussian filter ----------------------------------------->

    // end the clock
    auto end = std::chrono::high_resolution_clock::now(); // End time
    std::chrono::duration<double> duration = end - start; // Calculate duration

    // print the time taken
    std::cout << "Time taken for sorting: " << duration.count() << " seconds" << std::endl;

    for (unsigned int x = 0; x < size.x; x++) {
        for (unsigned int y = 0; y < size.y; y++) {
            image.setPixel(x, y, sf::Color(imageData[x][y][0], imageData[x][y][1], imageData[x][y][2]));
        }
    }

    // turning array data back to image
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    sf::RenderWindow window(sf::VideoMode(size.x, size.y), "Image");

    // display image
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(sprite);
        window.display();
    }

}