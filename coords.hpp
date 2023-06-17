#ifndef D_COORDS_HPP
#define D_COORDS_HPP

// requires
#include <concepts>
// is_same 
#include <type_traits>
#include "types.hpp"

template <typename T> requires (std::is_arithmetic_v<T>)
struct rdm::types::GenericCoords
{
    /*** Constructors ***/
    
    using Axis = T;

    constexpr GenericCoords(T t_x = {}, T t_y = {}):
        x(t_x), y(t_y)
    {
    }

    // ... In case the underlying type of the GenericCoords<> used as parameter is different from the one of the object to be constructed 

    template <typename U>

    requires (!std::is_same<T, U>{})

    // Conversion constructor
    GenericCoords(const GenericCoords<U>& c):
    x(static_cast<T>(c.x)), y(static_cast<T>(c.y))
    {
    }

    // Copy constructor 
    constexpr GenericCoords(const GenericCoords<T>& c):
        x(c.x), y(c.y)
    {}

    // *Operators*

    GenericCoords<T> operator=(GenericCoords<T>);

    GenericCoords<T> operator+(GenericCoords<T>) const;
    GenericCoords<T> operator-(GenericCoords<T>) const;

    GenericCoords<T> operator*(GenericCoords<T>) const;
    GenericCoords<T> operator/(GenericCoords<T>) const;

    GenericCoords<T> operator*(T) const;
    GenericCoords<T> operator/(T) const;

    GenericCoords<T> operator+=(GenericCoords<T>);
    GenericCoords<T> operator-=(GenericCoords<T>);

    GenericCoords<T> operator*=(GenericCoords<T>);
    GenericCoords<T> operator/=(GenericCoords<T>);

    GenericCoords<T> operator*=(T);
    GenericCoords<T> operator/=(T);

    bool operator==(GenericCoords<T>) const;
    bool operator!=(GenericCoords<T>) const;

    // Bool functions

    bool eitherAxisIsGreater(GenericCoords<T>) const;
    bool eitherAxisIsGrtrEqu(GenericCoords<T>) const;
    bool eitherAxisIsLesser(GenericCoords<T>)  const;
    bool eitherAxisIsLessEqu(GenericCoords<T>) const;

    bool bothAxesAreGreater(GenericCoords<T>) const;
    bool bothAxesAreGrtrEqu(GenericCoords<T>) const;
    bool bothAxesAreLesser(GenericCoords<T>)  const;
    bool bothAxesAreLessEqu(GenericCoords<T>) const;

    inline bool areWithin(GenericCoords<T> c1, GenericCoords<T> c2) const
    {
        return bothAxesAreGrtrEqu(c1) && bothAxesAreLessEqu(c2);
    }

    // *Methods*

    GenericCoords<T> swapAxes();
    GenericCoords<T> returnSwappedAxesCoords() const;

    T x;
    T y;
};

template <class T>
rdm::types::GenericCoords<T> rdm::types::GenericCoords<T>::operator=(GenericCoords<T> c)
{
    x = c.x;
    y = c.y;

    return *this;
}

template <class T>
rdm::types::GenericCoords<T> rdm::types::GenericCoords<T>::operator+(GenericCoords<T> c) const
{
    return GenericCoords<T>{
        static_cast<T>(x + c.x),
        static_cast<T>(y + c.y)
    };
}

template <class T>
rdm::types::GenericCoords<T> rdm::types::GenericCoords<T>::operator-(GenericCoords<T> c) const
{
    return GenericCoords<T>{
        static_cast<T>(x - c.x),
        static_cast<T>(y - c.y)
    };
}

template <class T>
rdm::types::GenericCoords<T> rdm::types::GenericCoords<T>::operator*(GenericCoords<T> c) const
{
    return GenericCoords<T>{
        static_cast<T>(x * c.x),
        static_cast<T>(y * c.y)
    };
}

