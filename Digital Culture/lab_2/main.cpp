#include <iostream>
#include <cmath>
#include <vector>

#include "bitmap_image.hpp"

using namespace std;

int main(){
    vector<vector<int> > img_array(128, (vector<int>(128)));

    bitmap_image image("img.bmp");
    for (int x = 0; x < image.width(); x++)
    {
        for (int y = 0; y < image.height(); y++)
        {
            rgb_t color;
            image.get_pixel(x, y, color.blue, color.red, color.green);
            img_array[x][y] = color.red;
        }
    }

    cout << "Middle string of image \n\n";
    for (int i = 0; i < 128; i++)
        cout << img_array[i][64] << ' ';
    cout << endl;

    vector<int> color_frequency(261);
    for (int i = 0; i < 261; i++)
        color_frequency[i] = 0;


    cout << "\n\nQuantized middle string of image \n\n";
    for (int i = 0; i < 128; i++)
    {
        img_array[i][64] = round(double(img_array[i][64]) / 20) * 20;
        color_frequency[img_array[i][64]]++;
        cout << img_array[i][64] << ' ';
    }
    cout << endl;

    cout << "\n\nEntropy \n\n";
    double entropy = 0;
    for (int i = 0; i < 261; i++){
        if (color_frequency[i] > 0){
            cout << i << ' ' << color_frequency[i] << endl;
            entropy = entropy - (double(color_frequency[i]) / 128) * log2(double(color_frequency[i]) / 128);
        }
    }
    cout << entropy << "\n";


}
