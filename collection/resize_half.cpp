#include "CImg.h"
using namespace cimg_library;
CImg<unsigned char> resize_image(const CImg<unsigned char>& img) {
    // Get the original image width and height.
    int width = img.width();
    int height = img.height();

    // Create a new image with half the original dimensions
    CImg<unsigned char> img_resized(width / 2, height / 2, 1, 3);

    // Loop through each color channel (R, G, B)
    for (int k = 0; k < 3; k++) {
        // Loop through the pixels of the resized image
        for (int i = 0; i < img_resized.width(); i++) {
            for (int j = 0; j < img_resized.height(); j++) {
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

    return img_resized;
}