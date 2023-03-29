# Recover JPEG
The `recover.c` program is designed to recover JPEG images from a raw file.

The program works by iterating through the input file 512 bytes at a time. It checks if the first 4 bytes match the JPEG header, indicating the start of a new image. When it finds a header, it creates a new output file with a filename of the format "000.jpg", "001.jpg", "002.jpg", and so on, and writes the 512-byte blocks of data to the output file until it finds another header.

### Usage

The program is run from the command line, like this: `./recover [IMAGE.raw]`

Where `[IMAGE.raw]` is the name of the raw file containing the deleted images to be recovered.

### Limitations

The program assumes:
- The input file contains only deleted JPEG images and will not work correctly if the file contains other types of data
- The JPEG images are stored in contiguous 512-byte blocks, with no gaps or overlapping data
- There is enough memory available to store the filename for each output image
- Does not perform any error checking on the input file or output files


### Dependencies

The program depends on the following standard libraries: `stdio.h`, `stdlib.h`, and `stdint.h`.