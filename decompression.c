#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#include <errno.h>
#include <glib-2.0/glib.h>
#include <glib-2.0/glib//garray.h>
#include "common.h"


void add_block_to_image(Pixel* image, Pixel* block, int x_origin, int y_origin, unsigned short block_size, unsigned short width){
    for (int y = 0; y < block_size; ++y) {
        for (int x = 0; x < block_size; ++x) {
            int i = real_index(x_origin + x, y_origin + y, width);
            int block_i = real_index(x, y, block_size);
            image[i] = block[block_i];
        }
    }
}

int decompress(char* in_path, char* out_path){

    FILE* f_in = fopen(in_path, "rb");
    if (f_in == NULL){
        printf("Error opening input file.\n");
        return 1;
    }

    BinHeader bin_header;
    if(fread(&bin_header, sizeof(BinHeader), 1, f_in) != 1){
        printf("Error reading binary header.\n");
        fclose(f_in);
        return 1;
    }

    unsigned short block_size = (bin_header.block_size[1] << 8) | bin_header.block_size[0];;

    unsigned short width = (bin_header.tga_header.width[1] << 8) | bin_header.tga_header.width[0];
    unsigned short height = (bin_header.tga_header.height[1] << 8) | bin_header.tga_header.height[0];;


    GByteArray* byte_array =  g_byte_array_new();
    byte last_byte;
    while (fread(&last_byte, sizeof(byte), 1, f_in) == 1){
        g_byte_array_append(byte_array, &last_byte, sizeof(byte));
    }

    Seq* seq_arr = (Seq*)byte_array->data;
    Pixel* img_data = malloc(width*height * sizeof(Pixel));
    int i = 0;
    for (int y = 0; y < height; y+=block_size){
        for (int x = 0; x < width; x+=block_size){
            Pixel* block = malloc(sizeof(Pixel) * block_size *block_size);
            long pixel_count = 0;
            while (pixel_count < (block_size * block_size)){

                Seq sequence = seq_arr[i];
                for (int j = 0; j < sequence.count; ++j) {
                    Pixel pixel = {
                            .red = sequence.red,
                            .green = sequence.green,
                            .blue = sequence.blue
                    };
                    block[pixel_count] = pixel;
                    pixel_count++;
                }
                i++;
            }
            add_block_to_image(img_data, block, x, y, block_size, width);
            free(block);
        }
    }



    FILE* f_out = fopen(out_path, "wb");
    if (f_out == NULL){
        printf("Error opening output file.\n");
        return 1;
    }

    if(fwrite(&bin_header.tga_header, sizeof(TGAHeader), 1, f_out) != 1){
        printf("Error writing TGA header.\n");
        fclose(f_in);
        fclose(f_out);
        return 1;
    }

    if (fwrite(img_data, sizeof(Pixel) * width * height, 1, f_out) != 1)
    {
        printf("Error writing image data.\n");
        fclose(f_in);
        fclose(f_out);
        return 1;

    }

    free(img_data);
    g_byte_array_free(byte_array, true);
    fclose(f_out);
    fclose(f_in);

    return 0;
}