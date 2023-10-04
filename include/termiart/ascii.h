#ifndef _TA_ASCII_H_
#define _TA_ASCII_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdio.h>
#include <stdint.h>

    /// print an ascii image to a file stream from an image buffer
    ///
    /// @param error 512B error buffer that will be printed to if an error occurs
    /// @param stream file stream to output to (buffered)
    /// @param rgba 8 bit depth image buffer with alpha channel (8888RGBA)
    /// @param width image width
    /// @param height image height
    /// @param color_opts output color options (null = no color)
    ///
    /// @return non-zero if success
    extern uint8_t ascii_from_rgba(char *error, FILE *stream, const uint8_t *rgba, uint32_t width, uint32_t height, const char *color_opts);

#ifdef __cplusplus
}
#endif

#endif