template <class T>
rdm::types::GenericCoords<T> rdm::types::GenericCoords<T>::operator/(GenericCoords<T> c) const
{
    return GenericCoords<T>{
        static_cast<T>(x / c.x),
        static_cast<T>(y / c.y)
    };
}

template <class T>
rdm::types::GenericCoords<T> rdm::types::GenericCoords<T>::operator*(T n) const
{
    return GenericCoords<T>{
        static_cast<T>(x * n),
        static_cast<T>(y * n)
    };
}

template <class T>
rdm::types::GenericCoords<T> rdm::types::GenericCoords<T>::operator/(T n) const
{
    return GenericCoords<T>{
        static_cast<T>(x / n),
        static_cast<T>(y / n)
    };
}

template <class T>
rdm::types::GenericCoords<T> rdm::types::GenericCoords<T>::operator+=(GenericCoords<T> c)
{
    x += c.x;
    y += c.y;

    return *this;
}

template <class T>
rdm::types::GenericCoords<T> rdm::types::GenericCoords<T>::operator-=(GenericCoords<T> c)
{
    x -= c.x;
    y -= c.y;

    return *this;
}

template <class T>
rdm::types::GenericCoords<T> rdm::types::GenericCoords<T>::operator*=(GenericCoords<T> c)
{
    x *= c.x;
    y *= c.y;

    return *this;
}

template <class T>
rdm::types::GenericCoords<T> rdm::types::GenericCoords<T>::operator/=(GenericCoords<T> c)
{
    x /= c.x;
    y /= c.y;

    return *this;
}

template <class T>
rdm::types::GenericCoords<T> rdm::types::GenericCoords<T>::operator*=(T n)
{
    x *= n;
    y *= n;

    return *this;
}

template <class T>
rdm::types::GenericCoords<T> rdm::types::GenericCoords<T>::operator/=(T n)
{
    x /= n;
    y /= n;

    return *this;
}

template <class T>
bool rdm::types::GenericCoords<T>::operator==(GenericCoords<T> c) const
{
    return x == c.x && y == c.y;
}

template <class T>
bool rdm::types::GenericCoords<T>::operator!=(GenericCoords<T> c) const
{
    return x != c.x || y != c.y;
}

// functions

template <class T>
bool rdm::types::GenericCoords<T>::eitherAxisIsGreater(GenericCoords<T> c) const
{
    return x > c.x || y > c.y;
}

template <class T>
bool rdm::types::GenericCoords<T>::eitherAxisIsGrtrEqu(GenericCoords<T> c) const
{
    return x >= c.x || y >= c.y;
}

template <class T>
bool rdm::types::GenericCoords<T>::eitherAxisIsLesser(GenericCoords<T> c) const
{
    return x < c.x || y < c.y;
}

template <class T>
bool rdm::types::GenericCoords<T>::eitherAxisIsLessEqu(GenericCoords<T> c) const
{
    return x <= c.x || y <= c.y;
}

template <class T>
bool rdm::types::GenericCoords<T>::bothAxesAreGreater(GenericCoords<T> c) const
{
    return x > c.x && y > c.y;
}

template <class T>
bool rdm::types::GenericCoords<T>::bothAxesAreGrtrEqu(GenericCoords<T> c) const
{
    return x >= c.x && y >= c.y;
}

template <class T>
bool rdm::types::GenericCoords<T>::bothAxesAreLesser(GenericCoords<T> c) const
{
    return x < c.x && y < c.y;
}

template <class T>
bool rdm::types::GenericCoords<T>::bothAxesAreLessEqu(GenericCoords<T> c) const
{
    return x <= c.x && y <= c.y;
}

template <class T>
rdm::types::GenericCoords<T> rdm::types::GenericCoords<T>::swapAxes()
{
    T temp = x;
    x = y;
    y = temp;

    return *this;
}

template <class T>
rdm::types::GenericCoords<T> rdm::types::GenericCoords<T>::returnSwappedAxesCoords() const
{
    return GenericCoords<T>{y, x};
}

#endif