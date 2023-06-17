#include "frame.hpp"
#include "buffer.hpp"
#include "camera.hpp"
#include "geometrics.hpp"
#include "texts.hpp"
#include "drawable.hpp"
#include <iostream>
#include <algorithm>
#include <limits>
#include <cmath>

rdm::types::Frame::Frame(const Size t_size):
    Texture(t_size)
{
}

rdm::types::Frame::Frame(const Frame& t_frame):
    Texture(t_frame),
    flags(1)
{
}

rdm::types::Frame::Frame(const Frame&& t_frame):
    Texture(std::move(t_frame)),
    flags(1)
{
}

rdm::types::Frame& rdm::types::Frame::operator=(const Frame& t_frame)
{
    if(t_frame.size != size)
    {
        reallocate(size);

        flags |= 1;
    }

    for(BigCounter i {}; i < size.x; ++i)
    {
        for(BigCounter j {}; j < size.y; ++j)
        {
            pixels[i][j] = t_frame.pixels[i][j];
        }
    }

    return *this;
}

rdm::types::Frame& rdm::types::Frame::operator=(const Frame&& t_frame)
{
    if(t_frame.size != size)
    {
        size = t_frame.size;
        
        flags |= 1;
    }

    pixels = t_frame.pixels;

    return *this;
}

void rdm::types::Frame::resize(const Size t_abs_size)
{
    // Reallocate pixel array with new size
    reallocate(t_abs_size);

    // Set size change flag
    flags |= 1;
}

void rdm::types::Frame::resize(const Coords t_rel_size)
{
    resize(size + t_rel_size);
}

void rdm::types::Frame::flush(Console& t_con)
{
    static Buffer* buffer;

    // Checks if frame has been resized
    if(flags & 0x1)
    {
        delete buffer;

        buffer = new Buffer{size};

        flags &= ~1;
    }

    // Fills buffer

    for(BigCounter i {}; i < size.x; ++i)
    {
        for(BigCounter j {}; j < size.y; ++j)
        {
            // Alt. "size.y - (j + 1)"
            buffer->setPixel({i, j}, pixels[i][j]);
        }
    }

    /*** Write buffer to console ***/

    t_con.drawBuffer(*buffer, {
        {0, 0}, size, {0, 0}
    });
}

rdm::types::Frame& rdm::types::Frame::operator<<(const PointsStructure& t_pnts_strct)
{
    for(size_t i {}; i < t_pnts_strct.points.size() - 1; ++i)
    {
        *this << Line{t_pnts_strct.points[i], t_pnts_strct.points[i + 1], t_pnts_strct.pxl};
    }

    *this << Line{t_pnts_strct.points[t_pnts_strct.points.size() - 1], t_pnts_strct.points[0], t_pnts_strct.pxl};

    return *this;
}

rdm::types::Frame& rdm::types::Frame::operator<<(const FilledPointsStructure& t_flld_pnts_strct)
{
    auto collectPixelOccourrencesOnY
    {
        [&](const BigCounter t_x, BigCounter t_start_y, const BigCounter t_end_y, const Pixel t_pxl)
            -> std::vector<Size>
        {
            std::vector<Size> points;

            for(; t_start_y <= t_end_y && t_start_y < this->size.y; ++t_start_y)
            {
                if(pixels[t_x][t_start_y] == t_pxl)
                {
                    points.push_back({t_x, t_start_y});
                }
            }

            return points;
        }
    };

    const Pixel signaling_pxl {static_cast<Color>(255), static_cast<Color>(255), 255};

    *this << PointsStructure{t_flld_pnts_strct.points, signaling_pxl};

    Size starting_point
    {
        std::min_element(
            t_flld_pnts_strct.points.begin(),
            t_flld_pnts_strct.points.end(),
            [](const Size t_p1, const Size t_p2)
            {
                return t_p1.x < t_p2.x; 
            }
        )->x,
        std::min_element(
            t_flld_pnts_strct.points.begin(),
            t_flld_pnts_strct.points.end(),
            [](const Size t_p1, const Size t_p2)
            {
                return t_p1.y < t_p2.y; 
            }
        )->y,
    };

    const Size ending_point
    {
        std::max_element(
            t_flld_pnts_strct.points.begin(),
            t_flld_pnts_strct.points.end(),
            [](const Size t_p1, const Size t_p2)
            {
                return t_p1.x < t_p2.x; 
            }
        )->x,
        std::max_element(
            t_flld_pnts_strct.points.begin(),
            t_flld_pnts_strct.points.end(),
            [](const Size t_p1, const Size t_p2)
            {
                return t_p1.y < t_p2.y; 
            }
        )->y,
    };

    for(BigCounter i {starting_point.x}; i <= ending_point.x && i < size.x; ++i)
    {
        const std::vector<Size> points {collectPixelOccourrencesOnY(i, starting_point.y, ending_point.y, signaling_pxl)};

        for(BigCounter j {}; j < points.size(); ++j)
        {
            if(!((points.size() - j) == 1))
            {
                *this << Line(points[j], points[j + 1], t_flld_pnts_strct.pxl);
            } else 
            {
                setPixel(points[j], t_flld_pnts_strct.pxl);
            }
        }
    }

    return *this;
}

