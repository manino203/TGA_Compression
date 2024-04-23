# TGA Image Compression

This program allows compressing and decompressing TGA images using the Simple Block Compression method.

## Compilation and Execution

To compile the program, use the following command:

`source make.sh`

### Compression

The program compresses the image by dividing it into blocks of a specified size and looking for sequences of similar pixels in each block. These sequences are then replaced with a sequence containing the first pixel in the sequence and the number of pixels in the sequence.

Example of using the program for compression:

`./jbk compress --input <file path> --output <file path> --block-size <number> --max-diff <number>`


###  Decompression

Example of using the program for decompression:

`./jbk decompress --input <file path> --output <file path>`


The arguments of the program (except for the first compress/decompress) can be entered in any order.








