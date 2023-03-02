#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

// Defining int with one-byte size as BYTE
typedef uint8_t BYTE;

// Declaring a constant of 512 as the size of a block of data
const int BLOCK_SIZE = 512;


int main(int argc, char *argv[])
{
    // Checking the number of command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Opening the raw file
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file\n");
        return 1;
    }

    FILE *image = NULL;   // Declaring a file pointer for copying the data
    BYTE buffer[BLOCK_SIZE];   // Declaring an array for storing a block of data
    char *name = malloc(8 * sizeof(char));   // Allocating memory for string
    int counter = 0;   // Counts the number of images

    // Reading from file and writing to image one block at a time
    while (fread(buffer, 1, BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff)
        {
            sprintf(name, "%03d.jpg", counter);   // Creating a name for the upcoming image
            if (counter > 0)
            {
                fclose(image);   // Closing the previous image if it existed
            }
            image = fopen(name, "w");   // Opening a new image with corresponding name
            fwrite(buffer, 1, BLOCK_SIZE, image);   // Writing a block of data
            counter++;
        }
        else if (counter > 0)
        {
            fwrite(buffer, 1, BLOCK_SIZE, image);   // Writing a block of data
        }
    }

    // Freeing allocated memory and closing opened files
    free(name);
    fclose(file);
    fclose(image);

}