// Resize an image by 50%.
#include "collection/resize_half.cpp"

int main() {
    // Load an image in jpg format.
    CImg<unsigned char> img("test_image.jpg");
    // Resize the image.
    CImg<unsigned char> img_resized = resize_image(img);
    // Save the resized image.
    img_resized.save("output/resized_image.jpg");
    return 0;
}