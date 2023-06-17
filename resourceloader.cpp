#include "resourceloader.hpp"
#include "texture.hpp"
#include "pixel.hpp"

#include <type_traits>
#include <fstream>
#include <filesystem>
#include <iostream>

char* rdm::types::ResourceLoader::loadFile(const std::string_view& t_path)
{
    // Static local input file stream
    static std::ifstream file;

    // Open file in binary-input mode
    file.open(std::string(t_path), std::ios::binary | std::ios::in);

    // Get file size in bytes
    const auto file_size {std::filesystem::file_size(t_path)};

    // Allocate space for the file to be read to
    char* const file_content {new char[file_size]};

    // Read whole file
    file.read(file_content, file_size);

    // Close file
    file.close();

    // Return file content address 
    return file_content;
}

void rdm::types::ResourceLoader::writeFile(const char* const t_content, const size_t t_size, const std::string_view& t_path)
{
    // Static local output file stream
    static std::ofstream file;

    // Open file stream in binary-output mode
    file.open(std::string(t_path), std::ios::binary | std::ios::out | std::ios::trunc);

    // Write specified size of memory location to file
    file.write(t_content, t_size);

    // Close file
    file.close();
}

void rdm::types::ResourceLoader::saveToFile(const Texture& t_texture, const std::string_view& t_path)
{
    // Get texture size
    const auto texture_size {t_texture.getSize()};

    // Alias for texture_size type without const qualifier
    using texture_size_pure_type = std::remove_const<decltype(texture_size)>::type; 

    // Calculate size for texture data
    const size_t data_size {
        sizeof(texture_size_pure_type) + sizeof(Pixel) * texture_size.x * texture_size.y
    };

    // Allocate space for texture data
    char* const texture_data {new char[data_size]};

    // Write texture size to memory using casts
    *(static_cast<texture_size_pure_type*>(static_cast<void*>(texture_data))) = texture_size;

    // Texture pixels pointer
    Pixel* pixel_pointer {static_cast<Pixel*>(static_cast<void*>(texture_data + sizeof(texture_size_pure_type)))};

    // Read texture pixels to memory
    for(size_t i {}; i < texture_size.x; ++i)
    {
        for(size_t j {}; j < texture_size.y; ++j)
        {
            pixel_pointer[i + j * texture_size.x] = t_texture.pixels[i][j];
        }
    }

    // Write memory to file
    writeFile(texture_data, data_size, t_path);

    // Deallocate memory
    delete[] texture_data;
}

void rdm::types::ResourceLoader::loadFromFile(Texture& t_texture, const std::string_view& t_path)
{
    // Load data into memory
    const char* const texture_data {loadFile(t_path)};

    // Read new size and reallocate
    t_texture.reallocate(
        *(static_cast<const decltype(t_texture.size)*>(static_cast<const void*>(texture_data)))
    );

    // Texture pixels pointer
    const Pixel* const pixel_pointer {static_cast<const Pixel*>(static_cast<const void*>(texture_data + sizeof(t_texture.size)))};

    // Read texture pixels
    for(size_t i {}; i < t_texture.size.x; ++i)
    {
        for(size_t j {}; j < t_texture.size.y; ++j)
        {
            t_texture.pixels[i][j] = pixel_pointer[i + j * t_texture.size.x];
        }
    }

    // Deallocate memory
    delete[] texture_data;
}