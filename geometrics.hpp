#ifndef D_LINE_HPP
#define D_LINE_HPP

#include "types.hpp"
#include "coords.hpp"
#include "pixel.hpp"

struct rdm::types::Line
{
    Size  p1;
    Size  p2;
    Pixel pxl;
};

struct rdm::types::Rectangle
{
    Size  p1;
    Size  p4;
    Pixel pxl;
};

struct rdm::types::FilledRectangle
{
    Size  p1;
    Size  p4;
    Pixel pxl;
};

struct rdm::types::PointsStructure
{
    std::vector<Size> points;
    Pixel pxl;
};

struct rdm::types::FilledPointsStructure
{
    std::vector<Size> points;
    Pixel pxl;
};

#endif