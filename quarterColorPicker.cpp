/**
 * @file quarterColorPicker.cpp
 * @description Implements the QuarterColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "quarterColorPicker.h"

QuarterColorPicker::QuarterColorPicker(PNG &inputimg, unsigned char b_amount)
{
    // Complete your implementation below
    referenceimg = inputimg;
    brightamount = b_amount;
}

/**
 * Picks the color for pixel (x, y).
 *
 * Using the private reference image, scale each dimension by half
 * and tile the smaller image in a 2 x 2 grid over the original dimensions
 * of the image, and return the pixel at the appropriate coordinate from
 * the tiled image, brightened on each R/G/B channel by the required amount.
 *
 * The value of each pixel in the scaled image will be a bilinear interpolation
 * of a 2x2 pixel region from the original image, with each of the R/G/B/A channels
 * processed individually. Interpolate over the x-axis before the y-axis.
 * Truncate any fractional values on the R/G/B channels. Brighten each color channel
 * as the final step.
 *
 * @pre referenceimg width and height are both even
 */
RGBAPixel QuarterColorPicker::operator()(PixelPoint p) {

    unsigned int adjustedX = p.x % (referenceimg.width() / 2);
    unsigned int adjustedY = p.y % (referenceimg.height() / 2);

    // Establish the original image coordinates for sampling.
    unsigned int originalX = adjustedX * 2;
    unsigned int originalY = adjustedY * 2;

    // Acquire the four adjacent pixels to perform the averaging.
    RGBAPixel* topLeftPixel = referenceimg.getPixel(originalX, originalY);
    RGBAPixel* topRightPixel = referenceimg.getPixel(originalX + 1, originalY);
    RGBAPixel* bottomLeftPixel = referenceimg.getPixel(originalX, originalY + 1);
    RGBAPixel* bottomRightPixel = referenceimg.getPixel(originalX + 1, originalY + 1);

    RGBAPixel result;
    // Average the RGB values of the acquired pixels.
    result.r = ((topLeftPixel->r + topRightPixel->r)/2 + (bottomLeftPixel->r + bottomRightPixel->r)/2)/2;
    result.g = ((topLeftPixel->g + topRightPixel->g)/2 + (bottomLeftPixel->g + bottomRightPixel->g)/2)/2;
    result.b = ((topLeftPixel->b + topRightPixel->b)/2 + (bottomLeftPixel->b + bottomRightPixel->b)/2)/2;
    // Directly use the alpha value from the top-left pixel.
    result.a = topLeftPixel->a;

    // Implement the brightening effect on the resulting color.
    result.r = std::min(255, result.r + brightamount);
    result.g = std::min(255, result.g + brightamount);
    result.b = std::min(255, result.b + brightamount);

    return result;
}



/**
 * Add your private QuarterColorPicker function implementations below
 */