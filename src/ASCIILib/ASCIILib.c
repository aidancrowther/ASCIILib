#include "ASCIILib/ASCIILib.h"

void cleanUpImage(ASCIILib_Image* image) {
    for (int h=0; h<image->height; h++)
        free(image->pixels[h]);
    free(image->pixels);
    free(image);
}

void downscaleImage(ASCIILib_Image* image, int new_width, int new_height){
    ASCIILib_Image downscaledImage;
    downscaledImage.height = new_height;
    downscaledImage.width = new_width;
    int block_height = image->height / new_height;
    int block_width = image->width / new_width;
    downscaledImage.pixels = malloc(sizeof(ASCIILib_Pixel*) * new_height);

    for (int h=0; h<new_height; h++){
        downscaledImage.pixels[h] = malloc(sizeof(ASCIILib_Pixel) * new_width);
        for (int w=0; w<new_width; w++){
            int sum_red   = 0,
                sum_green = 0,
                sum_blue  = 0;
            int pixel_count;
            pixel_count = 0;

            int start_height = h * block_height;
            int next_height  = (h * block_height) + block_height;
            if (next_height > image->height) next_height = image->height;
            for (int bh=start_height; bh < next_height; bh++) {
                int start_width = w * block_width;
                int next_width  = (w * block_width) + block_width;
                if (next_width > image->width) next_width = image->width;
                for (int bw=start_width; bw < next_width; bw++) {
                    ASCIILib_Pixel* pixel = &(image->pixels[bh][bw]);
                    sum_red   += pixel->red;
                    sum_green += pixel->green;
                    sum_blue  += pixel->blue;
                    pixel_count++;
                }
            }

            ASCIILib_Pixel* pixel = &(downscaledImage.pixels[h][w]);
            if (pixel_count>0) {
                pixel->red   = sum_red   / pixel_count;
                pixel->green = sum_green / pixel_count;
                pixel->blue  = sum_blue  / pixel_count;
            } else {
                pixel->red   = 0;
                pixel->green = 0;
                pixel->blue  = 0;
            }
        }
    }

    //cleanUpImage(image);
    for (int h=0; h<image->height; h++)
        free(image->pixels[h]);
    free(image->pixels);

    image->height = downscaledImage.height;
    image->width  = downscaledImage.width;
    image->pixels = downscaledImage.pixels;
}

unsigned char convertPixelToBlackAndWhite(ASCIILib_Pixel* pixel) {
    // the const literals are luma values
    unsigned char grey = ((double)pixel->red   * 0.2126) ///3) //
                       + ((double)pixel->green * 0.7152) ///3) //
                       + ((double)pixel->blue  * 0.0722);///3);//
    return grey;
}

// converts the image in the container to black and white
// this changes the contents of the structure given
void convertImageToBlackAndWhite(ASCIILib_Image* image) {
    for (int h=0; h<image->height; h++)
        for (int w=0; w<image->width; w++) {
            ASCIILib_Pixel* pixel = &(image->pixels[h][w]);
            unsigned char grey = convertPixelToBlackAndWhite(pixel);
            pixel->red   = grey;
            pixel->green = grey;
            pixel->blue  = grey;
        }
}

char getCharacterForGreyScale(unsigned char grey) {
    // This is the scale of darkest ascii characters to lightest
    const char* ascii_scale = "$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,\"^`'.";
    const int ascii_scale_size = 69;

    float grey_f = (float)grey / 255.0;
    char ascii = ascii_scale[(size_t)(grey_f * (ascii_scale_size-1))];
    return ascii;
}

char** convertToASCII(int width_out, int height_out, ASCIILib_Image* image){
    char** ASCIIImage = malloc(sizeof(char*) * height_out);
    for (int row=0; row<height_out; row++)
        ASCIIImage[row] = malloc(sizeof(char) * (width_out+1));

    //convertImageToBlackAndWhite(image);
    downscaleImage(image, width_out, height_out);

    for (int h=0; h<image->height; h++) {
        for (int w=0; w<image->width; w++) {
            ASCIILib_Pixel* pixel = &(image->pixels[h][w]);
            unsigned char grey = convertPixelToBlackAndWhite(pixel);
            char ASCII_char = getCharacterForGreyScale(grey);

            ASCIIImage[h][w] = ASCII_char;
        }
        ASCIIImage[h][width_out] = '\0';
    }

    return ASCIIImage;
}

size_t AsciiArtTextBufSize(size_t width, size_t height){
    return (width * height) // text grid
                + height    // plus a new line for every row
                + 1;        // plus a null term ('\0') to terminate the string
}

void convertGreyScaleToASCII(uint8_t* image, size_t width, size_t height, char* return_text) {
    size_t i = 0;
    for (size_t h=0; h < height; h++) {
        for (size_t w=0; w < width; w++) {
            return_text[i] = getCharacterForGreyScale(image[i]);
            i++;
        }
        i++;
        return_text[i] = '\n';
    }
    return_text[(width*height) + height] = '\0';
}
