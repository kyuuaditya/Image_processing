#include <iostream>
#include <math.h>
#include "C:\mingw64\include\CImg.h"
using namespace cimg_library;

int main() {
    CImg<unsigned char> img("image.jpg");
    int w = img.width();
    int h = img.height();

    // create a window
    CImg<unsigned char> image(w, h, 1, 3);
    CImgDisplay display(image, "Glitch the Image");
    image.fill(0);

    float scale = 1;
    float sx = 1;
    float sy = 1;
    float a = 0;
    float b = 0;
    int translate_x = 0;
    int translate_y = 0;
    float theta = 0;
    int cord_x = 0;
    int cord_y = 0;

    std::cout << sin(theta) << std::endl;
    std::cout << cos(theta) << std::endl;

    while (!display.is_closed()) {
        image.fill(0);

        float sinT = sin(theta);
        float cosT = cos(theta);
        float tanA = tan(a);
        float tanB = tan(b);

        // apply rgb shift
        for (int i = 0; i < w; i++) {
            for (int j = 0; j < h; j++) {
                // cord_x = (int)((float)(scale * i + a * j + translate_x) * cosT - (float)(b * i + scale * j + translate_y) * sinT);
                // cord_y = (int)((float)(b * i + scale * j + translate_y) * cosT + (float)(scale * i + a * j + translate_x) * sinT);
                // cord_x = (int)(scale * i + a * j + translate_x);
                // cord_y = (int)(b * i + scale * j + translate_y);

                // // shear only
                // cord_x = i * (tanA * tanB + 1) + j * tanA;
                // cord_y = i * tanB + j;

                // // shear -> scaling
                // cord_x = i * (sx + sx * tanA * tanB) + sx * j * tanA;
                // cord_y = sy * i * tanB + sy * j;

                // // shear -> scaling -> rotation
                // cord_x = i * (sx * cosT + tanB * (sx * tanA * cosT - sy * sinT)) + j * (sx * tanA * cosT - sy * sinT);
                // cord_y = i * (sx * sinT + tanB * (sx * tanA * sinT + sy * cosT)) + j * (sy * cosT + sx * tanA * sinT);

                // shear -> scaling -> rotation(centre)
                cord_x = cosT * (i * (sx + sx * tanA * tanB) + sx * j * tanA - w / 2) - sinT * (sy * i * tanB + sy * j - h / 2) + w / 2 + translate_x;
                cord_y = sinT * (i * (sx + sx * tanA * tanB) + sx * j * tanA - w / 2) + cosT * (sy * i * tanB + sy * j - h / 2) + h / 2 + translate_y;

                if (cord_x >= 0 && cord_x < w && cord_y >= 0 && cord_y < h) {
                    image(cord_x, cord_y, 0) = img(i, j, 0);
                    image(cord_x, cord_y, 1) = img(i, j, 1);
                    image(cord_x, cord_y, 2) = img(i, j, 2);
                }
            }
        }


        // <-------------key events------------->
        if (display.is_keyARROWUP()) {
            translate_y -= 1;
        };
        if (display.is_keyARROWDOWN()) {
            translate_y += 1;
        };
        if (display.is_keyARROWLEFT()) {
            translate_x -= 1;
        };
        if (display.is_keyARROWRIGHT()) {
            translate_x += 1;
        };

        if (display.is_keyW()) {
            scale += 0.01;
            sx += 0.01;
            sy += 0.01;
        };
        if (display.is_keyS()) {
            scale -= 0.01;
            sx -= 0.01;
            sy -= 0.01;
        };
        if (display.is_keyI()) sx += 0.01;
        if (display.is_keyK()) sx -= 0.01;
        if (display.is_keyJ()) sy += 0.01;
        if (display.is_keyL()) sy -= 0.01;

        if (display.is_keyD()) a += 0.01;
        if (display.is_keyA()) a -= 0.01;

        if (display.is_keyQ()) b += 0.01;
        if (display.is_keyE()) b -= 0.01;

        if (display.is_keyZ()) theta += 0.01;
        if (display.is_keyX()) theta -= 0.01;

        if (display.is_keyESC()) break;

        if (display.is_keyENTER()) {
            image.save("output.jpg");
            std::cout << "Image saved as output.jpg" << std::endl;
        }
        // <-------------key events------------->

        image.display(display);
    }
    return 0;
}