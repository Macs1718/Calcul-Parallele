#ifndef _MANDELBULB_LIGHT_HPP_
#define _MANDELBULB_LIGHT_HPP_
#include <memory>
#include "vector3d.hpp"
#include "point3d.hpp"

using color_rgb = vector3d;

class light
{
public:
    color_rgb color;

    light( const color_rgb& rgb ) : color(rgb)
    {}
    light( const light& ) = default;
    light( light&& ) = default;
    virtual ~light() = default;

    /* Pour le shading */
    virtual color_rgb contribution_at( const point3d& pos, const vector3d& nrm ) const = 0;
    /* Pour l'ombrage */
    virtual vector3d direction_from( const point3d& pos ) const = 0;
    /* Clonage d'une lumière */
    virtual std::shared_ptr<light> clone() const = 0;
};

#endif
