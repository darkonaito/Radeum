#ifndef D_TYPES_HPP
#define D_TYPES_HPP
 
#include <cstdint>
#include <type_traits>
#include <concepts>
#include <vector> 
#include <utility>

namespace rdm::types
{
    using Counter       = uint8_t;
    using BigCounter    = uint16_t;
    using Axis          = int32_t; 
    
    enum class KeyState : Counter;
    enum class Color    : Counter;

    template <class T> requires (std::is_arithmetic_v<T>)
    struct GenericCoords; 

    using Size   = GenericCoords<BigCounter>;
    using Coords = GenericCoords<Axis>;

    struct Pixel;

    struct KeyEvent;

    struct Line;
    struct Rectangle;
    struct FilledRectangle;
    struct PointsStructure;
    struct FilledPointsStructure;

    struct HorizontalText;
    struct VerticalText;

    using SendHorizontalText = std::pair<const HorizontalText&, const Size>;
    using SendVerticalText   = std::pair<const VerticalText&,   const Size>; 


    class KeyEventsHandler;
    class RandomGenerator;
    class ResourceLoader;
    class InputHandler;
    class Texture;
    class Console;
    class Button;
    class Buffer;
    class Window;
    class Cursor;
    class Camera;
    class Frame;
    class Key;
}

#endif