#include <iostream>

#include "CImg.h"
using namespace cimg_library;

int main() {
    CImg<unsigned char> img("image.jpg");
    // 800x600 image with 3 color channels (RGB)
    // CImgDisplay display(img, "Final_image");

    int width = img.width();
    int height = img.height();
    // int height = 800;
    // int width = 800;

    std::cout << width << " " << height << std::endl;

    // int a = 107;
    // int b = 29;
    // int a = 5;
    // int b = 8;

    CImg<unsigned char> img_resized(width / 2, height / 2, 1, 3);

    int width_r = (int)img_resized.width();
    int height_r = (int)img_resized.height();
    // each character is 19 by 9 in size
    // std::cout << "a";
    // int img_resized_a[height_r][width_r][3] = {0};

    // for (int k = 0; k < 3; k++) {
    //     for (int i = 0; i < height_r; i++) {
    //         for (int j = 0; j < width_r; j++) {
    //             img_resized_a[i][j][k] = 0;
    //         }
    //     }
    // }

    // std::cout << "█ █ █ █" << std::endl;
    // std::cout << " █ █ █ █" << std::endl;
    // std::cout << "█ █ █ █" << std::endl;

    // while (1) {
    // for (int k = 0; k < 3; k++) {
    //     for (int i = 0; i < height; i++) {
    //         for (int j = 0; j < width; j++) {
    //             img_resized_a[i / (2)][j / (2)][k] += img(i, j, 0, k);
    //         }
    //     }
    // }

    for (int k = 0; k < 3; k++) {
        for (int i = 0; i < width_r; i++) {
            for (int j = 0; j < height_r; j++) {
                // std::cout << j << std::endl;
                img_resized(i, j, 0, k) =
                    (img(2 * i, 2 * j, 0, k) + img(2 * i, 2 * j + 1, 0, k) +
                     img(2 * i + 1, 2 * j, 0, k) +
                     img(2 * i + 1, 2 * j + 1, 0, k)) /
                    4;
            }
        }
    }

    // for (int k = 0; k < 3; k++) {
    //     for (int i = 0; i < height / 2; i++) {
    //         for (int j = 0; j < width / 2; j++) {
    //             // canvas[i / (2)][j / (2)][k] += img(i, j, k);
    //             img_resized(i, j, 0, k) =
    //                 static_cast<int>(img_resized_a[i][j][k]);
    //             // img_resized(i, j, 0, 1) =
    //             static_cast<int>(canvas[i][j][1]);
    //             // img_resized(i, j, 0, 2) =
    //             static_cast<int>(canvas[i][j][2]);
    //         }
    //     }
    // }

    CImgDisplay draw_img_resized(img_resized, "image_resized");

    while (!draw_img_resized.is_closed()) {
        draw_img_resized.wait();
    }

    img_resized.save("img_resized.jpg");

    // std::cout << "5" << std::endl;
    // }
}