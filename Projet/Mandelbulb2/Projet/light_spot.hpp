#ifndef _MANDELBULB_LIGHT_SPOT_HPP_
#define _MANDELBULB_LIGHT_SPOT_HPP_
#include <cmath>
#include "light.hpp"
#include "types.hpp"

class light_spot : public light
{
public:
    point3d  position;
    vector3d direction;
    real_t   angle;

    light_spot( const point3d& pos, const vector3d& dir, real_t ang, const color_rgb& col ) :
        light(col), position(pos), direction(dir.normalize()), angle(ang)
    {}
    light_spot( const light_spot& ) = default;
    light_spot( light_spot&& ) = default;
    ~light_spot() = default;

    /* Pour le shading */
    virtual color_rgb contribution_at( const point3d& pos, const vector3d& nrm ) const final
    {
        auto dir_lght = this->direction_from(pos);
        // Calcul angle entre direction du spot et le rayon reliant le point au spot :
        real_t ang = std::acos(dir_lght|this->direction);
        // On regarde si le spot nous éclaire bien...
        if ( std::abs(ang) < angle )
            return std::max(real_t(0),(nrm | dir_lght)) * this->color;
        else return {0,0,0};
    }
    /* Pour l'ombrage */
    virtual vector3d direction_from( const point3d& pos ) const final
    {
        return (pos - this->position).normalize();
    }
    virtual std::shared_ptr<light> clone() const
    {
        return std::make_shared<light_spot>(*this);
    }

};

#endif
