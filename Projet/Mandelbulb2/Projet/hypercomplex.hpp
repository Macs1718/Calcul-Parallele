#ifndef _MANDELBULB_HYPERCOMPLEX_HPP_
#define _MANDELBULB_HYPERCOMPLEX_HPP_
#include "types.hpp"
#include <cmath>
#include <iostream>

struct hypercomplex {
public:
    real_t x, y, z;
    hypercomplex() = default;
    hypercomplex( real_t rx, real_t ry, real_t rz )
        : x( rx ), y( ry ), z( rz )
    {
    }
    hypercomplex( const hypercomplex & ) = default;
    hypercomplex( hypercomplex && ) = default;
    ~hypercomplex() = default;

    hypercomplex operator+( const hypercomplex &hz ) const
    {
        return {this->x + hz.x, this->y + hz.y, this->z + hz.z};
    }

    hypercomplex &operator=( const hypercomplex & ) = default;
    hypercomplex &operator=( hypercomplex && ) = default;

    /**
   * @brief Renvoie la norme au carré de l'hypercomplexe
   * @details Renvoie la norme au carré de l'hypercomplexe
   * 
   * Même protocole que la classe complexe de la STL...
   * 
   * @return le carré du module de l'hypercomplexe
   */
    real_t norm() const
    {
        return this->x * this->x + this->y * this->y + this->z * this->z;
    }

    template <int n>
    hypercomplex pow() const;

    hypercomplex pow( int n ) const;
};

/**
   * @brief Renvoie la norme au carré de l'hypercomplexe
   * @details Renvoie la norme au carré de l'hypercomplexe
   * 
   * Même interface que la classe complexe de la STL...
   * 
   * @return le carré du module de l'hypercomplexe
   */
real_t norm( const hypercomplex &hz )
{
    return hz.norm();
}
/**
 * @brief Renvoie le module de l'hypercomplexe
 * @details Renvoie le module de l'hypercomplexe
 * 
 * même interface que les complexes
 * 
 * @param hz [description]
 * @return [description]
 */
real_t abs( const hypercomplex &hz )
{
    return std::sqrt( hz.norm() );
}

hypercomplex
hypercomplex::pow(int n) const
{
    //constexpr const real_t pi = 3.141592653589793;
    real_t r = abs( *this );
    real_t theta = n * std::acos(z/r);
    real_t phi = n*std::atan2(y,x);
    real_t rn = std::pow(r, real_t(n));
    real_t sin_theta = std::sin( theta );
    return {rn * sin_theta * std::cos(phi), rn * sin_theta * std::sin(phi), rn * std::cos( theta )};
}


/**
 * @brief Calcul la puissance nième d'un hypercomplex
 * @details Calcul la puissance nième d'un hypercomplex
 * 
 * Le calcul de la puissance nième se fait via la représentation sphérique de h'hypercomplexe soit :
 * 
 * <x,y,z>^{n} = r^{n}< cos(n.theta)cos(n.phi), sin(n.theta)cos(n.phi), sin(n.theta) >
 * 
 * où | r = sqrt(x²+y²+z²)
 *    | theta = arctan(y/x)
 *    | et phi = arctan(sqrt(x²+y²)/z) = arcsin(z/r) )
 * 
 * @tparam n la puissance nième
 */
template <int n>
hypercomplex
hypercomplex::pow() const
{
    const real_t pi = std::acos( -1 );
    real_t r = abs( *this );
    real_t theta = std::atan2( std::sqrt(x*x+y*y), z );
    real_t phi = std::atan2(y,x);
    real_t rn = 1;
    for ( int i = 0; i < n; ++i ) rn *= r;
    real_t sin_n_theta = std::sin(n * theta );
    return {rn * sin_n_theta * std::cos(n * phi), rn * sin_n_theta * std::sin(n*phi), rn * std::cos( n * theta )};
}
//
template <>
hypercomplex
hypercomplex::pow<1>() const
{
    return *this;
}
// A voir si on ne peut pas spécialiser la puissance pour 3, 5, etc. en simplifiant la formule !

inline std::ostream& operator << ( std::ostream& sout, const hypercomplex& c )
{
  sout << "( " << c.x << ", " << c.y << ", " << c.z << " )";
  return sout;
}
#endif
