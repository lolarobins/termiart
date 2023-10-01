#include <stdint.h>
#include <string.h>

#include <termiart/dots.h>

// const string dot patterns for printing
const char *dot_patterns[256] = {
    // 0b00000XXX
    " ", // use space as first char
    "\u2801",
    "\u2802",
    "\u2803",
    "\u2804",
    "\u2805",
    "\u2806",
    "\u2807",

    // 0b0000XXXX
    "\u2840",
    "\u2841",
    "\u2842",
    "\u2843",
    "\u2844",
    "\u2845",
    "\u2846",
    "\u2847",

    // 0b000X0XXX
    "\u2808",
    "\u2809",
    "\u280A",
    "\u280B",
    "\u280C",
    "\u280D",
    "\u280E",
    "\u280F",

    // 0b000XXXXX
    "\u2848",
    "\u2849",
    "\u284A",
    "\u284B",
    "\u284C",
    "\u284D",
    "\u284E",
    "\u284F",

    // 0b00X00XXX
    "\u2810",
    "\u2811",
    "\u2812",
    "\u2813",
    "\u2814",
    "\u2815",
    "\u2816",
    "\u2817",

    // 0b00X0XXXX
    "\u2850",
    "\u2851",
    "\u2852",
    "\u2853",
    "\u2854",
    "\u2855",
    "\u2856",
    "\u2857",

    // 0b00XX0XXX
    "\u2818",
    "\u2819",
    "\u281A",
    "\u281B",
    "\u281C",
    "\u281D",
    "\u281E",
    "\u281F",

    // 0b00XXXXXX
    "\u2858",
    "\u2859",
    "\u285A",
    "\u285B",
    "\u285C",
    "\u285D",
    "\u285E",
    "\u285F",

    // 0b0X000XXX
    "\u2820",
    "\u2821",
    "\u2822",
    "\u2823",
    "\u2824",
    "\u2825",
    "\u2826",
    "\u2827",

    // 0b0X00XXXX
    "\u2860",
    "\u2861",
    "\u2862",
    "\u2863",
    "\u2864",
    "\u2865",
    "\u2866",
    "\u2867",

    // 0b0X0X0XXX
    "\u2828",
    "\u2829",
    "\u282A",
    "\u282B",
    "\u282C",
    "\u282D",
    "\u282E",
    "\u282F",

    // 0b0X0XXXXX
    "\u2868",
    "\u2869",
    "\u286A",
    "\u286B",
    "\u286C",
    "\u286D",
    "\u286E",
    "\u286F",

    // 0b0XX00XXX
    "\u2830",
    "\u2831",
    "\u2832",
    "\u2833",
    "\u2834",
    "\u2835",
    "\u2836",
    "\u2837",

    // 0b0XX0XXXX
    "\u2870",
    "\u2871",
    "\u2872",
    "\u2873",
    "\u2874",
    "\u2875",
    "\u2876",
    "\u2877",

    // 0b0XXX0XXX
    "\u2838",
    "\u2839",
    "\u283A",
    "\u283B",
    "\u283C",
    "\u283D",
    "\u283E",
    "\u283F",

    // 0b0XXXXXXX
    "\u2878",
    "\u2879",
    "\u287A",
    "\u287B",
    "\u287C",
    "\u287D",
    "\u287E",
    "\u287F",

    // 0bX0000XXX
    "\u2880",
    "\u2881",
    "\u2882",
    "\u2883",
    "\u2884",
    "\u2885",
    "\u2886",
    "\u2887",

    // 0bX000XXXX
    "\u28C0",
    "\u28C1",
    "\u28C2",
    "\u28C3",
    "\u28C4",
    "\u28C5",
    "\u28C6",
    "\u28C7",

    // 0bX00X0XXX
    "\u2888",
    "\u2889",
    "\u288A",
    "\u288B",
    "\u288C",
    "\u288D",
    "\u288E",
    "\u288F",

    // 0bX00XXXXX
    "\u28C8",
    "\u28C9",
    "\u28CA",
    "\u28CB",
    "\u28CC",
    "\u28CD",
    "\u28CE",
    "\u28CF",

    // 0bX0X00XXX
    "\u2890",
    "\u2891",
    "\u2892",
    "\u2893",
    "\u2894",
    "\u2895",
    "\u2896",
    "\u2897",

    // 0bX0X0XXXX
    "\u28D0",
    "\u28D1",
    "\u28D2",
    "\u28D3",
    "\u28D4",
    "\u28D5",
    "\u28D6",
    "\u28D7",

    // 0bX0XX0XXX
    "\u2898",
    "\u2899",
    "\u289A",
    "\u289B",
    "\u289C",
    "\u289D",
    "\u289E",
    "\u289F",

    // 0bX0XXXXXX
    "\u28D8",
    "\u28D9",
    "\u28DA",
    "\u28DB",
    "\u28DC",
    "\u28DD",
    "\u28DE",
    "\u28DF",

    // 0bXX000XXX
    "\u28A0",
    "\u28A1",
    "\u28A2",
    "\u28A3",
    "\u28A4",
    "\u28A5",
    "\u28A6",
    "\u28A7",

    // 0bXX00XXXX
    "\u28E0",
    "\u28E1",
    "\u28E2",
    "\u28E3",
    "\u28E4",
    "\u28E5",
    "\u28E6",
    "\u28E7",

    // 0bXX0X0XXX
    "\u28A8",
    "\u28A9",
    "\u28AA",
    "\u28AB",
    "\u28AC",
    "\u28AD",
    "\u28AE",
    "\u28AF",

    // 0bXX0XXXXX
    "\u28E8",
    "\u28E9",
    "\u28EA",
    "\u28EB",
    "\u28EC",
    "\u28ED",
    "\u28EE",
    "\u28EF",

    // 0bXXX00XXX
    "\u28B0",
    "\u28B1",
    "\u28B2",
    "\u28B3",
    "\u28B4",
    "\u28B5",
    "\u28B6",
    "\u28B7",

    // 0bXXX0XXXX
    "\u28F0",
    "\u28F1",
    "\u28F2",
    "\u28F3",
    "\u28F4",
    "\u28F5",
    "\u28F6",
    "\u28F7",

    // 0bXXXX0XXX
    "\u28B8",
    "\u28B9",
    "\u28BA",
    "\u28BB",
    "\u28BC",
    "\u28BD",
    "\u28BE",
    "\u28BF",

    // 0bXXXXXXXX
    "\u28F8",
    "\u28F9",
    "\u28FA",
    "\u28FB",
    "\u28FC",
    "\u28FD",
    "\u28FE",
    "\u28FF",
};

