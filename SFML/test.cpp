#include <sfml/Graphics.hpp>
#include <iostream>
#include <vector>
// #include <math.h>
#include <cmath>
#include <chrono>

#define M_PI 3.14159265358979323846

// Function to generate a Gaussian kernel
std::vector<std::vector<double>> generateGaussianKernel(int size, double sigma) {
    std::vector<std::vector<double>> kernel(size, std::vector<double>(size));
    double sum = 0.0;
    int halfSize = size / 2;

    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            double value = (double)((1 / (2 * M_PI * sigma * sigma)) * exp(-((x - halfSize) * (x - halfSize) + (y - halfSize) * (y - halfSize)) / (2 * sigma * sigma)));
            kernel[x][y] = value;
            sum += value;
        }
    }

    for (int i = 0; i < size; i++) { // Normalizing the kernel
        for (int j = 0; j < size; j++) {
            kernel[i][j] /= sum;
        }
    }

    for (int i = 0;i < size;i++) { // Displaying the kernel
        for (int j = 0;j < size;j++) {
            std::cout << kernel[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return kernel;
}

// Applying Gaussian blur to the image
void applyGaussianBlur(std::vector<std::vector<std::vector<int>>>& imageData, int sizeX, int sizeY, double sigma, int padding) {
    int kernelSize = 2 * int(padding / 2) + 1; // You can change this to any odd number
    std::vector<std::vector<double>> kernel = generateGaussianKernel(kernelSize, sigma);
    std::vector<std::vector<std::vector<int>>> tempImageGaus = imageData;

    int halfSize = kernelSize / 2;
    for (unsigned int x = padding; x < sizeX - padding; x++) {
        for (unsigned int y = padding; y < sizeY - padding; y++) {
            int r = 0, g = 0, b = 0;
            for (int i = 0; i < kernelSize; i++) {
                for (int j = 0; j <= kernelSize; j++) {
                    r += imageData[x - halfSize + i][y - halfSize + j][0] * kernel[i][j];
                    g += imageData[x - halfSize + i][y - halfSize + j][1] * kernel[i][j];
                    b += imageData[x - halfSize + i][y - halfSize + j][2] * kernel[i][j];
                }
            }
            tempImageGaus[x][y][0] = static_cast<int>(r);
            tempImageGaus[x][y][1] = static_cast<int>(g);
            tempImageGaus[x][y][2] = static_cast<int>(b);
        }
    }
    imageData = tempImageGaus;
}

int main() {
    // Load an image file
    sf::Image image;
    if (!image.loadFromFile("12345.jpg")) {
        std::cerr << "Failed to load image" << std::endl;
        return -1;
    }

    // Get image size
    sf::Vector2u size = image.getSize();
    std::cout << "Image size: " << size.x << "x" << size.y << std::endl;

    int padding = 6;
    std::vector<std::vector<std::vector<int>>> imageData(size.x + padding, std::vector<std::vector<int>>(size.y + padding, std::vector<int>(3)));
    std::vector<std::vector<std::vector<int>>> imageData_noPadding(size.x, std::vector<std::vector<int>>(size.y, std::vector<int>(3)));
    std::vector<std::vector<std::vector<int>>> tempImage(size.x + padding, std::vector<std::vector<int>>(size.y + padding, std::vector<int>(3)));

    // reading image data and sending it to an array
    for (unsigned int x = padding / 2; x < size.x + padding / 2; x++) {
        for (unsigned int y = padding / 2; y < size.y + padding / 2; y++) {
            sf::Color pixel = image.getPixel(x - padding / 2, y - padding / 2); // get pixel color
            imageData[x][y][0] = pixel.r;
            imageData[x][y][1] = pixel.g;
            imageData[x][y][2] = pixel.b;
        }
    }

    auto start = std::chrono::high_resolution_clock::now(); // Start time

    // ! <------------------------------------------ sobel filter ----------------------------------------->
    // // 3x3 kernel    1  0 -1    -1 -2 -1
    // //               2  0 -2     0  0  0
    // //               1  0 -1     1  2  1
    // // applying sobel filter to the image
    // for (unsigned int x = 1; x < size.x - 1; ++x) {
    //     for (unsigned int y = 1; y < size.y - 1; ++y) {
    //         int gx = imageData[x - 1][y - 1][0] + 2 * imageData[x - 1][y][0] + imageData[x - 1][y + 1][0] - imageData[x + 1][y - 1][0] - 2 * imageData[x + 1][y][0] - imageData[x + 1][y + 1][0];
    //         int gy = imageData[x - 1][y - 1][0] + 2 * imageData[x][y - 1][0] + imageData[x + 1][y - 1][0] - imageData[x - 1][y + 1][0] - 2 * imageData[x][y + 1][0] - imageData[x + 1][y + 1][0];
    //         int g = sqrt(gx * gx + gy * gy);
    //         image.setPixel(x, y, sf::Color(g, g, g));
    //         tempImage[x][y][0] = g;
    //         tempImage[x][y][1] = g;
    //         tempImage[x][y][2] = g;
    //     }
    // }
    // imageData = tempImage;
    // ! <------------------------------------------ sobel filter ----------------------------------------->

    // TODO <------------------------------------------ gaussian filter (constant kernel) ----------------------------------------->
    double sigma = 1.0; // You can change this value
    tempImage = imageData;
    applyGaussianBlur(imageData, size.x, size.y, sigma, padding);
    sigma = 2.0;
    applyGaussianBlur(tempImage, size.x, size.y, sigma, padding);

    for (unsigned int x = 0; x < size.x; x++) {
        for (unsigned int y = 0; y < size.y; y++) {
            imageData[x][y][0] = abs(imageData[x][y][0] - tempImage[x][y][0]);
            imageData[x][y][1] = abs(imageData[x][y][1] - tempImage[x][y][1]);
            imageData[x][y][2] = abs(imageData[x][y][2] - tempImage[x][y][2]);
        }
    }
    // TODO <------------------------------------------ gaussian filter (constant kernel) ----------------------------------------->

    // ! <------------------------------------------ clock ----------------------------------------->
    auto end = std::chrono::high_resolution_clock::now(); // End time
    std::chrono::duration<double> duration = end - start; // Calculate duration

    std::cout << "Time taken by filter: " << duration.count() << " seconds" << std::endl;
    // ! <------------------------------------------ clock ----------------------------------------->

    // ? <-----------------------------------turning array data back to image---------------------------------------------->
    for (unsigned int x = 0; x < size.x; x++) {
        for (unsigned int y = 0; y < size.y; y++) {
            imageData_noPadding[x][y][0] = 255 - imageData[x + padding / 2][y + padding / 2][0];
            imageData_noPadding[x][y][1] = 255 - imageData[x + padding / 2][y + padding / 2][1];
            imageData_noPadding[x][y][2] = 255 - imageData[x + padding / 2][y + padding / 2][2];
        }
    }

    for (unsigned int x = 0; x < size.x; x++) {
        for (unsigned int y = 0; y < size.y; y++) {
            image.setPixel(x, y, sf::Color(imageData_noPadding[x][y][0], imageData_noPadding[x][y][1], imageData_noPadding[x][y][2]));
        }
    }

    // Save the image to a file
    if (!image.saveToFile("output.png")) {
        std::cerr << "Failed to save image" << std::endl;
    }

    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    sf::RenderWindow window(sf::VideoMode(size.x, size.y), "Image");
    // ? <-----------------------------------turning array data back to image---------------------------------------------->
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
        window.close();
    }

}