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

            image[i][j].rgbtRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            image[i][j].rgbtGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            image[i][j].rgbtBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);
        }  
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
