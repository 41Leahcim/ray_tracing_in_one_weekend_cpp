#include <iostream>

int main(){
    // Image properties
    const int IMAGE_WIDTH = 256;
    const int IMAGE_HEIGHT = 256;

    // Rendering
    std::cout << "P3\n" << IMAGE_WIDTH << ' ' << IMAGE_HEIGHT << "\n255\n";

    for(int y = IMAGE_HEIGHT - 1;y >= 0;y--){
        for(int x = 0;x < IMAGE_HEIGHT;x++){
            double red_double = static_cast<double>(x) / (IMAGE_WIDTH - 1);
            double green_double = static_cast<double>(y) / (IMAGE_HEIGHT - 1);
            double blue_double = 0.25;

            int red_int = static_cast<int>(255.999 * red_double);
            int green_int = static_cast<int>(255.999 * green_double);
            int blue_int = static_cast<int>(255.999 * blue_double);

            std::cout << red_int << ' ' << green_int << ' ' << blue_int << '\n';
        }
    }
}
