// ASCIILib
// 
// This lib is intended for you to easily
// pass a pixel array in and get an ascii image back

#include <stdlib.h>
#include <stdint.h>

#include <math.h>

typedef struct ASCIILib_Pixel {
    uint8_t red;
    uint8_t blue;
    uint8_t green;
} ASCIILib_Pixel;

typedef struct ASCIILib_Image {
    size_t width;
    size_t height;
    ASCIILib_Pixel** pixels;
} ASCIILib_Image;

// takes an image in and returns ascii of the specified size
// arguments:
//   * int width_out  <- the requested width  of the ascii grid
//   * int height_out <- the requested height of the ascii grid
//   * ASCIILib_Image image <- the image to be converted into ascii art
// returns:
//   * a ascii image of the input dimensions
//     The returned values are rows of characters (of size width) from top to bottom
char** convertToASCII(int width_out, int height_out, ASCIILib_Image* image);

size_t AsciiArtTextBufSize(size_t width, size_t height);
void convertGreyScaleToASCII(uint8_t* image, size_t width, size_t height, char* return_text);

