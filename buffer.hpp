#ifndef D_BUFFER_HPP
#define D_BUFFER_HPP

#include <windows.h>

#include "types.hpp"
#include "coords.hpp"
#include "pixel.hpp"

class rdm::types::Buffer
{
    public:
        /*** Constructors ***/

        // Fixed buffer size
        Buffer(Size);

        // Fill buffer with pixel
        void fill(Pixel = Pixel{});

        // Set buffer pixel
        bool setPixel(Size, Pixel);

        // Get buffer size
        Size getSize() const;

        // Get CHAR_INFO buffer pointer
        CHAR_INFO* getBuffer() const;

        // Loop through pixels...
        bool operator==(const Buffer&);

        /*** Destructor ***/

        ~Buffer();

    private:
        const Size size;
        CHAR_INFO* const buffer;

        // Convert x;y coords to buffer index
        size_t coordsToIndex(Size) const;
};


#endif