rdm::types::Frame& rdm::types::Frame::operator<<(Line t_line)
{
    const double delta_x {static_cast<double>(t_line.p2.x - t_line.p1.x)};
    const double delta_y {static_cast<double>(t_line.p2.y - t_line.p1.y)};

    const double coeff {delta_y / delta_x};

    if(delta_x == 0)
    {
        if(t_line.p1.y > t_line.p2.y)
        {
            std::swap(t_line.p1, t_line.p2);
        }

        for(BigCounter i {t_line.p1.y}; i <= t_line.p2.y; ++i)
        {
            setPixel({t_line.p1.x, i}, t_line.pxl);
        }
    } else
    { 
        const double inv_abs_coeff {1.0 / std::abs(coeff)};
        
        if(t_line.p1.x > t_line.p2.x)
        {
            std::swap(t_line.p1, t_line.p2);
        }
        for(double i {}; i + t_line.p1.x <= t_line.p2.x; (inv_abs_coeff >= 1) ? ++i : (i += inv_abs_coeff))
        {
            setPixel({static_cast<BigCounter>(t_line.p1.x + std::round(i)), static_cast<BigCounter>(t_line.p1.y + std::round(i * coeff))}, t_line.pxl);
        }
    }

    return *this;
}

rdm::types::Size rdm::types::Frame::coords(const Size t_coords) const
{
    return {t_coords.x, static_cast<BigCounter>(size.y - t_coords.y)};
}

rdm::types::Frame& rdm::types::Frame::operator<<(const Rectangle& t_rect)
{
    const Size p2 {t_rect.p4.x, t_rect.p1.y};
    const Size p3 {t_rect.p1.x, t_rect.p4.y};

    *this
        << Line(t_rect.p1,        p2, t_rect.pxl)
        << Line(t_rect.p1,        p3, t_rect.pxl)
        << Line(       p2, t_rect.p4, t_rect.pxl)
        << Line(       p3, t_rect.p4, t_rect.pxl)
    ;

    return *this;
}

rdm::types::Frame& rdm::types::Frame::operator<<(const FilledRectangle& t_rect)
{
    for(BigCounter i {t_rect.p1.x}; i < t_rect.p4.x; ++i)
    {
        for(BigCounter j {t_rect.p1.y}; j < t_rect.p4.y; ++j)
        {
            setPixel({i, j}, t_rect.pxl);
        }
    }

    return *this;
}

rdm::types::Frame& rdm::types::Frame::operator<<(const std::pair<const Texture&, const Size>& t_txt_coords)
{
    const Size texture_size {t_txt_coords.first.getSize()};

    for(BigCounter i {}; i < texture_size.x; ++i)
    {
        for(BigCounter j {}; j < texture_size.y; ++j)
        {
            setPixel(
                {
                    static_cast<BigCounter>(i + t_txt_coords.second.x),
                    static_cast<BigCounter>(j + t_txt_coords.second.y)
                },
                t_txt_coords.first.pixels[i][j]
            );
        }
    }

   return *this;
}

