/**
 * @file borderColorPicker.cpp
 * @description Implements the BorderColorPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "borderColorPicker.h"

/**
 * Constructs a new BorderColorPicker.
 *
 * @param width        Number of pixels to color around border.
 * @param inputimage   Image for referencing original image colors.
 * @param bcolor       Color to be used for painting the fill border.
 * @param tol          Tolerance used to determine the border of the fill.
 */
BorderColorPicker::BorderColorPicker(unsigned int width, PNG &inputimage, RGBAPixel scolor, RGBAPixel bcolor, double tol)
{
    // Complete your implementation below
    borderwidth = width;
    img = inputimage;
    seedcolor = scolor;
    bordercolor = bcolor;
    tolerance = tol;
}

/**
 * Picks the color for pixel at point. If the x or y coordinate is
 * at or within an Euclidean radius of borderwidth pixels from the border of
 * the fill region, it will be colored with the required border color.
 * Otherwise, its color will not be changed.
 *
 * @param p   The point for which you're picking a color.
 * @return    The color chosen for (p).
 */
RGBAPixel BorderColorPicker::operator()(PixelPoint p)
{
    RGBAPixel refColor = *(img.getPixel(p.x, p.y));

    if (seedcolor.distanceTo(refColor) > tolerance) {
        return refColor;
    }

    if (img.width() - p.x <= borderwidth || p.x < borderwidth || img.height() - p.y <= borderwidth || p.y < borderwidth) {
        return bordercolor;
    }

    for (unsigned i = p.x - borderwidth; i <= p.x + borderwidth; i++)
    {
        for (unsigned j = p.y - borderwidth; j <= p.y + borderwidth; j++)
        {
            double distance = (i - p.x) * (i - p.x) + (j - p.y) * (j - p.y);
            if (distance <= borderwidth * borderwidth)
            {
                RGBAPixel *point = img.getPixel(i, j);
                if (seedcolor.distanceTo(*point) > tolerance) {
                    return bordercolor;
                }
            }
        }
    }

    return refColor;
}


/**
 * Add your private BorderColorPicker function implementations below
 */
