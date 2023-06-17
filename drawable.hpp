#ifndef D_DRAWABLE_HPP
#define D_DRAWABLE_HPP

#include <initializer_list>
#include <tuple>
#include <vector>
#include "texture.hpp"

#include "abstracts.hpp"
#include "types.hpp"

class rdm::abstr::Drawable
{
    friend class rdm::types::Frame;

    public:
        using Element = std::tuple<rdm::types::Texture, rdm::types::Size, bool>;

        Drawable(std::initializer_list<Element> elements);
        Drawable(const std::vector<Element>& elements);

    protected:
        std::vector<Element> elements;
};

#endif