rdm::types::Frame& rdm::types::Frame::operator<<(const std::pair<const Frame&, const Camera&>& t_frame_cam)
{
    const Size draw_area    {t_frame_cam.second.getDrawRegionArea()};
    const Size offset       {t_frame_cam.second.getBorderOffset()};
    const Size start_coords {t_frame_cam.second.getStartingCoords()};

    for(BigCounter i {}; i < draw_area.x; ++i)
    {
        for(BigCounter j {}; j < draw_area.y; ++j)
        {
            setPixel({static_cast<BigCounter>(i + offset.x), static_cast<BigCounter>(j + offset.y)}, t_frame_cam.first.pixels[i + start_coords.x][j + start_coords.y]);
        }
    }

    return *this;
}

rdm::types::Frame& rdm::types::Frame::operator<<(const std::pair<const HorizontalText&, const Size>& t_txt_coords)
{
    BigCounter y_offset {};
    BigCounter x_offset {};

    for(BigCounter i {}; i < t_txt_coords.first.text.size(); ++i)
    {
        const char txt {t_txt_coords.first.text[i]};

        if(txt == '\n')
        {
            ++y_offset;
            x_offset = 0;

        } else 
        {
            setPixel(
                {static_cast<BigCounter>(t_txt_coords.second.x + x_offset), static_cast<BigCounter>(t_txt_coords.second.y - y_offset)},
                {t_txt_coords.first.fore, t_txt_coords.first.back, t_txt_coords.first.text[i]}
            );

            ++x_offset;
        }
    }

    return *this;
}

rdm::types::Frame& rdm::types::Frame::operator<<(const std::pair<const VerticalText&, const Size>& t_txt_coords)
{
    BigCounter y_offset {};
    BigCounter x_offset {};

    for(BigCounter i {}; i < t_txt_coords.first.text.size(); ++i)
    {
        const char txt {t_txt_coords.first.text[i]};

        if(txt == '\n')
        {
            ++x_offset;
            y_offset = 0;

        } else 
        {
            setPixel(
                {static_cast<BigCounter>(t_txt_coords.second.x + x_offset), static_cast<BigCounter>(t_txt_coords.second.y - y_offset)},
                {t_txt_coords.first.fore, t_txt_coords.first.back, t_txt_coords.first.text[i]}
            );

            ++y_offset;
        }
    }

    return *this;
}

rdm::types::Frame& rdm::types::Frame::operator<<(const rdm::abstr::Drawable& drawable_object)
{
    for(const auto& i : drawable_object.elements)
    {
        if(std::get<bool>(i))
        {
            *this << std::make_pair(std::get<Texture>(i), std::get<Size>(i));
        }
    }

    return *this;
}

void rdm::types::Frame::setPixel(const Size t_coords, const Pixel t_pxl)
{
    if(t_coords.bothAxesAreLesser(size))
    {
        Pixel& frame_pixel {pixels[t_coords.x][t_coords.y]};

        if(t_pxl.fore != Color::transp)
        {
            frame_pixel.fore = t_pxl.fore;
        }
    
        if(t_pxl.back != Color::transp)
        {
            frame_pixel.back = t_pxl.back;
        }
    
        if(t_pxl.txt != Pixel::transp_char)
        {
            frame_pixel.txt = t_pxl.txt;
        }
    }
}

void rdm::types::Frame::drawCenter(const Pixel t_pxl)
{
    pixels[size.x / 2][size.y / 2] = t_pxl;
}

rdm::types::Size rdm::types::Frame::getCenter() const
{
    return size / 2;
}

void rdm::types::Frame::fill(const Pixel t_pxl)
{
    for(BigCounter i {}; i < size.x; ++i)
    {
        for(BigCounter j {}; j < size.y; ++j)
        {
            pixels[i][j] = t_pxl;
        }
    }
}

void rdm::types::Frame::clear()
{
    fill(Pixel{Color::black, Color::black, ' '});
}