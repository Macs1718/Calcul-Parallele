#ifndef _MANDELBULB_HPP_
#define _MANDELBULB_HPP_
#include <vector>
#include <tuple>
#include "vector3d.hpp"
#include "point3d.hpp"
#include "types.hpp"

class mandelbulb
{
public:
    /**
     * @brief Define a mandelbulb with order order
     * @details Define the serie :
     *       zh_{n+1} = zh_{n}^{order} + ch
     *       zh_{0} = <0,0,0>
     * where zh_{n} and c are hypercomplex numbers defined as a triplet
     * z = <x,y,z> = rho<sin(theta)cos(phi),sin(phi)*sin(theta),cos(theta)> and the power function :
     * zh^{n} = rho^{n}<sin(n.theta)cos(n.phi),sin(n.phi).sin(n.theta),cos(n.theta)>
     * 
     * @param order [description]
     * @param max_iter [description]
     */
    mandelbulb( unsigned order, unsigned max_iter ) : degree(order), max_iteration(max_iter)
    {}
    mandelbulb( const mandelbulb& ) = default;
    mandelbulb( mandelbulb&& )      = default;
    ~mandelbulb() = default;

    mandelbulb& operator = ( const mandelbulb& ) = default;
    mandelbulb& operator = ( mandelbulb&& ) = default;

    /**
     * @brief Compute an approximation of the distance between a point and the mandelbulb.
     * @details [long description]
     * 
     * @param pt [description]
     * @return [description]
     */
    real_t distance_estimator( const point3d& pt ) const;

    vector3d normal_at( const point3d& pt ) const;

    int degree;
    unsigned max_iteration;
};

#endif
