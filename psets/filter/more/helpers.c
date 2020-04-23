#include "helpers.h"
#include "stdio.h"
#include "math.h"

void is255(double *sR, double *sG, double *sB);
RGBTRIPLE sobel(RGBTRIPLE *g1, RGBTRIPLE *g2, RGBTRIPLE *g3,
                RGBTRIPLE *g4, RGBTRIPLE *g5, RGBTRIPLE *g6,
                RGBTRIPLE *g7, RGBTRIPLE *g8, RGBTRIPLE *g9);
void fillRGB(RGBTRIPLE rgb, BYTE num);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double tmp = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue * 1.0) / 3);

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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int w = width - 1 - j;

            RGBTRIPLE tmp = image[i][j];
            image[i][j] = image[i][w];
            image[i][w] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    double sR = 0;
    double sG = 0;
    double sB = 0;

    RGBTRIPLE tmp[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = * &image[i][j];
        }
    }

    // ↓ height - 1
    // 2 [[ ] [ ] [ ]]
    // 1 [[ ] [ ] [ ]]
    // 0 [[ ] [ ] [ ]]
    //[-]  0   1   2  <- width - 1

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 && j != width - 1 && j != 0)
            {
                // [[ ] [ ] [ ]]
                // [[ ] [ ] [ ]]
                // [[ ] [o] [ ]]
                sR = round((tmp[i][j - 1].rgbtRed + tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed +
                            tmp[i + 1][j - 1].rgbtRed + tmp[i + 1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed * 1.0) /
                           6);

                sG = round((tmp[i][j - 1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen +
                            tmp[i + 1][j - 1].rgbtGreen + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen * 1.0) /
                           6);

                sB = round((tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue +
                            tmp[i + 1][j - 1].rgbtBlue + tmp[i + 1][j].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue * 1.0) /
                           6);
            }
            else if (i == height - 1 && j != width - 1 && j != 0)
            {
                // [[ ] [o] [ ]]
                // [[ ] [ ] [ ]]
                // [[ ] [ ] [ ]]
                sR = round((tmp[i][j - 1].rgbtRed + tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed +
                            tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed * 1.0) /
                           6);

                sG = round((tmp[i][j - 1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen +
                            tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen * 1.0) /
                           6);

                sB = round((tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue +
                            tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue * 1.0) /
                           6);
            }
            else if (j == 0 && i != 0 && i != height - 1)
            {
                // [[ ] [ ] [ ]]
                // [[o] [ ] [ ]]
                // [[ ] [ ] [ ]]
                sR = round((tmp[i + 1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed +
                            tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed +
                            tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed * 1.0) /
                           6);

                sG = round((tmp[i + 1][j].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen +
                            tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen +
                            tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen * 1.0) /
                           6);

                sB = round((tmp[i + 1][j].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue +
                            tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue +
                            tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue * 1.0) /
                           6);
            }
            else if (j == width - 1 && i != 0 && i != height - 1)
            {
                // [[ ] [ ] [ ]]
                // [[ ] [ ] [o]]
                // [[ ] [ ] [ ]]
                sR = round((tmp[i + 1][j].rgbtRed + tmp[i + 1][j - 1].rgbtRed +
                            tmp[i][j].rgbtRed + tmp[i][j - 1].rgbtRed +
                            tmp[i - 1][j].rgbtRed + tmp[i - 1][j - 1].rgbtRed * 1.0) /
                           6);

                sG = round((tmp[i + 1][j].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen +
                            tmp[i][j].rgbtGreen + tmp[i][j - 1].rgbtGreen +
                            tmp[i - 1][j].rgbtGreen + tmp[i - 1][j - 1].rgbtGreen * 1.0) /
                           6);

                sB = round((tmp[i + 1][j].rgbtBlue + tmp[i + 1][j - 1].rgbtBlue +
                            tmp[i][j].rgbtBlue + tmp[i][j - 1].rgbtBlue +
                            tmp[i - 1][j].rgbtBlue + tmp[i - 1][j - 1].rgbtBlue * 1.0) /
                           6);
            }
            else if (j == 0 && i == 0)
            {
                // [[ ] [ ] [ ]]
                // [[ ] [ ] [ ]]
                // [[o] [ ] [ ]]
                sR = round((tmp[i + 1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed +
                            tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed * 1.0) /
                           4);

                sG = round((tmp[i + 1][j].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen +
                            tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen * 1.0) /
                           4);

                sB = round((tmp[i + 1][j].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue +
                            tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue * 1.0) /
                           4);
            }
            else if (i == 0 && j == width - 1)
            {
                // [[ ] [ ] [ ]]
                // [[ ] [ ] [ ]]
                // [[ ] [ ] [o]]
                sR = round((tmp[i + 1][j].rgbtRed + tmp[i + 1][j - 1].rgbtRed +
                            tmp[i][j].rgbtRed + tmp[i][j - 1].rgbtRed * 1.0) /
                           4);

                sG = round((tmp[i + 1][j].rgbtGreen + tmp[i + 1][j - 1].rgbtGreen +
                            tmp[i][j].rgbtGreen + tmp[i][j - 1].rgbtGreen * 1.0) /
                           4);

                sB = round((tmp[i + 1][j].rgbtBlue + tmp[i + 1][j - 1].rgbtBlue +
                            tmp[i][j].rgbtBlue + tmp[i][j - 1].rgbtBlue * 1.0) /
                           4);
            }
            else if (j == 0 && i == height - 1)
            {
                // [[o] [ ] [ ]]
                // [[ ] [ ] [ ]]
                // [[ ] [ ] [ ]]
                sR = round((tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed +
                            tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed * 1.0) /
                           4);

                sG = round((tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen +
                            tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen * 1.0) /
                           4);

                sB = round((tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue +
                            tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue * 1.0) /
                           4);
            }
            else if (j == width - 1 && i == height - 1)
            {
                // [[ ] [ ] [o]]
                // [[ ] [ ] [ ]]
                // [[ ] [ ] [ ]]
                sR = round((tmp[i - 1][j].rgbtRed + tmp[i - 1][j - 1].rgbtRed +
                            tmp[i][j].rgbtRed + tmp[i][j - 1].rgbtRed * 1.0) /
                           4);

                sG = round((tmp[i - 1][j].rgbtGreen + tmp[i - 1][j - 1].rgbtGreen +
                            tmp[i][j].rgbtGreen + tmp[i][j - 1].rgbtGreen * 1.0) /
                           4);

                sB = round((tmp[i - 1][j].rgbtBlue + tmp[i - 1][j - 1].rgbtBlue +
                            tmp[i][j].rgbtBlue + tmp[i][j - 1].rgbtBlue * 1.0) /
                           4);
            }
            else if (i != 0 && j != 0 && j != width - 1 && i != height - 1)
            {
                // [[ ] [ ] [ ]]
                // [[ ] [o] [ ]]
                // [[ ] [ ] [ ]]
                sR = round((tmp[i - 1][j - 1].rgbtRed + tmp[i - 1][j].rgbtRed + tmp[i - 1][j + 1].rgbtRed +
                            tmp[i][j - 1].rgbtRed + tmp[i][j].rgbtRed + tmp[i][j + 1].rgbtRed +
                            tmp[i + 1][j - 1].rgbtRed + tmp[i + 1][j].rgbtRed + tmp[i + 1][j + 1].rgbtRed * 1.0) /
                           9);

                sG = round((tmp[i - 1][j - 1].rgbtGreen + tmp[i - 1][j].rgbtGreen + tmp[i - 1][j + 1].rgbtGreen +
                            tmp[i][j - 1].rgbtGreen + tmp[i][j].rgbtGreen + tmp[i][j + 1].rgbtGreen +
                            tmp[i + 1][j - 1].rgbtGreen + tmp[i + 1][j].rgbtGreen + tmp[i + 1][j + 1].rgbtGreen * 1.0) /
                           9);

                sB = round((tmp[i - 1][j - 1].rgbtBlue + tmp[i - 1][j].rgbtBlue + tmp[i - 1][j + 1].rgbtBlue +
                            tmp[i][j - 1].rgbtBlue + tmp[i][j].rgbtBlue + tmp[i][j + 1].rgbtBlue +
                            tmp[i + 1][j - 1].rgbtBlue + tmp[i + 1][j].rgbtBlue + tmp[i + 1][j + 1].rgbtBlue * 1.0) /
                           9);
            }

            is255(&sR, &sG, &sB);

            image[i][j].rgbtRed = sR;
            image[i][j].rgbtGreen = sG;
            image[i][j].rgbtBlue = sB;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height + 2][width + 2];
    RGBTRIPLE blank;
    RGBTRIPLE res;

    blank.rgbtRed = 0;
    blank.rgbtGreen = 0;
    blank.rgbtBlue = 0;
    res.rgbtRed = 0;
    res.rgbtGreen = 0;
    res.rgbtBlue = 0;
    for (int i = 0; i < height + 2; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (j == 0 || i == 0 || j >= width + 1 || i >= height + 1)
            {
                tmp[i][j] = blank;
            }
            else
            {
                tmp[i][j] = * &image[i - 1][j - 1];
            }
        }
    }

    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            res = sobel(&tmp[i - 1][j - 1], &tmp[i - 1][j], &tmp[i - 1][j + 1],
                        &tmp[i][j - 1], &tmp[i][j], &tmp[i][j + 1],
                        &tmp[i + 1][j - 1], &tmp[i + 1][j], &tmp[i + 1][j + 1]);

            if (i >= 1 || j >= 1 || i <= height || j <= width)
            {
                image[i - 1][j - 1] = res;
            }
            else
            {
                printf("i %i %i j", i, j);
            }

        } // j
    }     // i

    return;
}

