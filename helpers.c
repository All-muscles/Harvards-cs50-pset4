#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // loop over each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // calculate the average of the rgb in each pixel

            int color = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            
            image[i][j].rgbtRed = color;
            image[i][j].rgbtGreen = color;
            image[i][j].rgbtBlue = color;
        }   
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            /*
            sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue

            sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue

            sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
            */

            int originalRed = image[i][j].rgbtRed;
            int originalGreen = image[i][j].rgbtGreen;
            int originalBlue = image[i][j].rgbtBlue;

            int sepia_red = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int sepia_green = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int sepia_blue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            if (sepia_red > 255)
            {
                sepia_red = 255;
            }
            if (sepia_green > 255)
            {
                sepia_green = 255;
            }
            if (sepia_blue > 255)
            {
                sepia_blue = 255;
            }

            image[i][j].rgbtRed = sepia_red;
            image[i][j].rgbtGreen = sepia_green;
            image[i][j].rgbtBlue = sepia_blue;
        }  
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, half = width / 2; j < half; j++)
        {
            // swap pixels from left to right, we could just create a new array which would be a simpler approach but efficiency wise this is the best way around

            // make a temporary variable to store 
            RGBTRIPLE tmp;
            tmp.rgbtRed = image[i][j].rgbtRed;
            tmp.rgbtGreen = image[i][j].rgbtGreen;
            tmp.rgbtBlue = image[i][j].rgbtBlue;

            // change the value of the variable we have  a copy of 
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;

            // put the value of the copy in the right variable
            image[i][width - 1 - j].rgbtRed = tmp.rgbtRed;
            image[i][width - 1 - j].rgbtGreen = tmp.rgbtGreen;
            image[i][width - 1 - j].rgbtBlue = tmp.rgbtBlue;
        } 
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // an array to copy each pixel that has been blurred to
    RGBTRIPLE copy[height][width];

    // go through each pixel
    for (int pixel_row = 0; pixel_row < height; pixel_row++)
    {
        for (int pixel_coloumn = 0; pixel_coloumn < width; pixel_coloumn++)
        {
            // the main image is our reference and we will write the blurred image onto the copy array, then at the end will copy the copy into the original image array
            int totalRed = 0, totalGreen = 0, totalBlue = 0, count = 0;

            for (int row_off_set = -1; row_off_set <= 1; row_off_set++)
            {
                for (int column_off_set = -1; column_off_set <= 1; column_off_set++)
                {
                    int neighbor_row = row_off_set + pixel_row;
                    int neighbor_column = column_off_set + pixel_coloumn;

                    // checks if tht neighbor_row and neighbor_column are not out of bound
                    if (neighbor_row >= 0 && neighbor_row < height && neighbor_column >= 0 && neighbor_column < width)
                    {
                        totalRed += image[neighbor_row][neighbor_column].rgbtRed;
                        totalGreen += image[neighbor_row][neighbor_column].rgbtGreen;
                        totalBlue += image[neighbor_row][neighbor_column].rgbtBlue;
                        count++;
                    } 
                }
            }

            copy[pixel_row][pixel_coloumn].rgbtRed = round((float) totalRed / count);
            copy[pixel_row][pixel_coloumn].rgbtGreen = round((float) totalGreen / count);
            copy[pixel_row][pixel_coloumn].rgbtBlue = round((float) totalBlue / count);
        }
    }

    // copy the copy array into the image array
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copy[i][j].rgbtRed;
            image[i][j].rgbtGreen = copy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = copy[i][j].rgbtBlue;
        }
    }
}
