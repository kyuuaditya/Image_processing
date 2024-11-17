// * Author: Aditya Pratap Singh(kyuuaditya)
#include "CImg.h"
using namespace cimg_library;

int main() {
    // Load an image in jpg format.
    CImg<unsigned char> img("image.jpg");

    // Get the original image width and height.
    int width = img.width();
    int height = img.height();

    // Create a new image with half the original dimensions
    CImg<unsigned char> img_resized(width / 2, height / 2, 1, 3);

    // Get the resized image width and height
    int width_r = (int)img_resized.width();
    int height_r = (int)img_resized.height();

    // Loop through each color channel (R, G, B)
    for (int k = 0; k < 3; k++) {
        // Loop through the pixels of the resized image
        for (int i = 0; i < width_r; i++) {
            for (int j = 0; j < height_r; j++) {
                // Average the 2x2 pixel block from the original image
                // to compute the average color value
                img_resized(i, j, 0, k) =
                    (img(2 * i + 1, 2 * j + 1, 0, k) +
                     img(2 * i, 2 * j + 1, 0, k) + img(2 * i + 1, 2 * j, 0, k) +
                     img(2 * i, 2 * j, 0, k)) /
                    4;
            }
        }
    }

    // Save the resized image to a file
    img_resized.save("resized_image.jpg");
}