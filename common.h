#ifndef TGA_COMPRESSION_COMMON_H
#define TGA_COMPRESSION_COMMON_H

typedef unsigned char byte;

typedef struct {
    byte id_length;
    byte color_map_type;
    byte image_type;
    byte color_map[5];
    byte x_origin[2];
    byte y_origin[2];
    byte width[2];
    byte height[2];
    byte depth;
    byte descriptor;
} TGAHeader;

typedef struct {
    TGAHeader tga_header;
    byte block_size[2];
} BinHeader;

typedef struct
{
    byte red;
    byte green;
    byte blue;
} Pixel;

typedef struct {
    byte red;
    byte green;
    byte blue;
    byte count;
} Seq;

int real_index(int x, int y, int w);

int compress(char* in_path, char* out_path, unsigned short block_size, int max_diff);

int decompress(char* in_path, char* out_path);

#endif //TGA_COMPRESSION_COMMON_H
