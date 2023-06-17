#ifndef D_TEXTURE_HPP
#define D_TEXTURE_HPP

#include <string_view>
#include "types.hpp"
#include "coords.hpp"

class rdm::types::Texture
{
    friend class rdm::types::ResourceLoader;
    friend class rdm::types::Frame;

    public:
        enum class Way
        {
            HORIZONTALLY,
            VERTICALLY
        };

        Texture() = default;

        // Construct by size
        Texture(const Size size);
        
        // Construct by file
        Texture(const std::string_view& file_path);

        // Copy constructor
        Texture(const Texture& texture);

        // Move constructor
        Texture(Texture&& texture);

        // Copy Assigment operator
        Texture& operator=(const Texture& texture);

        // Move Assigment operator
        Texture& operator=(Texture&& texture);

        // Access operator
        const Pixel* operator[](BigCounter x) const;
        Pixel*       operator[](BigCounter x);
        
        /*** Methods ***/

        // Fill with pixel
        Texture& fill(const Pixel pixel);

        // Get texture size
        Size getSize() const;

        // Rotate
        Texture& rotate(short times);

        // Mirror 
        Texture& mirror(Way way);

        // Sample texture portion
        Texture sample(Size start, Size size) const;


        /*** Destructor ***/
        ~Texture();

    protected:
        Size size;

        Pixel** pixels {nullptr};

        void allocate();
        void deallocate();

        void reallocate(const Size new_size);
};

#endif