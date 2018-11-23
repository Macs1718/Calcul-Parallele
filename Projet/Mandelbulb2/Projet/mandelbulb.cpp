#include "mandelbulb.hpp"
#include "hypercomplex.hpp"
#include <cmath>

real_t
mandelbulb::distance_estimator( const point3d &pt ) const
{
    hypercomplex z{pt.x, pt.y, pt.z};
    hypercomplex c( z );
    real_t dr = 1, r = 0;
    for ( unsigned iter = 0; iter < this->max_iteration; ++iter ) {
        r = abs( z );
        if ( r > 2 ) break;
        double rnm1 = std::pow( r, this->degree - 1 );
        dr = rnm1 * this->degree * dr + 1;
        // z = z.pow(this->degree) + c;
        real_t theta = this->degree * std::acos( z.z / r );
        real_t phi = this->degree * std::atan2( z.y, z.x );
        real_t rn = r * rnm1;
        real_t rn_sin_theta = rn * std::sin( theta );
        z = hypercomplex{rn_sin_theta * std::cos( phi ), rn_sin_theta * std::sin( phi ),
                         rn * std::cos( theta )} + c;
    }
    return real_t( 0.5 ) * std::log( r ) * r / dr;
}

vector3d
mandelbulb::normal_at( const point3d &pt ) const
{
    real_t eps = 2.E-6;
    real_t n = this->distance_estimator( pt );
    real_t dx = this->distance_estimator( pt + vector3d{eps, 0, 0} ) - n;
    real_t dy = this->distance_estimator( pt + vector3d{0, eps, 0} ) - n;
    real_t dz = this->distance_estimator( pt + vector3d{0, 0, eps} ) - n;
    vector3d grad{dx, dy, dz};
    return grad.normalize();
}
