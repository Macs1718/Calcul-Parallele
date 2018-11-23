#ifndef _MANDELBULB_LIGHT_POINT_HPP_
#define _MANDELBULB_LIGHT_POINT_HPP_
#include "types.hpp"
#include "light.hpp"

class light_point : public light
{
public:
    point3d position;

    light_point( const point3d& pos, const color_rgb& col ) : 
        light(col), position(pos)
    {}
    light_point( const light_point& ) = default;
    light_point( light_point&& ) = default;
    ~light_point() = default;

    /* Pour le shading */
    virtual color_rgb contribution_at( const point3d& pos, const vector3d& nrm ) const final
    {
        auto direction = this->direction_from(pos);
        return std::max(real_t(0),(nrm | direction)) * this->color;
    }
    /* Pour l'ombrage */
    virtual vector3d direction_from( const point3d& pos ) const final
    {
        return (pos - position).normalize();
    }

    virtual std::shared_ptr<light> clone() const
    {
        return std::make_shared<light_point>(*this);
    }

};

#endif
