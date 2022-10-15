#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Sanitize input to one command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover [IMAGE.raw]\n");
        return 1;
    }

    // Open a memory card input
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Make file pointer for images output
    FILE *output = NULL;

    // Allocate a space for the filename output
    char *filename = malloc(8 * sizeof(BYTE));

    // Count number of images recovered
    int count = 0;

    // Declare a buffer
    BYTE buffer[512];

    // Iterate through the input file 512 blocks at a time
    while (fread(buffer, sizeof(BYTE), 512, input))
    {
        // Check if the first 4 bytes match the JPEG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close the previous output
            if (count > 0)
            {
                fclose(output);
            }
            // Write serialized image filenames
            sprintf(filename, "%03i.jpg", count);

            // Open the output for writing
            output = fopen(filename, "w");

            count++;
        }
        if (output != NULL)
        {
            // Write data to the buffer
            fwrite(buffer, sizeof(BYTE), 512, output);
        }
    }
    // Close I/O
    free(filename);
    fclose(input);
    fclose(output);

    return 0;
}