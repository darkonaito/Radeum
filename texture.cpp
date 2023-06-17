#include "texture.hpp"
#include "pixel.hpp"
#include <filesystem>
#include <iostream>
#include "resourceloader.hpp"

rdm::types::Texture::Texture(const Size t_size):
    size(t_size)
{
    allocate();
}

rdm::types::Texture::Texture(const std::string_view& t_path)
{
    ResourceLoader::loadFromFile(*this, t_path);
}

rdm::types::Texture::Texture(const Texture& t_txt)
{
    size = t_txt.size;

    allocate();

    for(BigCounter i {}; i < size.x; ++i)
    {
        for(BigCounter j {}; j < size.y; ++j)
        {
            pixels[i][j] = t_txt.pixels[i][j];
        }
    }
}

rdm::types::Texture::Texture(Texture&& t_txt)
{
    size = t_txt.size;
    pixels = t_txt.pixels;

    t_txt.pixels = nullptr;
}

rdm::types::Texture& rdm::types::Texture::operator=(const Texture& t_txt)
{
    if(size != t_txt.size)
    {
        reallocate(t_txt.size);
    }

    for(BigCounter i {}; i < size.x; ++i)
    {
        for(BigCounter j {}; j < size.y; ++j)
        {
            pixels[i][j] = t_txt.pixels[i][j];
        }
    }

    return *this;
}

rdm::types::Texture& rdm::types::Texture::operator=(Texture&& t_txt)
{
    if(&t_txt != this)
    {
        deallocate();

        size = t_txt.size;

        pixels = t_txt.pixels;

        t_txt.pixels = nullptr;
    }

    return *this;
}

const rdm::types::Pixel* rdm::types::Texture::operator[](const BigCounter t_x) const
{
    return pixels[t_x];
}

rdm::types::Pixel* rdm::types::Texture::operator[](const BigCounter t_x) 
{
    return pixels[t_x];
}

rdm::types::Size rdm::types::Texture::getSize() const
{
    return size;
}

rdm::types::Texture& rdm::types::Texture::fill(const Pixel t_pxl)
{
    for(BigCounter i {}; i < size.x; ++i)
    {
        for(BigCounter j {}; j < size.y; ++j)
        {
            pixels[i][j] = t_pxl;
        }
    }

    return *this;
}

rdm::types::Texture& rdm::types::Texture::rotate(short t_x)
{
    if(t_x == 0)
    {
        return *this;
    }

    Texture rotated_texture {size};

    if(t_x < 0)
    {
        t_x *= -3;
    }

    for(BigCounter i {}; i < size.x; ++i)
    {
        for(BigCounter j {}; j < size.y; ++j)
        {
            rotated_texture[size.x - j - 1][i] = pixels[i][j];
        }
    }

    *this = std::move(rotated_texture);

    rotate(t_x - 1);
}

rdm::types::Texture& rdm::types::Texture::mirror(const Way t_way)
{
    Texture mirrored_txt {size};

    if(t_way == Way::VERTICALLY)
    {
        for(BigCounter i {}; i < size.x; ++i)
        {
            for(BigCounter j {}; j < size.y; ++j)
            {
                mirrored_txt[i][j] = pixels[size.x - i - 1][j];
            }
        }
    } else if(t_way == Way::HORIZONTALLY)
    {
        for(BigCounter i {}; i < size.x; ++i)
        {
            for(BigCounter j {}; j < size.y; ++j)
            {
                mirrored_txt[i][j] = pixels[i][size.y - j - 1];
            }
        }
    }

    *this = std::move(mirrored_txt);

    return *this;
}

rdm::types::Texture rdm::types::Texture::sample(const Size t_start, const Size t_size) const
{
    Texture sampled_txt {t_size};

    for(BigCounter i {}; i < t_size.x; ++i)
    {
        for(BigCounter j {}; j < t_size.y; ++j)
        {
            sampled_txt[i][j] = pixels[i + t_start.x][j + t_start.y];
        }
    }

    return sampled_txt;
}

void rdm::types::Texture::allocate()
{
    pixels = new Pixel*[size.x];

    for(size_t i {}; i < size.x; ++i)
    {
        pixels[i] = new Pixel[size.y];
    }
}

void rdm::types::Texture::deallocate()
{
    if(pixels != nullptr)
    {
        for(size_t i {}; i < size.x; ++i)
        {
            delete [] pixels[i];
        }
    
        delete [] pixels;

        pixels = nullptr;
    }
}

void rdm::types::Texture::reallocate(const Size t_size)
{
    deallocate();

    size = t_size;

    allocate();
}

rdm::types::Texture::~Texture()
{
    deallocate();
}