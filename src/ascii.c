#include <stdio.h>
#include <stdint.h>
#include <string.h>

// order of characters by 'brightness' (https://stackoverflow.com/a/74186686)
const char ascii_order[] = "`.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@";

const float ascii_brightness[] = {0.0f, 0.0651f, 0.0829f, 0.0848f, 0.1227f, 0.1403f, 0.1559f, 0.185f, 0.2183f, 0.2417f,
                                  0.2571f, 0.2852f, 0.2902f, 0.2919f, 0.3099f, 0.3192f, 0.3232f, 0.3294f, 0.3384f, 0.3609f,
                                  0.3619f, 0.3667f, 0.3737f, 0.3747f, 0.3838f, 0.3921f, 0.396f, 0.3984f, 0.3993f, 0.4075f,
                                  0.4091f, 0.4101f, 0.42f, 0.423f, 0.4247f, 0.4274f, 0.4293f, 0.4328f, 0.4382f, 0.4385f,
                                  0.442f, 0.4473f, 0.4477f, 0.4503f, 0.4562f, 0.458f, 0.461f, 0.4638f, 0.4667f, 0.4686f,
                                  0.4693f, 0.4703f, 0.4833f, 0.4881f, 0.4944f, 0.4953f, 0.4992f, 0.5509f, 0.5567f, 0.5569f,
                                  0.5591f, 0.5602f, 0.5602f, 0.565f, 0.5776f, 0.5777f, 0.5818f, 0.587f, 0.5972f, 0.5999f,
                                  0.6043f, 0.6049f, 0.6093f, 0.6099f, 0.6465f, 0.6561f, 0.6595f, 0.6631f, 0.6714f, 0.6759f,
                                  0.6809f, 0.6816f, 0.6925f, 0.7039f, 0.7086f, 0.7235f, 0.7302f, 0.7332f, 0.7802f, 0.8234f,
                                  0.9037f, 0.9999f};

uint8_t ascii_from_rgba(char *error, FILE *stream, const uint8_t *rgba, uint32_t width, uint32_t height, const char *color_opts)
{
    // color opts (same as dots.c)
    uint8_t color_mode = 0, bold = 0, inverse = 0;

    if (color_opts)
        for (int i = 0, len = 0;; i++)
        {
            if (color_opts[i] == '-' || color_opts[i] == '\0')
            {
                if (!strncmp(&color_opts[i - len], "truecolor", 9))
                    color_mode = 1;
                else if (!strncmp(&color_opts[i - len], "inverse", 7))
                    inverse = 1;
                else if (!strncmp(&color_opts[i - len], "bold", 4))
                    bold = 1;
                else
                {
                    snprintf(error, 512, "invalid color option %s specified for ascii patterns\nvalid options: truecolor, bold, inverse\n", color_opts);
                    return 0;
                }

                if (color_opts[i] == '\0')
                    break;
                else
                    len = 0;
            }
            else
                len++;
        }

    // 2x4 chunks (similar to dots.c)
    for (int y = 0; y < height; y += 4)
    {
        uint8_t last_r = 0, last_g = 0, last_b = 0, set = 0;

        for (int x = 0; x < width; x += 2)
        {
            // mask to pass to dot array
            uint8_t mask = 0;
            uint16_t r = 0, g = 0, b = 0, sample = 0;

            for (int bx = 0; bx < (width - x < 2 ? width - x : 2); bx++)
                for (uint32_t by = 0; by < (height - y < 4 ? height - y : 4); by++)
                {
                    const uint8_t *color = &rgba[(((y + by) * width) + (x + bx)) * 4];

                    if (color[3])
                    {
                        mask |= 1 << ((bx * 4) + by);

                        // uses colors to determine character brightness
                        r += color[0];
                        g += color[1];
                        b += color[2];
                        sample++;
                    }
                }

            // if character to print (any non-transparent pixels)
            if (sample)
            {
                // calculate average
                r = r / sample;
                g = g / sample;
                b = b / sample;

                // handle changes for color printing
                if (color_mode && (last_r != r || last_g != g || last_b != b || !set))
                {
                    last_r = r;
                    last_g = g;
                    last_b = b;
                    set = 1;

                    // print color codes
                    switch (color_mode)
                    {
                    case 1:
                        fprintf(stream, "\033[38;2;%d;%d;%dm%s", r, g, b, bold ? "\033[1m" : "");
                        break;
                    }
                }

                // match character
                // rec 709 luma
                float luminance = (((float)r / 256) * 0.2126) +
                                  (((float)g / 256) * 0.7152) +
                                  (((float)b / 256) * 0.0722);

                uint8_t position = 0;
                for (; position < sizeof(ascii_order) - 1 && luminance >= ascii_brightness[position]; position++)
                    ;
                fputc(ascii_order[inverse ? sizeof(ascii_order) - position - 1 : position - 1], stream);

                // reset
                r = 0;
                g = 0;
                b = 0;
                sample = 0;
            }
            // nothing here.
            else
            {
                fputc(' ', stream);
            }
        }

        // print reset (if needed) and newline
        fprintf(stream, "%s\n", color_mode ? "\033[0m" : "");
    }

    return 1;
}
