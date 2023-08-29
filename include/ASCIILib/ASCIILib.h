// ASCIILib
// 
// This lib is intended for you to easily
// pass a pixel array in and get an ascii image back

#include <math.h>
#include <stdlib.h>

int func();


typedef struct ASCIILib_Pixel {
    unsigned char red;
    unsigned char blue;
    unsigned char green;
} ASCIILib_Pixel;

typedef struct ASCIILib_Image {
    int width;
    int height;
    ASCIILib_Pixel** pixels;
} ASCIILib_Image;

// takes an image in and returns ascii
// arguments:
//   * int width_out  <- the requested width  of the ascii grid
//   * int height_out <- the requested height of the ascii grid
//   * ASCIILib_Image image <- the image to be converted into ascii art
// returns:
//   * a ascii image of the input dimensions
//     The returned values are rows of characters (of size width) from top to bottom
char** convertToASCII(int width_out, int height_out, ASCIILib_Image* image);

