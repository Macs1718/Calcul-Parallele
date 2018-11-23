#ifndef _MANDELBULB_VECTOR3D_HPP_
#define _MANDELBULB_VECTOR3D_HPP_
#include <iostream>
#include <cmath>
#include "types.hpp"

class vector3d
{
public:
    real_t x,y,z;

    vector3d() = default;
    vector3d( real_t xx ) : x(xx), y(xx), z(xx)
    {}
    vector3d( real_t xx, real_t yy, real_t zz ) :
        x(xx), y(yy), z(zz)
    {}
    vector3d( const vector3d& ) = default;
    vector3d( vector3d&& ) = default;
    ~vector3d() = default;

    vector3d& operator = ( const vector3d& ) = default;
    vector3d& operator = ( vector3d&& ) = default;

    vector3d& normalize();
    vector3d normalize() const
    {
        vector3d u(*this);
        return u.normalize();
    }

    vector3d homothetie( const real_t& a ) const
    {
        return { a*this->x, a*this->y, a*this->z };
    }

    vector3d operator * ( const vector3d& u ) const
    {
        return { this->x * u.x, this->y * u.y, this->z * u.z };
    }

    real_t operator | ( const vector3d& u ) const
    {
        return this->x * u.x + this->y * u.y + this->z * u.z;
    }

    vector3d operator + ( const vector3d& u ) const
    {
        return { this->x + u.x, this->y + u.y, this->z + u.z };
    }

    vector3d operator - ( const vector3d& u ) const
    {
        return { this->x - u.x, this->y - u.y, this->z - u.z };
    }

    vector3d operator - () const
    {
        return { -this->x, -this->y, -this->z };
    }

    vector3d& operator += ( const vector3d& u )
    {
        this->x += u.x; this->y += u.y; this->z += u.z;
        return *this;
    }

    vector3d& operator -= ( const vector3d& u )
    {
        this->x -= u.x; this->y -= u.y; this->z -= u.z;
        return *this;
    }

    vector3d& operator *= ( const vector3d& u )
    {
        this->x *= u.x; this->y *= u.y; this->z *= u.z;
        return *this;
    }

    vector3d operator ^ ( const vector3d& u ) const
    {
        return vector3d{ this->y*u.z - this->z*u.y,
                         this->z*u.x - this->x*u.z,
                         this->x*u.y - this->y*u.x};
    }

    std::ostream& dump( std::ostream& sout ) const
    {
        sout << this->x << " " << this->y << " " << this->z;
        return sout;
    }

    explicit operator std::string() const;
};

inline vector3d 
operator * ( const real_t& alpha, const vector3d& u )
{
    return u.homothetie(alpha);
}

inline real_t norm( const vector3d& u )
{
    return u.x*u.x + u.y*u.y + u.z*u.z;
}

inline real_t abs( const vector3d& u )
{
    return std::sqrt(norm(u));
}

inline std::ostream& operator << ( std::ostream& sout, const vector3d& pt )
{
    sout << "{ " << pt.x << ", " << pt.y << ", " << pt.z << "}";
    return sout;
}

#endif
