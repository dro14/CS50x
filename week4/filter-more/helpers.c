// This is the program for applying filters on BMP images.
// It can convert an image to grayscale and sepia, reflect it horizontally, and blur the image.
#include "helpers.h"



// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    uint8_t originalRed;
    uint8_t originalGreen;
    uint8_t originalBlue;
    uint8_t average;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;

            average = round((originalRed + originalGreen + originalBlue) / 3.0);   // Calculating average value

            image[i][j].rgbtRed = average;   // Assigning average value
            image[i][j].rgbtGreen = average;   // Assigning average value
            image[i][j].rgbtBlue = average;   // Assigning average value
        }
    }
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Calculating the half of the width so that not to make one half of the image to reflect the other half
    int half_width = width / 2;
    uint8_t originalRed;
    uint8_t originalGreen;
    uint8_t originalBlue;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < half_width; j++)
        {
            originalRed = image[i][j].rgbtRed;   // Swapping red color values
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtRed = originalRed;

            originalGreen = image[i][j].rgbtGreen;   // Swapping green color values
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][width - 1 - j].rgbtGreen = originalGreen;

            originalBlue = image[i][j].rgbtBlue;   // Swapping blue color values
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtBlue = originalBlue;
        }
    }
}


// Finding the average value of a given grid
void findAverage(int height, int width, int i, int j, uint8_t originalMatrix[height][width], uint8_t blurredMatrix[height][width])
{
    int sum = 0;
    uint8_t average;

    if (i == 0 && j == 0)   // In the top-left corner
    {
        sum += originalMatrix[i][j];   // 2 rows and 2 columns
        sum += originalMatrix[i][j + 1];
        sum += originalMatrix[i + 1][j];
        sum += originalMatrix[i + 1][j + 1];

        average = round(sum / 4.0);
        blurredMatrix[i][j] = average;   // Assigning the calculated average value to a different matrix
    }
    else if (i == 0 && j == width - 1)   // In the top-right corner
    {
        sum += originalMatrix[i][j - 1];   // 2 rows and 2 columns
        sum += originalMatrix[i][j];
        sum += originalMatrix[i + 1][j - 1];
        sum += originalMatrix[i + 1][j];

        average = round(sum / 4.0);
        blurredMatrix[i][j] = average;   // Assigning the calculated average value to a different matrix
    }
    else if (i == height - 1 && j == 0)   // In the bottom-left corner
    {
        sum += originalMatrix[i - 1][j];    // 2 rows and 2 columns
        sum += originalMatrix[i - 1][j + 1];
        sum += originalMatrix[i][j];
        sum += originalMatrix[i][j + 1];

        average = round(sum / 4.0);
        blurredMatrix[i][j] = average;   // Assigning the calculated average value to a different matrix
    }
    else if (i == height - 1 && j == width - 1)   // In the bottom-right corner
    {
        sum += originalMatrix[i - 1][j - 1];   // 2 rows and 2 columns
        sum += originalMatrix[i - 1][j];
        sum += originalMatrix[i][j - 1];
        sum += originalMatrix[i][j];

        average = round(sum / 4.0);
        blurredMatrix[i][j] = average;   // Assigning the calculated average value to a different matrix
    }
    else if (i == 0)   // On the top edge
    {
        sum += originalMatrix[i][j - 1];   // 2 rows and 3 columns
        sum += originalMatrix[i][j];
        sum += originalMatrix[i][j + 1];
        sum += originalMatrix[i + 1][j - 1];
        sum += originalMatrix[i + 1][j];
        sum += originalMatrix[i + 1][j + 1];

        average = round(sum / 6.0);
        blurredMatrix[i][j] = average;   // Assigning the calculated average value to a different matrix
    }
    else if (j == 0)   // On the left edge
    {
        sum += originalMatrix[i - 1][j];   // 3 rows and 2 columns
        sum += originalMatrix[i - 1][j + 1];
        sum += originalMatrix[i][j];
        sum += originalMatrix[i][j + 1];
        sum += originalMatrix[i + 1][j];
        sum += originalMatrix[i + 1][j + 1];

        average = round(sum / 6.0);
        blurredMatrix[i][j] = average;   // Assigning the calculated average value to a different matrix
    }
    else if (j == width - 1)   // On the right edge
    {
        sum += originalMatrix[i - 1][j - 1];   // 3 rows and 2 columns
        sum += originalMatrix[i - 1][j];
        sum += originalMatrix[i][j - 1];
        sum += originalMatrix[i][j];
        sum += originalMatrix[i + 1][j - 1];
        sum += originalMatrix[i + 1][j];

        average = round(sum / 6.0);
        blurredMatrix[i][j] = average;   // Assigning the calculated average value to a different matrix
    }
    else if (i == height - 1)   // On the bottom edge
    {
        sum += originalMatrix[i - 1][j - 1];   // 2 rows and 3 columns
        sum += originalMatrix[i - 1][j];
        sum += originalMatrix[i - 1][j + 1];
        sum += originalMatrix[i][j - 1];
        sum += originalMatrix[i][j];
        sum += originalMatrix[i][j + 1];

        average = round(sum / 6.0);
        blurredMatrix[i][j] = average;   // Assigning the calculated average value to a different matrix
    }
    else   // In the middle
    {
        sum += originalMatrix[i - 1][j - 1];    // 3 rows and 3 columns
        sum += originalMatrix[i - 1][j];
        sum += originalMatrix[i - 1][j + 1];
        sum += originalMatrix[i][j - 1];
        sum += originalMatrix[i][j];
        sum += originalMatrix[i][j + 1];
        sum += originalMatrix[i + 1][j - 1];
        sum += originalMatrix[i + 1][j];
        sum += originalMatrix[i + 1][j + 1];

        average = round(sum / 9.0);
        blurredMatrix[i][j] = average;   // Assigning the calculated average value to a different matrix
    }
}


// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    uint8_t originalRedMatrix[height][width];
    uint8_t originalGreenMatrix[height][width];
    uint8_t originalBlueMatrix[height][width];
    uint8_t blurredRedMatrix[height][width];
    uint8_t blurredGreenMatrix[height][width];
    uint8_t blurredBlueMatrix[height][width];

    // Copying image color value into three separate matrices,
    // manipulation with them easier
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRedMatrix[i][j] = image[i][j].rgbtRed;
            originalGreenMatrix[i][j] = image[i][j].rgbtGreen;
            originalBlueMatrix[i][j] = image[i][j].rgbtBlue;
        }
    }

    // Calculating average color value for each pixel and saving it into different matrices
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            findAverage(height, width, i, j, originalRedMatrix, blurredRedMatrix);
            findAverage(height, width, i, j, originalGreenMatrix, blurredGreenMatrix);
            findAverage(height, width, i, j, originalBlueMatrix, blurredBlueMatrix);
        }
    }

    // Merging changed color values into the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = blurredRedMatrix[i][j];
            image[i][j].rgbtGreen = blurredGreenMatrix[i][j];
            image[i][j].rgbtBlue = blurredBlueMatrix[i][j];
        }
    }
}


// Check whether the given is out of range and round
uint8_t makeApt(double n)
{
    return (n > 255) ? 255 : round(n);
}


