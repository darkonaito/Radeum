#ifndef D_BUFFERLOADER_HPP
#define D_BUFFERLOADER_HPP

#include "types.hpp"
#include <string_view>

class rdm::types::ResourceLoader
{
    public:
        // Load texture from file
        static void loadFromFile(Texture&, const std::string_view&);

        // Save texture to file
        static void saveToFile(const Texture&, const std::string_view&);

    private:
        // Load file into memory
        static char* loadFile(const std::string_view& file_path);

        // Write momory section to file
        static void  writeFile(const char* const content, const size_t size, const std::string_view& file_path);
};

#endif