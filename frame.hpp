#ifndef D_FRAME_HPP
#define D_FRAME_HPP

#include "types.hpp"
#include "coords.hpp"
#include "texture.hpp"
#include "console.hpp"
#include "abstracts.hpp"

#include <utility>

// Inherits from texture (for size, pixels, getSize(), etc)

class rdm::types::Frame : public rdm::types::Texture 
{
    public:
        // Frame (size)
        Frame(const Size size);

        // Copy Constructor
        Frame(const Frame& frame);

        // Move constructor
        Frame(const Frame&& frame);

        // Copy assignment
        Frame& operator=(const Frame& frame);

        // Move assignment
        Frame& operator=(const Frame&& frame);

        // Draw raw texture
        Frame& operator<<(const std::pair<const Texture&, const Size>& texture_n_coords);

        // Draw frame
        Frame& operator<<(const std::pair<const Frame&, const Camera&>& frame_n_cam);

        // Draw line
        Frame& operator<<(Line line);

        // Draw points structure
        Frame& operator<<(const PointsStructure& points_structure);

        // Draw points structure
        Frame& operator<<(const FilledPointsStructure& filled_points_structure);

        // Draw rectangle
        Frame& operator<<(const Rectangle& hollow_rectangle);

        // Draw draw filled rectangle
        Frame& operator<<(const FilledRectangle& filled_rectangle);

        // Draw colored text
        Frame& operator<<(const std::pair<const HorizontalText&, const Size>& text_n_coords);
        Frame& operator<<(const std::pair<const VerticalText&, const Size>& text_n_coords);

        // Draw drawable object
        Frame& operator<<(const rdm::abstr::Drawable& drawable_object);

        // Set pixel
        void setPixel(const Size coords, const Pixel pixel);

        // Resize 
        void resize(Size   absolute_size);
        void resize(Coords relative_size);

        // Flush to console
        void flush(Console& console);

        // Fill buffer
        void fill(const Pixel pixel);

        // Clear buffer
        void clear();

        // Show center
        void drawCenter(const Pixel pixel);

        // Get center
        Size getCenter() const;

        // Convert coords
        Size coords(const Size coords) const;

    private:
        char flags {0x1};

        
};


#endif