// Calculate the value of one color for a given pixel and assinging it to a separate matrix
void process(int height, int width, int i, int j, uint8_t originalMatrix[height][width], uint8_t processedMatrix[height][width])
{
    int sumX = 0;
    int sumY = 0;
    double value;

    if (i == 0 && j == 0)   // In the top-left corner
    {
        sumX += 0 * originalMatrix[i][j];   // 2 rows and 2 columns
        sumX += 2 * originalMatrix[i][j + 1];
        sumX += 0 * originalMatrix[i + 1][j];
        sumX += 1 * originalMatrix[i + 1][j + 1];

        sumY += 0 * originalMatrix[i][j];   // 2 rows and 2 columns
        sumY += 0 * originalMatrix[i][j + 1];
        sumY += 2 * originalMatrix[i + 1][j];
        sumY += 1 * originalMatrix[i + 1][j + 1];

        value = sqrt((sumX * sumX) + (sumY * sumY));
        processedMatrix[i][j] = makeApt(value);   // Assigning the calculated appropriate value to a different matrix
    }
    else if (i == 0 && j == width - 1)   // In the top-right corner
    {
        sumX += -2 * originalMatrix[i][j - 1];   // 2 rows and 2 columns
        sumX += 0 * originalMatrix[i][j];
        sumX += -1 * originalMatrix[i + 1][j - 1];
        sumX += 0 * originalMatrix[i + 1][j];

        sumY += 0 * originalMatrix[i][j - 1];   // 2 rows and 2 columns
        sumY += 0 * originalMatrix[i][j];
        sumY += 1 * originalMatrix[i + 1][j - 1];
        sumY += 2 * originalMatrix[i + 1][j];

        value = sqrt((sumX * sumX) + (sumY * sumY));
        processedMatrix[i][j] = makeApt(value);   // Assigning the calculated appropriate value to a different matrix
    }
    else if (i == height - 1 && j == 0)   // In the bottom-left corner
    {
        sumX += 0 * originalMatrix[i - 1][j];   // 2 rows and 2 columns
        sumX += 1 * originalMatrix[i - 1][j + 1];
        sumX += 0 * originalMatrix[i][j];
        sumX += 2 * originalMatrix[i][j + 1];

        sumY += -2 * originalMatrix[i - 1][j];   // 2 rows and 2 columns
        sumY += -1 * originalMatrix[i - 1][j + 1];
        sumY += 0 * originalMatrix[i][j];
        sumY += 0 * originalMatrix[i][j + 1];

        value = sqrt((sumX * sumX) + (sumY * sumY));
        processedMatrix[i][j] = makeApt(value);   // Assigning the calculated appropriate value to a different matrix
    }
    else if (i == height - 1 && j == width - 1)   // In the bottom-right corner
    {
        sumX += -1 * originalMatrix[i - 1][j - 1];   // 2 rows and 2 columns
        sumX += 0 * originalMatrix[i - 1][j];
        sumX += -2 * originalMatrix[i][j - 1];
        sumX += 0 * originalMatrix[i][j];

        sumY += -1 * originalMatrix[i - 1][j - 1];   // 2 rows and 2 columns
        sumY += -2 * originalMatrix[i - 1][j];
        sumY += 0 * originalMatrix[i][j - 1];
        sumY += 0 * originalMatrix[i][j];

        value = sqrt((sumX * sumX) + (sumY * sumY));
        processedMatrix[i][j] = makeApt(value);   // Assigning the calculated appropriate value to a different matrix
    }
    else if (i == 0)   // On the top edge
    {
        sumX += -2 * originalMatrix[i][j - 1];   // 2 rows and 3 columns
        sumX += 0 * originalMatrix[i][j];
        sumX += 2 * originalMatrix[i][j + 1];
        sumX += -1 * originalMatrix[i + 1][j - 1];
        sumX += 0 * originalMatrix[i + 1][j];
        sumX += 1 * originalMatrix[i + 1][j + 1];

        sumY += 0 * originalMatrix[i][j - 1];   // 2 rows and 3 columns
        sumY += 0 * originalMatrix[i][j];
        sumY += 0 * originalMatrix[i][j + 1];
        sumY += 1 * originalMatrix[i + 1][j - 1];
        sumY += 2 * originalMatrix[i + 1][j];
        sumY += 1 * originalMatrix[i + 1][j + 1];

        value = sqrt((sumX * sumX) + (sumY * sumY));
        processedMatrix[i][j] = makeApt(value);   // Assigning the calculated appropriate value to a different matrix
    }
    else if (j == 0)   // On the left edge
    {
        sumX += 0 * originalMatrix[i - 1][j];   // 3 rows and 2 columns
        sumX += 1 * originalMatrix[i - 1][j + 1];
        sumX += 0 * originalMatrix[i][j];
        sumX += 2 * originalMatrix[i][j + 1];
        sumX += 0 * originalMatrix[i + 1][j];
        sumX += 1 * originalMatrix[i + 1][j + 1];

        sumY += -2 * originalMatrix[i - 1][j];   // 3 rows and 2 columns
        sumY += -1 * originalMatrix[i - 1][j + 1];
        sumY += 0 * originalMatrix[i][j];
        sumY += 0 * originalMatrix[i][j + 1];
        sumY += 2 * originalMatrix[i + 1][j];
        sumY += 1 * originalMatrix[i + 1][j + 1];

        value = sqrt((sumX * sumX) + (sumY * sumY));
        processedMatrix[i][j] = makeApt(value);   // Assigning the calculated appropriate value to a different matrix
    }
    else if (j == width - 1)   // On the right edge
    {
        sumX += -1 * originalMatrix[i - 1][j - 1];   // 3 rows and 2 columns
        sumX += 0 * originalMatrix[i - 1][j];
        sumX += -2 * originalMatrix[i][j - 1];
        sumX += 0 * originalMatrix[i][j];
        sumX += -1 * originalMatrix[i + 1][j - 1];
        sumX += 0 * originalMatrix[i + 1][j];

        sumY += -1 * originalMatrix[i - 1][j - 1];   // 3 rows and 2 columns
        sumY += -2 * originalMatrix[i - 1][j];
        sumY += 0 * originalMatrix[i][j - 1];
        sumY += 0 * originalMatrix[i][j];
        sumY += 1 * originalMatrix[i + 1][j - 1];
        sumY += 2 * originalMatrix[i + 1][j];

        value = sqrt((sumX * sumX) + (sumY * sumY));
        processedMatrix[i][j] = makeApt(value);   // Assigning the calculated appropriate value to a different matrix
    }
    else if (i == height - 1)   // On the bottom edge
    {
        sumX += -1 * originalMatrix[i - 1][j - 1];   // 2 rows and 3 columns
        sumX += 0 * originalMatrix[i - 1][j];
        sumX += 1 * originalMatrix[i - 1][j + 1];
        sumX += -2 * originalMatrix[i][j - 1];
        sumX += 0 * originalMatrix[i][j];
        sumX += 2 * originalMatrix[i][j + 1];

        sumY += -1 * originalMatrix[i - 1][j - 1];   // 2 rows and 3 columns
        sumY += -2 * originalMatrix[i - 1][j];
        sumY += -1 * originalMatrix[i - 1][j + 1];
        sumY += 0 * originalMatrix[i][j - 1];
        sumY += 0 * originalMatrix[i][j];
        sumY += 0 * originalMatrix[i][j + 1];

        value = sqrt((sumX * sumX) + (sumY * sumY));
        processedMatrix[i][j] = makeApt(value);   // Assigning the calculated appropriate value to a different matrix
    }
    else   // In the middle
    {
        sumX += -1 * originalMatrix[i - 1][j - 1];   // 2 rows and 3 columns
        sumX += 0 * originalMatrix[i - 1][j];
        sumX += 1 * originalMatrix[i - 1][j + 1];
        sumX += -2 * originalMatrix[i][j - 1];
        sumX += 0 * originalMatrix[i][j];
        sumX += 2 * originalMatrix[i][j + 1];
        sumX += -1 * originalMatrix[i + 1][j - 1];
        sumX += 0 * originalMatrix[i + 1][j];
        sumX += 1 * originalMatrix[i + 1][j + 1];

        sumY += -1 * originalMatrix[i - 1][j - 1];   // 2 rows and 3 columns
        sumY += -2 * originalMatrix[i - 1][j];
        sumY += -1 * originalMatrix[i - 1][j + 1];
        sumY += 0 * originalMatrix[i][j - 1];
        sumY += 0 * originalMatrix[i][j];
        sumY += 0 * originalMatrix[i][j + 1];
        sumY += 1 * originalMatrix[i + 1][j - 1];
        sumY += 2 * originalMatrix[i + 1][j];
        sumY += 1 * originalMatrix[i + 1][j + 1];

        value = sqrt((sumX * sumX) + (sumY * sumY));
        processedMatrix[i][j] = makeApt(value);   // Assigning the calculated appropriate value to a different matrix
    }
}


// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    uint8_t originalRedMatrix[height][width];
    uint8_t originalGreenMatrix[height][width];
    uint8_t originalBlueMatrix[height][width];
    uint8_t processedRedMatrix[height][width];
    uint8_t processedGreenMatrix[height][width];
    uint8_t processedBlueMatrix[height][width];

    // Copying image color value into three separate matrices,
    // manipulation with them easier
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRedMatrix[i][j] = image[i][j].rgbtRed;
            originalGreenMatrix[i][j] = image[i][j].rgbtGreen;
            originalBlueMatrix[i][j] = image[i][j].rgbtBlue;
        }
    }

    // Calculating average color value for each pixel and saving it into different matrices
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            process(height, width, i, j, originalRedMatrix, processedRedMatrix);
            process(height, width, i, j, originalGreenMatrix, processedGreenMatrix);
            process(height, width, i, j, originalBlueMatrix, processedBlueMatrix);
        }
    }

    // Merging changed color values into the original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = processedRedMatrix[i][j];
            image[i][j].rgbtGreen = processedGreenMatrix[i][j];
            image[i][j].rgbtBlue = processedBlueMatrix[i][j];
        }
    }
}