#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <glib-2.0/glib.h>
#include "common.h"


int real_index(int x, int y, int w){
    return y * w + x;
}

int compare_pixels(Pixel p1, Pixel p2){
    return abs(p1.red - p2.red) + abs(p1.green - p2.green) + abs(p1.blue - p2.blue);
}

GArray* compress_block(Pixel* pixels, int block_size, int width, int max_diff){
    GArray* result = g_array_new(false, true, sizeof(Seq));
    Pixel last_pixel = pixels[0];
    Seq sequence = {
        .red = last_pixel.red,
        .green = last_pixel.green,
        .blue = last_pixel.blue,
        .count = 1
    };
    for (int y = 0; y < block_size; ++y) {
        for (int x = 0; x < block_size; ++x) {
            if (y == 0 && x == 0){
                continue;
            }
            int i = real_index(x, y, width);
            if ((compare_pixels(last_pixel, pixels[i]) <= max_diff) && (sequence.count < 255)){
                sequence.count ++;
            }else{
                g_array_append_val(result, sequence);
                sequence.red = pixels[i].red;
                sequence.green = pixels[i].green;
                sequence.blue = pixels[i].blue;
                sequence.count = 1;
            }
            last_pixel = pixels[i];
        }
    }
    g_array_append_val(result, sequence);
    return result;
}

int compress(char* in_path, char* out_path, unsigned short block_size, int max_diff){

    FILE* f_in = fopen(in_path, "rb");
    if(f_in == NULL){
        printf("Error opening input file.\n");
        return 1;
    }

    TGAHeader img_header = {};
    if(fread(&img_header, sizeof(TGAHeader), 1, f_in) != 1)
    {
        printf("Error reading TGA header.\n");
        fclose(f_in);
        return 1;
    }

    unsigned short width = (img_header.width[1] << 8) | img_header.width[0];
    unsigned short height = (img_header.height[1] << 8) | img_header.height[0];

    if (width % block_size != 0 || height % block_size != 0){
        printf("Incompatible image size.\n");
        return 1;
    }

    if (img_header.image_type == 2 && img_header.depth == 24){

        FILE* f_out = fopen(out_path, "wb");
        if(f_out == NULL){
            printf("Error opening output file.\n");
            return 1;
        }

        BinHeader bin_header = {
                .tga_header = img_header,
                .block_size = block_size
        };
        if(fwrite(&bin_header, sizeof(BinHeader), 1, f_out) != 1){
            printf("Error writing binary header.\n");
            fclose(f_in);
            fclose(f_out);
            return 1;

            return 1;
        }

        Pixel* data = malloc(sizeof(Pixel) * width * height);
        if(fread(data, sizeof(Pixel) * width * height, 1, f_in) != 1){
            printf("Error reading image data.\n");
            fclose(f_in);
            return 1;

        }

        for (int y = 0; y < height; y+=block_size){
            for (int x = 0; x < width; x+=block_size){
                GArray* block = compress_block(&data[real_index(x, y, width)], block_size, width, max_diff);

                if (fwrite(block->data, block->len * sizeof(Seq), 1, f_out) != 1)
                {
                    printf("Error writing data.\n");
                    fclose(f_in);
                    fclose(f_out);
                    return 1;
                }
                g_array_free(block, true);
            }
        }

        fseek(f_in, 0, SEEK_END);
        long init_size = ftell(f_in);
        fseek(f_out, 0, SEEK_END);
        long comp_size = ftell(f_out);

        printf("initial size: %ld\n", init_size);
        printf("compressed size: %ld\n", comp_size);

        printf("ratio: %ld%%\n", comp_size /(init_size / 100));

        free(data);
        fclose(f_out);

    }else{
        printf("Incompatible image type or color depth.\n");
        return 1;
    }

    fclose(f_in);

    return 0;
}