RGBTRIPLE sobel(RGBTRIPLE *g1, RGBTRIPLE *g2, RGBTRIPLE *g3,
                RGBTRIPLE *g4, RGBTRIPLE *g5, RGBTRIPLE *g6,
                RGBTRIPLE *g7, RGBTRIPLE *g8, RGBTRIPLE *g9)
{
    RGBTRIPLE tmp;

    long gxR, gxG, gxB,
         gyR, gyG, gyB;

    double resR, resG, resB;

    gyR = (-1 * (g1->rgbtRed) + 0 * (g2->rgbtRed) + 1 * (g3->rgbtRed) +
           -2 * (g4->rgbtRed) + 0 * (g5->rgbtRed) + 2 * (g6->rgbtRed) +
           -1 * (g7->rgbtRed) + 0 * (g8->rgbtRed) + 1 * (g9->rgbtRed));
    gxR = (-1 * (g7->rgbtRed) + -2 * (g8->rgbtRed) + -1 * (g9->rgbtRed) +
           0 * (g4->rgbtRed) + 0 * (g5->rgbtRed) + 0 * (g6->rgbtRed) +
           1 * (g1->rgbtRed) + 2 * (g2->rgbtRed) + 1 * (g3->rgbtRed));

    gyG = (-1 * (g1->rgbtGreen) + 0 * (g2->rgbtGreen) + 1 * (g3->rgbtGreen) +
           -2 * (g4->rgbtGreen) + 0 * (g5->rgbtGreen) + 2 * (g6->rgbtGreen) +
           -1 * (g7->rgbtGreen) + 0 * (g8->rgbtGreen) + 1 * (g9->rgbtGreen));
    gxG = (-1 * (g7->rgbtGreen) + -2 * (g8->rgbtGreen) + -1 * (g9->rgbtGreen) +
           0 * (g4->rgbtGreen) + 0 * (g5->rgbtGreen) + 0 * (g6->rgbtGreen) +
           1 * (g1->rgbtGreen) + 2 * (g2->rgbtGreen) + 1 * (g3->rgbtGreen));

    gyB = (-1 * (g1->rgbtBlue) + 0 * (g2->rgbtBlue) + 1 * (g3->rgbtBlue) +
           -2 * (g4->rgbtBlue) + 0 * (g5->rgbtBlue) + 2 * (g6->rgbtBlue) +
           -1 * (g7->rgbtBlue) + 0 * (g8->rgbtBlue) + 1 * (g9->rgbtBlue));
    gxB = (-1 * (g7->rgbtBlue) + -2 * (g8->rgbtBlue) + -1 * (g9->rgbtBlue) +
           0 * (g4->rgbtBlue) + 0 * (g5->rgbtBlue) + 0 * (g6->rgbtBlue) +
           1 * (g1->rgbtBlue) + 2 * (g2->rgbtBlue) + 1 * (g3->rgbtBlue));

    resR = round(sqrt(pow(gxR, 2.0) + pow(gyR, 2.0)));
    resG = round(sqrt(pow(gxG, 2.0) + pow(gyG, 2.0)));
    resB = round(sqrt(pow(gxB, 2.0) + pow(gyB, 2.0)));

    is255(&resR, &resG, &resB);

    tmp.rgbtRed = resR;
    tmp.rgbtGreen = resG;
    tmp.rgbtBlue = resB;

    return tmp;
}

void is255(double *sR, double *sG, double *sB)
{
    if (*sR >= 255)
    {
        *sR = 255;
    }
    if (*sG >= 255)
    {
        *sG = 255;
    }
    if (*sB >= 255)
    {
        *sB = 255;
    }
}
