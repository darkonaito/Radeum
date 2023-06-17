#include "drawable.hpp"

#include <iostream>

rdm::abstr::Drawable::Drawable(std::initializer_list<Element> t_elements)
:
    elements(t_elements)
{   
}

rdm::abstr::Drawable::Drawable(const std::vector<Element>& t_elements)
:
    elements(t_elements)
{
}