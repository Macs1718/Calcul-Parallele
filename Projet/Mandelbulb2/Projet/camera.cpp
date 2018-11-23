#include <cmath>
#include "camera.hpp"

camera::camera( const point3d& pos, const point3d& target, const vector3d& cam_right ) : 
    position(pos), look_at(0,0,0), direction((pos-target).normalize()), right(), up(), fov(30)
{
    this->right = cam_right ^ this->direction;
    this->right.normalize();
    this->up = this->direction ^ this->right;
    this->up.normalize();
}
    
camera::camera( const point3d& pos, const vector3d& dir, const vector3d& cam_right ) :
    position(pos), look_at(0,0,0), direction(dir.normalize()), right(), up(), fov(30)
{
    this->right = cam_right ^ this->direction;
    right.normalize();
    this->up = this->direction ^ this->right;
    this->up.normalize();
}

void camera::move( real_t ddist, real_t dtheta, real_t dphi )
{
    // Calcul en polaire de la position de la camera :
    real_t dist = std::sqrt(position.x*position.x+position.y*position.y+position.z*position.z);
    real_t theta = std::atan2( std::sqrt(position.x*position.x+position.y*position.y), position.z );
    real_t phi = std::atan2(position.y,position.x);
    dist += ddist;
    theta += dtheta;
    phi += dphi;
    position = point3d{dist * std::sin(theta) * std::cos(phi), dist * std::sin(theta) * std::sin(phi), 
                       dist * std::cos(theta)};
}
