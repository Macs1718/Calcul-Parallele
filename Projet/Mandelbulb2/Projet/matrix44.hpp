#ifndef _MANDELBULB_MATRIX44_HPP
#define _MANDELBULB_MATRIX44_HPP
#include <algorithm>
#include <array>
#include "point3d.hpp"
#include "vector3d.hpp"

struct matrix44
{
    std::array<real_t,12> coefs;
    matrix44( const std::initializer_list<real_t>& mcoefs ) : coefs()
    {
        std::copy(mcoefs.begin(), mcoefs.end(), coefs.begin());
    }
    matrix44( const matrix44& ) = default;
    matrix44( matrix44&& ) = default;
    ~matrix44() = default;

    matrix44& operator = ( const matrix44& ) = default;
    matrix44& operator = ( matrix44&& ) = default;

    vector3d operator* ( const vector3d& u )
    {
        return { coefs[0] * u.x + coefs[1] * u.y + coefs[2] * u.z,
                 coefs[4] * u.x + coefs[5] * u.y + coefs[6] * u.z,
                 coefs[8] * u.x + coefs[9] * u.y + coefs[10]* u.z };
    }

    point3d operator* ( const point3d& u )
    {
        return { coefs[0] * u.x + coefs[1] * u.y + coefs[2] * u.z + coefs[3],
                 coefs[4] * u.x + coefs[5] * u.y + coefs[6] * u.z + coefs[7],
                 coefs[8] * u.x + coefs[9] * u.y + coefs[10]* u.z + coefs[11] };
    }
};

inline std::ostream& operator<< ( std::ostream& sout, const matrix44& mat )
{
    sout << mat.coefs[0] << "\t" << mat.coefs[1] << "\t" << mat.coefs[2] << "\t" << mat.coefs[3] << "\n"
         << mat.coefs[4] << "\t" << mat.coefs[5] << "\t" << mat.coefs[6] << "\t" << mat.coefs[7] << "\n"
         << mat.coefs[8] << "\t" << mat.coefs[9] << "\t" << mat.coefs[10] << "\t" << mat.coefs[11] << std::endl;
    return sout;
}

#endif
