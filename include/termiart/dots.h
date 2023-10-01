#ifndef _TA_DOTS_H_
#define _TA_DOTS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdint.h>

    /// braille dot patterns in a static list based upon pattern to print
    /// position in array corresponds to 8-bit mask to draw
    ///
    /// 0b87654321
    /// -> 8 4
    /// -> 7 3
    /// -> 6 2
    /// -> 5 1
    extern const char *dot_patterns[256];

    /// print a dot image to a file stream from an image buffer
    ///
    /// @param error 512B error buffer that will be printed to if an error occurs
    /// @param stream file stream to output to (buffered)
    /// @param rgba 8 bit depth image buffer with alpha channel (8888RGBA)
    /// @param width image width
    /// @param height image height
    /// @param color_opts output color options (null = no color)
    ///
    /// @return non-zero if success
    extern uint8_t dots_from_rgba(char *error, FILE *stream, const uint8_t *rgba, uint32_t width, uint32_t height, const char *color_opts);

#ifdef __cplusplus
}
#endif

#endif
