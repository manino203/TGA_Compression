#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "common.h"


int main(int argc, char** argv){
    int c;
    int option_index = 0;
    char *input_file = NULL;
    char *output_file = NULL;
    unsigned short block_size = 0;
    int max_diff = 0;
    if (argc < 2){
        printf("Wrong input.\n");
        return 1;
    }
    if(strcmp(argv[1], "compress") == 0){
        if(argc != 10){
            printf("Wrong input.\n");
            return 1;
        }else{
            struct option long_options[] = {
                    {"input", required_argument, 0, 'i'},
                    {"output", required_argument, 0, 'o'},
                    {"block-size", required_argument, 0, 'b'},
                    {"max-diff", required_argument, 0, 'm'},
                    {0, 0, 0, 0}
            };
            while ((c = getopt_long(argc, argv, "i:o:b:m:", long_options, &option_index)) != -1) {
                char* endptr;
                long val;
                switch (c) {
                    case 'i':
                        input_file = optarg;
                        break;
                    case 'o':
                        output_file = optarg;
                        break;
                    case 'b':
                        val = strtol(optarg, &endptr, 10);
                        if (*endptr != '\0' || optarg == endptr) {
                            printf("Wrong input.\n");
                            return 1;
                        } else {
                            block_size = val;
                        }
                        break;
                    case 'm':
                        val = strtol(optarg, &endptr, 10);
                        if (*endptr != '\0' || optarg == endptr) {
                            printf("Wrong input.\n");
                            return 1;
                        } else {
                            max_diff = (int)val;
                        }
                        break;
                    case '?':
                        printf("Wrong input.\n");
                        return 1;
                    default:
                        abort();
                }
            }
            return compress(input_file, output_file, block_size, max_diff);
        }
    }else if(strcmp(argv[1], "decompress") == 0){
        if(argc != 6){
            printf("Wrong input.\n");
            return 1;
        }else{
            struct option long_options[] = {
                    {"input", required_argument, 0, 'i'},
                    {"output", required_argument, 0, 'o'},
                    {0, 0, 0, 0}
            };
            while ((c = getopt_long(argc, argv, "i:o", long_options, &option_index)) != -1) {
                switch (c) {
                    case 'i':
                        input_file = optarg;
                        break;
                    case 'o':
                        output_file = optarg;
                        break;
                    case '?':
                        printf("Wrong input.\n");
                        return 1;
                    default:
                        abort();
                }
            }
            return decompress(input_file,output_file);
        }
    }else{
        printf("Wrong input.\n");
        return 1;
    }
}