// build image from 2x4 unicode dot patterns
uint8_t dots_from_rgba(char *error, FILE *stream, const uint8_t *rgba, uint32_t width, uint32_t height, const char *color_opts)
{
    // handle color options
    uint8_t color_mode = 0, bold = 0;

    if (color_opts)
    {
        // truecolor
        if (!strcmp(color_opts, "truecolor"))
            color_mode = 1;
        else if (!strcmp(color_opts, "truecolor-bold"))
        {
            bold = 1;
            color_mode = 1;
        }
        else
        {
            snprintf(error, 512, "invalid color option %s specified for dot patterns\nvalid options: truecolor, truecolor-bold\n", color_opts);
            return 0;
        }
    }

    // analyze in 2x4 chunks
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

                    // any color detected (alpha != 0)
                    if (color[3])
                    {
                        mask |= 1 << ((bx * 4) + by);

                        if (color_mode)
                        {
                            r += color[0];
                            g += color[1];
                            b += color[2];
                            sample++;
                        }
                    }
                }

            // colors detected + using color
            if (sample)
            {
                // calculate average
                r = r / sample;
                g = g / sample;
                b = b / sample;

                // handle changes
                if (last_r != r || last_g != g || last_b != b || !set)
                {
                    last_r = r;
                    last_g = g;
                    last_b = b;
                    set = 1;

                    switch (color_mode)
                    {
                    // truecolor
                    case 1:
                        fprintf(stream, "\033[38;2;%d;%d;%dm%s", r, g, b, bold ? "\033[1m" : "");
                        break;
                    }
                }

                // reset
                r = 0;
                g = 0;
                b = 0;
                sample = 0;
            }

            fprintf(stream, "%s", dot_patterns[mask]);
        }

        // print reset (if needed) and newline
        fprintf(stream, "%s\n", color_mode ? "\033[0m" : "");
    }

    return 1;
}
