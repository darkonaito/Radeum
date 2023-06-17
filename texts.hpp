#ifndef D_TEXTS_HPP
#define D_TEXTS_HPP

#include "types.hpp"
#include <string>

struct rdm::types::HorizontalText
{
    std::string text;
    Color fore;
    Color back;
};

struct rdm::types::VerticalText
{
    std::string text;
    Color fore;
    Color back;
};

#endif