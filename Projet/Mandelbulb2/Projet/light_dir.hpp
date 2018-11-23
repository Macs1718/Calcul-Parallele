#ifndef _MANDELBULB_LIGHT_DIR_HPP_
#define _MANDELBULB_LIGHT_DIR_HPP_
#include "light.hpp"

class light_dir : public light
{
public:
    vector3d direction;
    light_dir( const vector3d& dir, const color_rgb& col ) : 
        light(col), direction(dir.normalize())
    {}
    light_dir(const light_dir& lght ) = default;
    light_dir( light_dir&& ) = default;
    ~light_dir() = default;

    virtual color_rgb contribution_at( const point3d& pos, const vector3d& nrm ) const final
    {
        return std::max(real_t(0),(nrm | this->direction)) * this->color;
    }
    /* Pour l'ombrage */
    virtual vector3d direction_from( const point3d& pos ) const final
    {
        return this->direction;
    }
    virtual std::shared_ptr<light> clone() const
    {
        return std::make_shared<light_dir>(*this);
    }

};
#endif
