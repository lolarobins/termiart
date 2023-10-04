#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

#include <png.h>

#include <termiart/dots.h>
#include <termiart/ascii.h>

// reads png file to rgba buffer
// error writes to 512 byte char buf
uint8_t read_png(char *error, FILE *input_file, unsigned char **input_rgba, uint32_t *width, uint32_t *height)
{
    // read and verify png signature
    unsigned char sig[8];
    fread(sig, 1, 8, input_file);
    if (!png_check_sig(sig, 8))
    {
        if (error)
            strncpy(error, "cannot open png file: invalid png signature\n", 512);
        return 0;
    }

    png_structp read_png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!read_png)
    {
        if (error)
            strncpy(error, "cannot open png file: png_create_read_struct failed\n", 512);
        return 0;
    }

    png_infop info_png = png_create_info_struct(read_png);
    if (!info_png)
    {
        png_destroy_read_struct(&read_png, NULL, NULL);

        if (error)
            strncpy(error, "cannot open png file: png_create_info_struct failed\n", 512);
        return 0;
    }

    png_init_io(read_png, input_file);
    png_set_sig_bytes(read_png, 8);
    png_read_info(read_png, info_png);

    // image header info
    int bit_depth, color_type;
    png_get_IHDR(read_png, info_png, width, height, &bit_depth, &color_type, NULL, NULL, NULL);

    // convert to proper RGBA 8888
    // https://gist.github.com/niw/5963798
    if (bit_depth == 16)
        png_set_strip_16(read_png);

    if (color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_palette_to_rgb(read_png);

    if (color_type == PNG_COLOR_TYPE_GRAY && bit_depth < 8)
        png_set_expand_gray_1_2_4_to_8(read_png);

    if (png_get_valid(read_png, info_png, PNG_INFO_tRNS))
        png_set_tRNS_to_alpha(read_png);

    if (color_type == PNG_COLOR_TYPE_RGB ||
        color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_PALETTE)
        png_set_filler(read_png, 0xFF, PNG_FILLER_AFTER);

    if (color_type == PNG_COLOR_TYPE_GRAY ||
        color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(read_png);

    png_read_update_info(read_png, info_png);

    // allocate rgba array for program
    *input_rgba = malloc(png_get_rowbytes(read_png, info_png) * *height);

    // set pointers to pass to libpng
    png_byte **row_pointers = (png_byte **)malloc(sizeof(png_bytep) * *height);
    for (int y = 0; y < *height; y++)
        row_pointers[y] = &input_rgba[0][y * png_get_rowbytes(read_png, info_png)];

    png_read_image(read_png, row_pointers);

    // cleanup png read
    free(row_pointers);
    png_destroy_read_struct(&read_png, &info_png, NULL);

    return 1;
}

int main(int argc, char *argv[])
{
    // !! goto statements used for jumping down to cleanup routine to exit !! //

    // user inputs
    char *input = NULL, *output = NULL, *font = NULL, *color_opts = NULL;
    uint8_t input_type = 0, pattern = 0;
    // rgba buffer from loaded/generated image
    unsigned char *input_rgba = NULL;
    // file pointers to use
    FILE *input_file = NULL, *output_file = NULL;
    // loaded image properties
    uint32_t width = 0, height = 0;
    // buffer for error handling
    char error_buf[512];
    error_buf[0] = 0;

    // <- parse options -> //
    static struct option cmd_opts[] = {
        {"version", no_argument, 0, 'v'}, // version

        {"input", required_argument, 0, 'i'}, // input
        {"type", required_argument, 0, 't'},  // input type

        {"font", required_argument, 0, 'f'}, // font options

        {"color", required_argument, 0, 'c'}, // color

        {"output", required_argument, 0, 'o'}, // output file

        {"pattern", required_argument, 0, 'p'}, // character pattern

        {0, 0, 0, 0} // null terminator
    };

    for (int c = 0, index = 0; c != -1;)
    {
        c = getopt_long(argc, argv, "vi:t:f:c:m:o:p:", cmd_opts, &index);

        switch (c)
        {
            // no opts
        case -1:
            break;

        // version
        case 'v':
            printf("termiart version %s\n", _PROG_VERSION);
            goto cleanup;

        // input
        case 'i':
            // file input/string input
            input = strdup(optarg);
            break;
        // input type
        case 't':
            // valid options: png
            if (!strcmp(optarg, "png"))
                input_type = 0;
            else
            {
                snprintf(error_buf, 512, "invalid file type option %s\nvalid options: png\n", optarg);
                goto cleanup;
            }
            break;

        // font options
        case 'f':
            fprintf(stderr, "!! font feature not supported yet !!\n");
            font = strdup(optarg);
            break;

        // color
        case 'c':
            color_opts = strdup(optarg);
            break;

        // output
        case 'o':
            output = strdup(optarg);
            break;

        // pattern
        case 'p':
            // valid options: dots, ascii
            if (!strcmp(optarg, "dots"))
                pattern = 0;
            else if (!strcmp(optarg, "ascii"))
                pattern = 1;
            else
            {
                snprintf(error_buf, 512, "invalid pattern option %s\nvalid options: dots\n", optarg);
                goto cleanup;
            }
            break;

        // invalid option
        default:
            goto cleanup;
        }
    }

    // no input specified
    if (!input)
    {
        strncpy(error_buf, "no input file specified\n", 512);
        goto cleanup;
    }

    // <- handle inputs -> //
    if (input_type == 0) // PNG
    {
        // open file
        input_file = fopen(input, "r");
        if (!input_file)
        {
            snprintf(error_buf, 512, "cannot open file %s\n", input);
            goto cleanup;
        }

        // load rgba from png file
        read_png(error_buf, input_file, &input_rgba, &width, &height);

        if (error_buf[0])
            goto cleanup;
    }

    // <- output -> //
    output_file = output ? fopen(output, "a") : stdout;
    if (!output_file)
    {
        snprintf(error_buf, 512, "cannot write to file %s\n", input);
        goto cleanup;
    }

    switch (pattern)
    {
    // dot pattern
    case 0:
        dots_from_rgba(error_buf, output_file, input_rgba, width, height, color_opts);
        break;
    case 1:
        ascii_from_rgba(error_buf, output_file, input_rgba, width, height, color_opts);
        break;
    }

cleanup:
    if (input)
        free(input);
    if (input_file)
        fclose(input_file);
    if (input_rgba)
        free(input_rgba);
    if (output)
    {
        free(output);
        if (output_file)
            fclose(output_file);
    }
    if (font)
        free(font);
    if (color_opts)
        free(color_opts);

    // if text was put in, error occured
    if (error_buf[0])
    {
        fprintf(stderr, "%s", error_buf);
        return 1;
    }

    return 0;
}
