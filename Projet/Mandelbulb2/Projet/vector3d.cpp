#include "vector3d.hpp"
#include <sstream>

vector3d &vector3d::normalize()
{
    real_t nrm2 = norm( *this );
    if ( nrm2 > 0 ) {
        real_t inv_nrm = real_t(1) / std::sqrt( nrm2 );
        this->x *= inv_nrm;
        this->y *= inv_nrm;
        this->z *= inv_nrm;
    }
    return *this;
}

vector3d::operator std::string() const
{
    std::ostringstream sout;
    sout << "{ " << this->x << ", " << this->y << ", " << this->z << "}";
    return sout.str();
}
