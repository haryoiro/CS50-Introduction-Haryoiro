#include "helpers.h"
#include "stdio.h"
#include "math.h"
#include "stdlib.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double tmp = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue * 1.0) / 3.0);

            if (tmp >= 255)
            {
                tmp = 255;
            }
            
            image[i][j].rgbtRed = tmp;
            image[i][j].rgbtGreen = tmp;
            image[i][j].rgbtBlue = tmp;
        }
    }
    return;
}
// sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
// sepiaGreen = .349 * originalRed + .686 * originalGreen + .169 * originalBlue
// sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE originalRed = image[i][j].rgbtRed;
            BYTE originalGreen = image[i][j].rgbtGreen;
            BYTE originalBlue = image[i][j].rgbtBlue;

            double newRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            double newGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            double newBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            if (newRed >= 255)
            {
                newRed = 255;
            }
            if (newGreen >= 255)
            {
                newGreen = 255;
            }
            if (newBlue >= 255)
            {
                newBlue = 255;
            }

            image[i][j].rgbtRed = newRed;
            image[i][j].rgbtGreen = newGreen;
            image[i][j].rgbtBlue = newBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int w = width - 1;
            BYTE originalRed = image[i][j].rgbtRed;
            BYTE originalGreen = image[i][j].rgbtGreen;
            BYTE originalBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = image[i][w - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][w - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][w - j].rgbtBlue;

            image[i][w - j].rgbtRed = originalRed;
            image[i][w - j].rgbtGreen = originalGreen;
            image[i][w - j].rgbtBlue = originalBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    double plusRed = 0;
    double plusGreen = 0;
    double plusBlue = 0;
    RGBTRIPLE im[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            im[i][j] = * &image[i][j];
            // printf("%i", *&im[i][j]->rgbtRed);
        }
    }
    // printf("%i\n", im[5][5].rgbtRed);
    // 2 [[ ], [ ], [ ]]
    // 1 [[ ], [ ], [ ]]
    // 0 [[o], [ ], [ ]]
    //     0    1    2

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j == 0)
            {
                // [[ ], [ ], [ ]]
                // [[ ], [ ], [ ]]
                // [[o], [ ], [ ]]
                // printf("2, 0\n");
                plusRed = round((im[i + 1][j + 1].rgbtRed + im[i + 1][j].rgbtRed + im[i][j + 1].rgbtRed + im[i][j].rgbtRed * 1.0) / 4);

                plusGreen = round((im[i + 1][j + 1].rgbtGreen + im[i + 1][j].rgbtGreen + im[i][j + 1].rgbtGreen + im[i][j].rgbtGreen * 1.0) / 4);

                plusBlue = round((im[i + 1][j + 1].rgbtBlue + im[i + 1][j].rgbtBlue + im[i][j + 1].rgbtBlue + im[i][j].rgbtBlue * 1.0) / 4);

                if (plusRed >= 255)
                {
                    plusRed = 255;
                }
                if (plusGreen >= 255)
                {
                    plusGreen = 255;
                }
                if (plusBlue >= 255)
                {
                    plusBlue = 255;
                }

                image[i][j].rgbtRed = plusRed;
                image[i][j].rgbtGreen = plusGreen;
                image[i][j].rgbtBlue = plusBlue;
            }
            if (j != 0 && j != width - 1 && i == 0)
            {
                // [[ ], [ ], [ ]]
                // [[ ], [ ], [ ]]
                // [[ ], [o], [ ]]
                // printf("2, 1\n");
                plusRed = round((im[i][j - 1].rgbtRed + im[i][j].rgbtRed + im[i][j + 1].rgbtRed + im[i + 1][j - 1].rgbtRed +
                                 im[i + 1][j].rgbtRed + im[i + 1][j + 1].rgbtRed * 1.0) / 6);

                plusGreen = round((im[i][j - 1].rgbtGreen + im[i][j].rgbtGreen + im[i][j + 1].rgbtGreen + im[i + 1][j - 1].rgbtGreen +
                                   im[i + 1][j].rgbtGreen + im[i + 1][j + 1].rgbtGreen * 1.0) / 6);

                plusBlue = round((im[i][j - 1].rgbtBlue + im[i][j].rgbtBlue + im[i][j + 1].rgbtBlue + im[i + 1][j - 1].rgbtBlue +
                                  im[i + 1][j].rgbtBlue + im[i + 1][j + 1].rgbtBlue * 1.0) / 6);

                if (plusRed >= 255)
                {
                    plusRed = 255;
                }
                if (plusGreen >= 255)
                {
                    plusGreen = 255;
                }
                if (plusBlue >= 255)
                {
                    plusBlue = 255;
                }

                image[i][j].rgbtRed = plusRed;
                image[i][j].rgbtGreen = plusGreen;
                image[i][j].rgbtBlue = plusBlue;

                // im[i][j].rgbtRed = 0;
                // im[i][j].rgbtGreen = 255;
                // im[i][j].rgbtBlue = 0;
            }
            if (i == 0 && j == width - 1)
            {
                // [[ ], [ ], [ ]]
                // [[ ], [ ], [ ]]
                // [[ ], [ ], [o]]
                // printf("2, 2\n");
                plusRed = round((im[i + 1][j].rgbtRed + im[i + 1][j - 1].rgbtRed + im[i][j].rgbtRed + im[i][j - 1].rgbtRed * 1.0) / 4);

                plusGreen = round((im[i + 1][j].rgbtGreen + im[i + 1][j - 1].rgbtGreen + im[i][j].rgbtGreen + im[i][j - 1].rgbtGreen * 1.0) / 4);

                plusBlue = round((im[i + 1][j].rgbtBlue + im[i + 1][j - 1].rgbtBlue + im[i][j].rgbtBlue + im[i][j - 1].rgbtBlue * 1.0) / 4);

                if (plusRed >= 255)
                {
                    plusRed = 255;
                }
                if (plusGreen >= 255)
                {
                    plusGreen = 255;
                }
                if (plusBlue >= 255)
                {
                    plusBlue = 255;
                }

                image[i][j].rgbtRed = plusRed;
                image[i][j].rgbtGreen = plusGreen;
                image[i][j].rgbtBlue = plusBlue;
            }
            if (i != 0 && i != height - 1 && j == 0)
            {
                // [[ ], [ ], [ ]]
                // [[o], [ ], [ ]]
                // [[ ], [ ], [ ]]
                // printf("0, 1\n");

                plusRed = round((im[i + 1][j + 1].rgbtRed + im[i + 1][j].rgbtRed + im[i][j + 1].rgbtRed + im[i][j].rgbtRed +
                                 im[i - 1][j + 1].rgbtRed + im[i - 1][j].rgbtRed * 1.0) / 6);

                plusGreen = round((im[i + 1][j + 1].rgbtGreen + im[i + 1][j].rgbtGreen + im[i][j + 1].rgbtGreen + im[i][j].rgbtGreen +
                                   im[i - 1][j + 1].rgbtGreen + im[i - 1][j].rgbtGreen * 1.0) / 6);

                plusBlue = round((im[i + 1][j + 1].rgbtBlue + im[i + 1][j].rgbtBlue + im[i][j + 1].rgbtBlue + im[i][j].rgbtBlue +
                                  im[i - 1][j + 1].rgbtBlue + im[i - 1][j].rgbtBlue * 1.0) / 6);

                if (plusRed >= 255)
                {
                    plusRed = 255;
                }
                if (plusGreen >= 255)
                {
                    plusGreen = 255;
                }
                if (plusBlue >= 255)
                {
                    plusBlue = 255;
                }

                image[i][j].rgbtRed = plusRed;
                image[i][j].rgbtGreen = plusGreen;
                image[i][j].rgbtBlue = plusBlue;

                // im[i][j].rgbtRed = 255;
                // im[i][j].rgbtGreen = 0;
                // im[i][j].rgbtBlue = 0;
            }
            if (i != 0 && i != height - 1 && j != 0 && j != width - 1)
            {
                // [[ ], [ ], [ ]]
                // [[ ], [o], [ ]]
                // [[ ], [ ], [ ]]

                // printf("1, 1\n");
                plusRed = round((im[i - 1][j - 1].rgbtRed + im[i - 1][j].rgbtRed + im[i - 1][j + 1].rgbtRed + im[i][j - 1].rgbtRed +
                                 im[i][j].rgbtRed + im[i][j + 1].rgbtRed + im[i + 1][j - 1].rgbtRed + im[i + 1][j].rgbtRed + im[i + 1][j + 1].rgbtRed *
                                 1.0) / 9);

                plusGreen = round((im[i - 1][j - 1].rgbtGreen + im[i - 1][j].rgbtGreen + im[i - 1][j + 1].rgbtGreen + im[i][j - 1].rgbtGreen +
                                   im[i][j].rgbtGreen + im[i][j + 1].rgbtGreen + im[i + 1][j - 1].rgbtGreen + im[i + 1][j].rgbtGreen + im[i + 1][j + 1].rgbtGreen *
                                   1.0) / 9);

                plusBlue = round((im[i - 1][j - 1].rgbtBlue + im[i - 1][j].rgbtBlue + im[i - 1][j + 1].rgbtBlue + im[i][j - 1].rgbtBlue +
                                  im[i][j].rgbtBlue + im[i][j + 1].rgbtBlue + im[i + 1][j - 1].rgbtBlue + im[i + 1][j].rgbtBlue + im[i + 1][j + 1].rgbtBlue *
                                  1.0) / 9);

                if (plusRed >= 255)
                {
                    plusRed = 255;
                }
                if (plusGreen >= 255)
                {
                    plusGreen = 255;
                }
                if (plusBlue >= 255)
                {
                    plusBlue = 255;
                }

                image[i][j].rgbtRed = plusRed;
                image[i][j].rgbtGreen = plusGreen;
                image[i][j].rgbtBlue = plusBlue;

                // im[i][j].rgbtRed = 255;
                // im[i][j].rgbtGreen = 255;
                // im[i][j].rgbtBlue = 255;
            }
            if (i != 0 && i != height - 1 && j == width - 1)
            {
                // [[ ], [ ], [ ]]
                // [[ ], [ ], [o]]
                // [[ ], [ ], [ ]]

                // printf("1, 2\n");
                plusRed = round((im[i + 1][j].rgbtRed + im[i + 1][j - 1].rgbtRed + im[i][j].rgbtRed + im[i][j - 1].rgbtRed +
                                 im[i - 1][j].rgbtRed + im[i - 1][j - 1].rgbtRed * 1.0) / 6);

                plusGreen = round((im[i + 1][j].rgbtGreen + im[i + 1][j - 1].rgbtGreen + im[i][j].rgbtGreen + im[i][j - 1].rgbtGreen +
                                   im[i - 1][j].rgbtGreen + im[i - 1][j - 1].rgbtGreen * 1.0) / 6);

                plusBlue = round((im[i + 1][j].rgbtBlue + im[i + 1][j - 1].rgbtBlue + im[i][j].rgbtBlue + im[i][j - 1].rgbtBlue +
                                  im[i - 1][j].rgbtBlue + im[i - 1][j - 1].rgbtBlue * 1.0) / 6);

                if (plusRed >= 255)
                {
                    plusRed = 255;
                }
                if (plusGreen >= 255)
                {
                    plusGreen = 255;
                }
                if (plusBlue >= 255)
                {
                    plusBlue = 255;
                }

                image[i][j].rgbtRed = plusRed;
                image[i][j].rgbtGreen = plusGreen;
                image[i][j].rgbtBlue = plusBlue;

                // im[i][j].rgbtRed = 0;
                // im[i][j].rgbtGreen = 0;
                // im[i][j].rgbtBlue = 255;
            }
            if (i == height - 1 && j == 0)
            {
                // [[o], [ ], [ ]]
                // [[ ], [ ], [ ]]
                // [[ ], [ ], [ ]]
                // printf("0, 0\n");
                plusRed = round((im[i][j + 1].rgbtRed + im[i][j].rgbtRed + im[i - 1][j + 1].rgbtRed + im[i - 1][j].rgbtRed * 1.0) / 4);

                plusGreen = round((im[i][j + 1].rgbtGreen + im[i][j].rgbtGreen + im[i - 1][j + 1].rgbtGreen + im[i - 1][j].rgbtGreen * 1.0) / 4);

                plusBlue = round((im[i][j + 1].rgbtBlue + im[i][j].rgbtBlue + im[i - 1][j + 1].rgbtBlue + im[i - 1][j].rgbtBlue * 1.0) / 4);

                if (plusRed >= 255)
                {
                    plusRed = 255;
                }
                if (plusGreen >= 255)
                {
                    plusGreen = 255;
                }
                if (plusBlue >= 255)
                {
                    plusBlue = 255;
                }

                image[i][j].rgbtRed = plusRed;
                image[i][j].rgbtGreen = plusGreen;
                image[i][j].rgbtBlue = plusBlue;
            }
            if (i == height - 1 && j != 0 && j != width - 1)
            {
                // [[ ], [o], [ ]]
                // [[ ], [ ], [ ]]
                // [[ ], [ ], [ ]]

                // printf("0, 1\n");
                plusRed = round((im[i - 1][j - 1].rgbtRed + im[i - 1][j].rgbtRed + im[i - 1][j + 1].rgbtRed +
                                 im[i][j - 1].rgbtRed + im[i][j].rgbtRed + im[i][j + 1].rgbtRed * 1.0) / 6);

                plusGreen = round((im[i - 1][j - 1].rgbtGreen + im[i - 1][j].rgbtGreen + im[i - 1][j + 1].rgbtGreen +
                                   im[i][j - 1].rgbtGreen + im[i][j].rgbtGreen + im[i][j + 1].rgbtGreen * 1.0) / 6);

                plusBlue = round((im[i - 1][j - 1].rgbtBlue + im[i - 1][j].rgbtBlue + im[i - 1][j + 1].rgbtBlue +
                                  im[i][j - 1].rgbtBlue + im[i][j].rgbtBlue + im[i][j + 1].rgbtBlue * 1.0) / 6);

                if (plusRed >= 255)
                {
                    plusRed = 255;
                }
                if (plusGreen >= 255)
                {
                    plusGreen = 255;
                }
                if (plusBlue >= 255)
                {
                    plusBlue = 255;
                }

                image[i][j].rgbtRed = plusRed;
                image[i][j].rgbtGreen = plusGreen;
                image[i][j].rgbtBlue = plusBlue;

                // im[i][j].rgbtRed = 40;
                // im[i][j].rgbtGreen = 40;
                // im[i][j].rgbtBlue = 40;
            }
            if (i == height - 1 && j == width - 1)
            {
                // [[ ], [ ], [o]]
                // [[ ], [ ], [ ]]
                // [[ ], [ ], [ ]]
                // printf("0, 2\n");
                plusRed = round((im[i][j].rgbtRed + im[i][j - 1].rgbtRed + im[i - 1][j].rgbtRed + im[i - 1][j - 1].rgbtRed * 1.0) / 4);

                plusGreen = round((im[i][j].rgbtGreen + im[i][j - 1].rgbtGreen + im[i - 1][j].rgbtGreen + im[i - 1][j - 1].rgbtGreen * 1.0) / 4);

                plusBlue = round((im[i][j].rgbtBlue + im[i][j - 1].rgbtBlue + im[i - 1][j].rgbtBlue + im[i - 1][j - 1].rgbtBlue * 1.0) / 4);

                if (plusRed >= 255)
                {
                    plusRed = 255;
                }
                if (plusGreen >= 255)
                {
                    plusGreen = 255;
                }
                if (plusBlue >= 255)
                {
                    plusBlue = 255;
                }

                image[i][j].rgbtRed = plusRed;
                image[i][j].rgbtGreen = plusGreen;
                image[i][j].rgbtBlue = plusBlue;
            }
        }
    }
    return;
}