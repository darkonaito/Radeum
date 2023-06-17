#include "window.hpp"
#include "coords.hpp"

rdm::types::Window::Window(
    Size t_pos,
    Size t_size,
    const std::string_view& t_title
):
    handle(GetConsoleWindow())
{
    SetWindowTextA(handle, t_title.data());
    move(t_pos);
    resizeClientArea(t_size);
}

void rdm::types::Window::move(Size t_abs_pos)
{
    SetWindowPos(
        // Handle to the window used by the current console
        handle,
        // Null (unusued parameter)
        nullptr, 
        // New X and Y position for the window
        static_cast<int>(t_abs_pos.x),
        static_cast<int>(t_abs_pos.y), 
        // Generic X and Y for the expected new size parameters (unusued parameters)
        0, 0,
        // Ignore the new size parameters, don't do stuff with the second function parameter
        SWP_NOSIZE | SWP_NOZORDER);
}

void rdm::types::Window::move(Coords t_rel_pos)
{
    move(getCoords() + t_rel_pos);
}

void rdm::types::Window::resize(Size t_abs_size)
{
    SetWindowPos(
        // Handle to the window used by the current console
        handle,
        // Null (unusued parameter)
        nullptr,
        // Generic X and Y for the expected new position parameters (unusued parameters)
        0, 0,
        // New X and Y size for the window
        static_cast<int>(t_abs_size.x),
        static_cast<int>(t_abs_size.y),
        // Ignore the new position parameters, don't do stuff with the second function parameter
        SWP_NOMOVE | SWP_NOZORDER
    );
}

void rdm::types::Window::resize(Coords t_rel_size)
{
    resize(getSize() + t_rel_size);
}

void rdm::types::Window::resizeClientArea(Size t_abs_size)
{
    static RECT rect;
    static Size client_area_coords;

    client_area_coords = getClientAreaCoords();

    rect.left   = client_area_coords.x;
    rect.top    = client_area_coords.y;
    rect.right  = client_area_coords.x + t_abs_size.x;
    rect.bottom = client_area_coords.y + t_abs_size.y;


    LONG style = GetWindowLong(handle, GWL_STYLE);

    AdjustWindowRect(
        &rect,
        style,
        false
    );


    SetWindowPos(
        // Handle to the console window
        handle,
        // Ignored parameter
        nullptr,
        // New window coords
        rect.left, rect.top,
        // New window size
        rect.right - rect.left, rect.bottom - rect.top,
        // Ignore second parameter
        SWP_NOZORDER
    );
}

void rdm::types::Window::resizeClientArea(Coords t_rel_size)
{
    resizeClientArea(getClientAreaSize() + t_rel_size);
}

void rdm::types::Window::setTitle(const std::string_view& t_title)
{
    // Use c-style string of t_title as title
    SetConsoleTitle(t_title.data());
}

rdm::types::Size rdm::types::Window::getCoords() const
{
    // Static const pointer to rect
    static RECT rect;

    // Gets top-left and bottom-right coords of the window 
    GetWindowRect(handle, &rect);

    // Return coords
    return Size {
        static_cast<BigCounter>(rect.left),
        static_cast<BigCounter>(rect.top)
    };

}

rdm::types::Size rdm::types::Window::getSize() const
{
    // Static const pointer to rect
    static RECT rect; 

    // Gets top-left and bottom-right coords of the window 
    GetWindowRect(handle, &rect);

    // Calculates x and y by subtracting the starting coords to the ending coords and returns them
    return Size {
        static_cast<BigCounter>(rect.right  - rect.left),
        static_cast<BigCounter>(rect.bottom - rect.top)
    };
}

rdm::types::Size rdm::types::Window::getClientAreaCoords() const
{
    static POINT client_area_start_coords;

    client_area_start_coords.x = 0;
    client_area_start_coords.y = 0;

    ClientToScreen(handle, &client_area_start_coords);

    return Size {
        static_cast<BigCounter>(client_area_start_coords.x),
        static_cast<BigCounter>(client_area_start_coords.y)
    };
}

rdm::types::Size rdm::types::Window::getClientAreaSize() const
{
    static RECT rect;

    GetClientRect(handle, &rect);

    return Size {
        static_cast<BigCounter>(rect.right),
        static_cast<BigCounter>(rect.bottom),
    };
}

void rdm::types::Window::setVisibility(bool t_show)
{
    ShowWindow(handle, static_cast<int>(t_show));
}

bool rdm::types::Window::isFocused() const
{
    // GetForegroundWindow() returns and handle to the currently focused window
    return (handle == GetForegroundWindow());
}