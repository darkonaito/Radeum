namespace utils2d
{
    struct Line;
}

struct Line2D
{
    GenericCoords<double> p1, p2;

    Pixel pxl;

    operator Line() const 
    {
        return Line(
            {
                std::round(p1.x),
                std::round(p1.y)
            },
            {
                std::round(p2.x),
                std::round(p2.y)
            },
            pxl
        );
    }
};