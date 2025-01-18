#include <iostream>
#include <math.h>
#include "C:\mingw64\include\CImg.h"
using namespace cimg_library;

int main() {
    // import the image
    CImg<unsigned char> img("image.jpg");
    int w = img.width();
    int h = img.height();

    // create a window
    CImg<unsigned char> image(w, h, 1, 3);
    CImgDisplay display(image, "Glitch the Image");
    image.fill(0);

    float sx = 0.75; // scale in x-direction
    float sy = 0.75; // scale in y-direction
    float a = 0; // shear-x
    float b = 0; // shear-y
    int translate_x = w / 8;
    int translate_y = h / 8;
    float theta = 0; // rotation angle

    // temprary variables
    int cord_x = 0;
    int cord_y = 0;

    while (!display.is_closed()) {
        image.fill(0);
        int rotation = 1;

        float sinT = sin(theta);
        float cosT = cos(theta);
        float tanA = tan(a);
        float tanB = tan(b);

        // apply rgb shift
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                // shear -> scaling -> rotation(centre) -> translation
                cord_x = cosT * (i * (sx + sx * tanA * tanB) + sx * j * tanA - w / 4) - sinT * (sy * i * tanB + sy * j - h / 4) + w / 4 + translate_x;
                cord_y = sinT * (i * (sx + sx * tanA * tanB) + sx * j * tanA - w / 4) + cosT * (sy * i * tanB + sy * j - h / 4) + h / 4 + translate_y;

                // transform all rgb channels
                if (cord_x >= 0 && cord_x < w && cord_y >= 0 && cord_y < h) { // check if it's in canvas
                    image(cord_x, cord_y, 0) = img(i, j, 0);
                    image(cord_x, cord_y, 1) = img(i, j, 1);
                    image(cord_x, cord_y, 2) = img(i, j, 2);
                }
            }
        }


        // <-------------key events------------->
        if (display.is_keyARROWUP()) translate_y -= 1;
        if (display.is_keyARROWDOWN()) translate_y += 1;
        if (display.is_keyARROWLEFT()) translate_x -= 1;
        if (display.is_keyARROWRIGHT()) translate_x += 1;

        if (display.is_keyW()) {
            sx += 0.01;
            sy += 0.01;
        };
        if (display.is_keyS()) {
            sx -= 0.01;
            sy -= 0.01;
        };
        if (display.is_keyI()) sy -= 0.01;
        if (display.is_keyK()) sy += 0.01;
        if (display.is_keyJ()) sx -= 0.01;
        if (display.is_keyL()) sx += 0.01;

        if (display.is_keyD()) a += 0.01;
        if (display.is_keyA()) a -= 0.01;
        if (display.is_keyQ()) b += 0.01;
        if (display.is_keyE()) b -= 0.01;

        if (display.is_keyZ()) theta += 0.01;
        if (display.is_keyX()) theta -= 0.01;

        if (display.is_keyESC()) break;

        if (display.is_keyENTER()) {
            image.save("output.png");
            std::cout << "Image saved as output.jpg" << std::endl;
        }
        // <-------------key events------------->

        image.display(display);
    }
    return 0;
}