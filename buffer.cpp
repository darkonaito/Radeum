#include "buffer.hpp"
#include "utils.hpp"

rdm::types::Buffer::Buffer(Size t_size):
    size(t_size),
    buffer(new CHAR_INFO[size.x * size.y])
{
}

rdm::types::Buffer::~Buffer()
{
    delete[] buffer;
}

bool rdm::types::Buffer::setPixel(Size t_coords, Pixel t_pxl)
{
    if(t_coords.bothAxesAreLesser(size))
    {
        buffer[coordsToIndex(t_coords)] = t_pxl.to_charinfo();

        return true;
    } else 
    {
        return false;
    }
}

rdm::types::Size rdm::types::Buffer::getSize() const
{
    return size;
}

CHAR_INFO* rdm::types::Buffer::getBuffer() const
{
    return buffer;
} 

void rdm::types::Buffer::fill(Pixel t_pxl)
{
    // Fill buffer with specified pixel
    for(size_t i {}; i < size.x * size.y; ++i)
    {
        buffer[i] = t_pxl.to_charinfo();
    }
}

bool rdm::types::Buffer::operator==(const Buffer& t_buff)
{
    if(size == t_buff.size)
    {
        for(size_t i {}; i < size.x * size.y; ++i)
        {
            if(t_buff.buffer[i].Attributes != buffer[i].Attributes || t_buff.buffer[i].Char.UnicodeChar != buffer[i].Char.UnicodeChar)
            {
                return false;
            }
        }
    } else 
    {
        return false;
    }

    return true;
}

size_t rdm::types::Buffer::coordsToIndex(Size t_coords) const
{
    return t_coords.x + t_coords.y * size.x;
}