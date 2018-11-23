#ifndef _MANDELBULB_POINT3D_HPP_
#define _MANDELBULB_POINT3D_HPP_
#include <iostream>
#include <cmath>
#include "vector3d.hpp"

class point3d
{
public:
    real_t x,y,z;

    point3d() = default;
    point3d( real_t xx ) : x(xx), y(xx), z(xx)
    {}
    point3d( real_t xx, real_t yy, real_t zz ) :
        x(xx), y(yy), z(zz)
    {}
    point3d( const point3d& ) = default;
    point3d( point3d&& ) = default;
    ~point3d() = default;

    point3d& operator = ( const point3d& ) = default;
    point3d& operator = ( point3d&& ) = default;


    point3d operator + ( const point3d& u ) const
    {
        return { this->x + u.x, this->y + u.y, this->z + u.z };
    }

    point3d operator + ( const vector3d& u ) const
    {
        return { this->x + u.x, this->y + u.y, this->z + u.z };
    }


    vector3d operator - ( const point3d& u ) const
    {
        return { this->x - u.x, this->y - u.y, this->z - u.z };
    }

    point3d operator - ( const vector3d& u ) const
    {
        return { this->x - u.x, this->y - u.y, this->z - u.z };
    }

    point3d operator - () const
    {
        return { -this->x, -this->y, -this->z };
    }

    point3d& operator += ( const point3d& u )
    {
        this->x += u.x; this->y += u.y; this->z += u.z;
        return *this;
    }

    point3d& operator -= ( const point3d& u )
    {
        this->x -= u.x; this->y -= u.y; this->z -= u.z;
        return *this;
    }

    std::ostream& dump( std::ostream& sout ) const
    {
        sout << this->x << " " << this->y << " " << this->z;
        return sout;
    }

    explicit operator vector3d() const { return {this->x,this->y,this->z}; }

    explicit operator std::string() const;
};

inline point3d 
operator * ( const real_t& alpha, const point3d& u )
{
    return {alpha*u.x,alpha*u.y,alpha*u.z};
}

inline std::ostream& operator << ( std::ostream& sout, const point3d& pt )
{
    sout << "{ " << pt.x << ", " << pt.y << ", " << pt.z << "}";
    return sout;
}

#endif
